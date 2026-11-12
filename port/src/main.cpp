// Entry point of the native build: PS2Recomp's runner main, plus a watchdog that prints the guest (EE) threads.
//
// Usage: bt2 gamedata/SLUS_214.41 [disc.iso]
//        The folder holding the ELF is cdrom0: and host0:. With the disc image the CD searches and sector reads
//        use the image's own LSNs, which is what the game's FILEIO.IRX reads on the IOP side (DATAP.WAD).
// Environment: BT2_WATCH=<seconds>        print the EE threads every <seconds> (default 5, 0 = off)
//              BT2_INPUT=<t>:<button>[,...] press a pad button at <t> seconds of guest time (NTSC VBlanks / 60)
//                                          for 0.5 s, so runs replay identically at any host speed (start, select, cross,
//                                          circle, square, triangle, up, down, left, right, l1, r1, l2, r2)
//              BT2_CONTROL=<fifo>         read commands from a named pipe while running: a button name presses it
//                                          (as in BT2_INPUT), `shot <file.ppm>` saves the displayed frame
//              BT2_SHOT=<prefix>          save render target and displayed buffer as PPM at each watchdog tick
//
// The watchdog uses the runtime's debug-UI hook (called once per frame from the render loop), so PS2Recomp itself
// is not modified. Each line: thread id, status, wait reason/object, pc, ra, entry; then the semaphores.

#include "ps2_runtime.h"
#include "ps2_identity.h"

void installMovieHle(PS2Runtime &runtime); // movie.cpp
void installIdentityHle(PS2Runtime &runtime); // identity.cpp
int installColTrace(PS2Runtime &runtime); // coltrace.cpp (BT2_COL_TRACE)
void colTraceStats(); // coltrace.cpp
void installCallCounters(PS2Runtime &runtime); // callcount.cpp (BT2_CALLTRACE)
void callCountReport(); // callcount.cpp
int installGuestWatch(PS2Runtime &runtime); // watchaddr.cpp (BT2_WATCH_ADDR)
void guestWatchTick(PS2Runtime &rt); // watchaddr.cpp
int installStoreWatch(PS2Runtime &runtime); // storewatch.cpp (BT2_STORE_ADDR)
void storeWatchSetLiveContext(R5900Context *ctx); // storewatch.cpp
#ifdef BT2_HAVE_NATIVE
int installNativeFunctions(PS2Runtime &rt); // build/gen/native_wrappers.cpp (port/tools/gen_native.py)
#endif
// Buttons held by the scripted input (BT2_INPUT / BT2_CONTROL), active-high; read by movie.cpp to skip movies.
uint16_t g_bt2ScriptedButtons = 0u;
#include "runtime/ee_scheduler.h"
#include "runtime/gs/gs_frontend.h"

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <utility>
#include <vector>
#include <string>

namespace ps2_stubs
{
void setPadOverrideState(uint16_t buttons, uint8_t lx, uint8_t ly, uint8_t rx, uint8_t ry);
void clearPadOverrideState();
extern void (*ps2PadReadHook)(); // Pad.cpp: called on every guest pad read (drives BT2_INPUT off guest time)
}

namespace
{
// libpad button bits (16-bit, active-low on the wire): low byte = data[2], high byte = data[3].
uint16_t buttonBit(const std::string &name)
{
    static const std::pair<const char *, uint16_t> table[] = {
        {"select", 1u << 0}, {"start", 1u << 3}, {"up", 1u << 4}, {"right", 1u << 5}, {"down", 1u << 6},
        {"left", 1u << 7}, {"l2", 1u << 8}, {"r2", 1u << 9}, {"l1", 1u << 10}, {"r1", 1u << 11},
        {"triangle", 1u << 12}, {"circle", 1u << 13}, {"cross", 1u << 14}, {"square", 1u << 15}};
    for (const auto &[n, bit] : table)
        if (name == n)
            return bit;
    return 0u;
}

// Scripted pad input for unattended runs (BT2_INPUT), applied from the per-frame hook.
struct InputScript
{
    std::vector<std::pair<double, uint16_t>> presses;
    size_t next = 0;
    double releaseAt = -1.0;
    double readyAt = 0.0;

    void parse(const char *spec)
    {
        std::string all(spec);
        size_t pos = 0;
        while (pos < all.size())
        {
            size_t end = all.find(',', pos);
            if (end == std::string::npos)
                end = all.size();
            const std::string item = all.substr(pos, end - pos);
            const size_t colon = item.find(':');
            if (colon != std::string::npos)
                presses.emplace_back(std::atof(item.substr(0, colon).c_str()), buttonBit(item.substr(colon + 1)));
            pos = end + 1;
        }
    }

    void tick(double t)
    {
        if (releaseAt >= 0.0 && t >= releaseAt)
        {
            ps2_stubs::clearPadOverrideState();
            g_bt2ScriptedButtons = 0u;
            releaseAt = -1.0;
            readyAt = t + 0.25; // the game must see the button up before the next press
        }
        if (next < presses.size() && t >= presses[next].first && releaseAt < 0.0 && t >= readyAt)
        {
            std::fprintf(stderr, "[input %.1fs] press %04x\n", t, presses[next].second);
            ps2_stubs::setPadOverrideState(static_cast<uint16_t>(0xFFFFu & ~presses[next].second), 0x80, 0x80, 0x80,
                                           0x80);
            g_bt2ScriptedButtons = presses[next].second;
            releaseAt = t + 0.5;
            ++next;
        }
    }
};

// The scripted input advances from the guest's own pad reads, not from the present: a press scheduled for guest
// second T lands on the first read at or after T however slow the host is. ps2_stubs::ps2PadReadHook calls this.
static InputScript *g_inputScript = nullptr;
static PS2Runtime *g_inputRuntime = nullptr;
static void inputOnPadRead()
{
    if (g_inputScript != nullptr && g_inputRuntime != nullptr)
    {
        const double guestTime = static_cast<double>(g_inputRuntime->eeScheduler().currentVSyncTick()) / 60.0;
        g_inputScript->tick(guestTime);
    }
}

const char *statusName(EeThreadStatus s)
{
    switch (s)
    {
    case EeThreadStatus::Running: return "RUN";
    case EeThreadStatus::Ready: return "READY";
    case EeThreadStatus::Waiting: return "WAIT";
    case EeThreadStatus::WaitingSuspended: return "WAITSUSP";
    case EeThreadStatus::Suspended: return "SUSP";
    case EeThreadStatus::Dormant: return "DORMANT";
    }
    return "?";
}

const char *waitName(EeWaitReason r)
{
    switch (r)
    {
    case EeWaitReason::None: return "-";
    case EeWaitReason::Sleep: return "sleep";
    case EeWaitReason::Semaphore: return "sema";
    case EeWaitReason::EventFlag: return "evflag";
    case EeWaitReason::VSync: return "vsync";
    case EeWaitReason::External: return "external";
    case EeWaitReason::Mpeg: return "mpeg";
    }
    return "?";
}

// Live control for unattended debugging (BT2_CONTROL): one command per line from a FIFO.
struct ControlPipe
{
    int fd = -1;
    std::string pending;
    std::vector<std::string> lines;

    void open(const char *path)
    {
        fd = ::open(path, O_RDONLY | O_NONBLOCK);
        if (fd < 0)
            std::fprintf(stderr, "[control] cannot open %s\n", path);
    }

    void poll()
    {
        if (fd < 0)
            return;
        char buf[256];
        ssize_t n;
        while ((n = ::read(fd, buf, sizeof(buf))) > 0)
            pending.append(buf, static_cast<size_t>(n));
        size_t nl;
        while ((nl = pending.find('\n')) != std::string::npos)
        {
            lines.push_back(pending.substr(0, nl));
            pending.erase(0, nl + 1);
        }
    }
};

// Real frame rate. The watchdog hook runs once per frame from the render loop, so counting its calls is the
// frame rate the user sees. PS2 is 60 Hz (NTSC); "60 fps" means staying at that, and a menu that runs slower is
// either starved of guest time or the host is the bottleneck.
struct FpsMeter
{
    uint64_t frames = 0;
    double windowStart = 0.0;
    double lastFps = 0.0;
    double worstFps = 1e9;
    // The guest's own VSync tick is what paces the 3D scene: the host only presents a new frame when it changes,
    // so if it does not run at 60 Hz the whole screen refreshes at that lower rate (the FMV looks fine because
    // the movie path is not paced by it). Compared here against wall clock: 60.0 means the guest is real-time.
    uint64_t lastVtick = 0;
    double lastVHz = 0.0;

    void tick(double now, uint64_t vsyncTick)
    {
        if (windowStart == 0.0)
        {
            windowStart = now;
            lastVtick = vsyncTick;
        }
        ++frames;
        const double elapsed = now - windowStart;
        if (elapsed >= 2.0)
        {
            lastFps = frames / elapsed;
            lastVHz = static_cast<double>(vsyncTick - lastVtick) / elapsed;
            if (lastFps < worstFps)
                worstFps = lastFps;
            std::fprintf(stderr, "  [fps] %.1f (worst %.1f) | guest vsync %.1f Hz (target 60)\n", lastFps, worstFps,
                         lastVHz);
            std::fflush(stderr);
            frames = 0;
            lastVtick = vsyncTick;
            windowStart = now;
        }
    }
};

void saveDisplayPpm(PS2Runtime &rt, const std::string &path)
{
    const GSRegisters &regs = rt.memory().gs();
    const uint32_t fbp = static_cast<uint32_t>(regs.dispfb1 & 0x1FFu);
    const uint32_t fbw = std::max<uint32_t>(static_cast<uint32_t>((regs.dispfb1 >> 9) & 0x3Fu), 1u);
    const uint32_t psm = static_cast<uint32_t>((regs.dispfb1 >> 15) & 0x1Fu);
    const uint32_t w = fbw * 64u, h = 512u;
    FILE *f = std::fopen(path.c_str(), "wb");
    if (!f)
        return;
    std::fprintf(f, "P6\n%u %u\n255\n", w, h);
    for (uint32_t y = 0; y < h; ++y)
        for (uint32_t x = 0; x < w; ++x)
        {
            const uint32_t c = rt.gs().ReadVram(psm, fbp * 32u, fbw, x, y);
            uint8_t rgb[3];
            if (psm == 0x02u || psm == 0x0Au)
            {
                rgb[0] = static_cast<uint8_t>((c & 0x1Fu) << 3);
                rgb[1] = static_cast<uint8_t>(((c >> 5) & 0x1Fu) << 3);
                rgb[2] = static_cast<uint8_t>(((c >> 10) & 0x1Fu) << 3);
            }
            else
            {
                rgb[0] = static_cast<uint8_t>(c);
                rgb[1] = static_cast<uint8_t>(c >> 8);
                rgb[2] = static_cast<uint8_t>(c >> 16);
            }
            std::fwrite(rgb, 1, 3, f);
        }
    std::fclose(f);
    std::fprintf(stderr, "[control] saved %s\n", path.c_str());
}

// The state of the thread that is actually running. The thread dump in Watchdog::tick prints each thread's saved
// context, which for the running one is stale (the live one lives in EeScheduler::currentContext()), so a freeze
// of the game is invisible there: the EE cycle counter stops, or $sp walks down without bound because a recursion
// is overflowing the stack into the heap. This prints the live registers every tick, and on either symptom dumps
// the guest stack around $sp (the words that fall in the code range are the saved return addresses).
struct LiveWatch
{
    uint64_t lastCycle = 0;
    int sameCycle = 0;
    uint32_t lastSp = 0;
    int spDown = 0;
    bool dumpedCycle = false;
    bool dumpedSp = false;

    // Guest RAM at its own host addresses (identity mode); the low 64 KB lives in the shadow (ps2_identity.h).
    static uint32_t guestWord(uint32_t addr)
    {
        addr &= 0x1FFFFFFCu;
        if (addr < kPs2LowShadowSize)
        {
            uint32_t v;
            std::memcpy(&v, g_ps2LowShadow + addr, sizeof(v));
            return v;
        }
        if (addr >= PS2_RAM_SIZE)
            return 0u;
        uint32_t v;
        std::memcpy(&v, reinterpret_cast<const void *>(static_cast<uintptr_t>(addr)), sizeof(v));
        return v;
    }

    static bool looksLikeCode(uint32_t w) { return w >= 0x00100000u && w < 0x00400000u; }

    void dumpStack(R5900Context *live, const char *why)
    {
        const uint32_t sp = getRegU32(live, 29);
        std::fprintf(stderr, "  [live %s] stack from sp %08x:\n", why, sp);
        for (uint32_t off = 0; off < 0x400u; off += 0x20u)
        {
            std::fprintf(stderr, "    sp+%03x:", off);
            for (uint32_t i = 0; i < 8; ++i)
            {
                const uint32_t w = guestWord(sp + off + 4u * i);
                std::fprintf(stderr, " %08x%s", w, looksLikeCode(w) ? "*" : " ");
            }
            std::fprintf(stderr, "\n");
        }
        std::fflush(stderr);
    }

    void tick(PS2Runtime &rt, uint64_t cycle)
    {
        R5900Context *live = rt.eeScheduler().currentContext();
        if (live == nullptr)
            return;
        const uint32_t pc = live->pc, ra = getRegU32(live, 31), sp = getRegU32(live, 29);
        std::fprintf(stderr, "  [live] pc %08x ra %08x sp %08x gp %08x a0 %08x a1 %08x a2 %08x a3 %08x\n", pc, ra, sp,
                     getRegU32(live, 28), getRegU32(live, 4), getRegU32(live, 5), getRegU32(live, 6),
                     getRegU32(live, 7));

        if (cycle == lastCycle)
            ++sameCycle;
        else
            sameCycle = 0;
        lastCycle = cycle;

        if (sp < lastSp)
            ++spDown;
        else if (sp > lastSp + 0x100u)
            spDown = 0;
        lastSp = sp;

        if (sameCycle >= 2 && !dumpedCycle)
        {
            dumpedCycle = true;
            std::fprintf(stderr, "  [live] EE CYCLE COUNTER FROZEN at %llu for %d ticks\n",
                         static_cast<unsigned long long>(cycle), sameCycle);
            dumpStack(live, "frozen cycle");
        }
        if (spDown >= 3 && !dumpedSp)
        {
            dumpedSp = true;
            std::fprintf(stderr, "  [live] $sp WALKING DOWN for %d ticks (runaway recursion?)\n", spDown);
            dumpStack(live, "sp down");
        }
    }
};

struct Watchdog
{
    InputScript input;
    ControlPipe control;
    LiveWatch live;
    FpsMeter fps;
    double period = 5.0;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point last = start;

    void tick(PS2Runtime &rt)
    {
        const auto now = std::chrono::steady_clock::now();
        const double guestTime = static_cast<double>(rt.eeScheduler().currentVSyncTick()) / 60.0;
        control.poll();
        for (const std::string &line : control.lines)
        {
            if (line.rfind("shot ", 0) == 0)
                saveDisplayPpm(rt, line.substr(5));
            else if (buttonBit(line) != 0u)
                input.presses.emplace_back(guestTime, buttonBit(line));
        }
        control.lines.clear();
        // The scripted pad advances from the guest's pad reads (inputOnPadRead), not from here: driven by the
        // present it landed a whole frame late, or got skipped, whenever the host presented slowly.
        if (period <= 0.0)
            return;
        if (std::chrono::duration<double>(now - last).count() < period)
            return;
        last = now;
        const EeKernelSnapshot s = rt.eeScheduler().snapshot();
        std::fprintf(stderr, "[watch %.0fs] cycle %llu running %d\n",
                     std::chrono::duration<double>(now - start).count(),
                     static_cast<unsigned long long>(s.eeCycle), s.runningThreadId);
        for (const auto &t : s.threads)
            std::fprintf(stderr, "  thread %2d %-8s %-8s obj %3d pc %08x ra %08x entry %08x prio %d\n", t.id,
                         statusName(t.status), waitName(t.waitReason), t.waitId, t.pc, t.ra, t.entry,
                         t.currentPriority);
        for (const auto &m : s.semaphores)
            std::fprintf(stderr, "  sema %3d count %d/%d waiters %u\n", m.id, m.count, m.maxCount, m.waiters);
        // Video output: what the game programmed into the GS (PMODE/DISPFB/DISPLAY) and whether the runtime has
        // a frame to present. All zero = the game has not set up the display yet.
        const GSRegisters &regs = rt.memory().gs();
        const GSDebugSnapshot gs = rt.gs().getDebugSnapshot();
        std::fprintf(stderr, "  gs pmode %llx dispfb1 %llx display1 %llx dispfb2 %llx display2 %llx | present %s %ux%u fbp %x | "
                             "uploads %llu packed %llu\n",
                     (unsigned long long)regs.pmode, (unsigned long long)regs.dispfb1,
                     (unsigned long long)regs.display1, (unsigned long long)regs.dispfb2,
                     (unsigned long long)regs.display2, gs.hasHostPresentationFrame ? "yes" : "no",
                     gs.hostPresentationWidth, gs.hostPresentationHeight, gs.hostPresentationDisplayFbp,
                     (unsigned long long)rt.gs().nativeImageUploadCount(),
                     (unsigned long long)rt.gs().nativePackedGIFPacketCount());
        // Non-zero 32-bit words in GS VRAM, overall and in the displayed buffer (DISPFB1.FBP, 640x512 PSMCT32):
        // tells "nothing drawn" from "drawn but not presented".
        const uint8_t *vram = rt.memory().getGSVRAM();
        const uint32_t fbBase = static_cast<uint32_t>(regs.dispfb1 & 0x1FFu) * 2048u * 4u;
        size_t vramWords = 0, fbWords = 0;
        for (size_t i = 0; i < PS2_GS_VRAM_SIZE; i += 4)
        {
            const bool nz = (vram[i] | vram[i + 1] | vram[i + 2] | vram[i + 3]) != 0;
            vramWords += nz;
            fbWords += nz && i >= fbBase && i < fbBase + 640u * 512u * 4u;
        }
        std::fprintf(stderr, "  vram non-zero words %zu, in display buffer %zu; dma kicks %llu\n", vramWords, fbWords,
                     static_cast<unsigned long long>(rt.memory().dmaStartCount()));
        // Which 256 KB pages of VRAM hold data (FBP units of 8 KB: page n covers FBP n*32 .. n*32+31).
        std::fprintf(stderr, "  vram pages:");
        for (size_t page = 0; page < PS2_GS_VRAM_SIZE / 0x40000u; ++page)
        {
            size_t nz = 0;
            for (size_t i = page * 0x40000u; i < (page + 1) * 0x40000u; i += 4)
                nz += (vram[i] | vram[i + 1] | vram[i + 2] | vram[i + 3]) != 0;
            std::fprintf(stderr, " %zu", nz);
        }
        std::fprintf(stderr, "\n");
        // BT2_SHOT=<prefix>: save the render target (FRAME of context 1) and the displayed buffer (DISPFB1) as PPM.
        if (const char *prefix = std::getenv("BT2_SHOT"))
        {
            const auto save = [&](const char *tag, uint32_t fbp, uint32_t fbw, uint32_t psm, uint32_t w, uint32_t h)
            {
                char name[512];
                std::snprintf(name, sizeof(name), "%s_%s_%03.0f.ppm", prefix, tag,
                              std::chrono::duration<double>(now - start).count());
                if (FILE *f = std::fopen(name, "wb"))
                {
                    std::fprintf(f, "P6\n%u %u\n255\n", w, h);
                    for (uint32_t y = 0; y < h; ++y)
                        for (uint32_t x = 0; x < w; ++x)
                        {
                            uint32_t c = rt.gs().ReadVram(psm, fbp * 32u, fbw, x, y);
                            uint8_t rgb[3];
                            if (psm == 0x02u || psm == 0x0Au) // 16-bit: 5:5:5
                            {
                                rgb[0] = static_cast<uint8_t>((c & 0x1Fu) << 3);
                                rgb[1] = static_cast<uint8_t>(((c >> 5) & 0x1Fu) << 3);
                                rgb[2] = static_cast<uint8_t>(((c >> 10) & 0x1Fu) << 3);
                            }
                            else
                            {
                                rgb[0] = static_cast<uint8_t>(c);
                                rgb[1] = static_cast<uint8_t>(c >> 8);
                                rgb[2] = static_cast<uint8_t>(c >> 16);
                            }
                            std::fwrite(rgb, 1, 3, f);
                        }
                    std::fclose(f);
                }
            };
            save("frame", gs.ctx[0].frame.fbp, std::max<uint32_t>(gs.ctx[0].frame.fbw, 1u), gs.ctx[0].frame.psm,
                 std::max<uint32_t>(gs.ctx[0].frame.fbw, 1u) * 64u, 512u);
            save("display", static_cast<uint32_t>(regs.dispfb1 & 0x1FFu), static_cast<uint32_t>((regs.dispfb1 >> 9) & 0x3Fu),
                 static_cast<uint32_t>((regs.dispfb1 >> 15) & 0x1Fu),
                 std::max<uint32_t>(static_cast<uint32_t>((regs.dispfb1 >> 9) & 0x3Fu), 1u) * 64u, 448u);
        }
        std::fprintf(stderr, "  gs packets %llu reg writes %llu draw kicks %llu\n",
                     (unsigned long long)rt.gs().gifPacketCount(), (unsigned long long)rt.gs().registerWriteCount(),
                     (unsigned long long)rt.gs().drawKickCount());
        std::fprintf(stderr, "  gs ctx0 frame fbp %x fbw %u psm %x | zbuf zbp %x | ctx1 frame fbp %x | vram[0] %08x vram[0x80000] %08x\n",
                     gs.ctx[0].frame.fbp, gs.ctx[0].frame.fbw, gs.ctx[0].frame.psm, gs.ctx[0].zbuf.zbp, gs.ctx[1].frame.fbp,
                     *reinterpret_cast<const uint32_t *>(vram), *reinterpret_cast<const uint32_t *>(vram + 0x80000));
        colTraceStats();
        callCountReport();
        if (const char *sd = std::getenv("BT2_SCHED_TRACE"))
        {
            if (sd[0] != '0')
            {
                const EeScheduler::ScheduleDebug d = rt.eeScheduler().scheduleDebug();
                std::fprintf(stderr,
                             "  [sched] cyc %llu sliceEnds %llu cur %d resched %d sliceExp %d | disp %llu ckpt %llu "
                             "slices %llu switches %llu | ready front %d used %u | perThread",
                             static_cast<unsigned long long>(d.eeCycle),
                             static_cast<unsigned long long>(d.sliceEndCycle), d.currentThreadId, d.rescheduleRequested,
                             d.timeSliceExpired, static_cast<unsigned long long>(d.dispatches),
                             static_cast<unsigned long long>(d.checkpointsTrue),
                             static_cast<unsigned long long>(d.slicesExpired), static_cast<unsigned long long>(d.switches),
                             d.readyFrontPriority, d.readyQueuesUsed);
                for (int i = 0; i < 8; ++i)
                    std::fprintf(stderr, " t%d=%llu", i, static_cast<unsigned long long>(d.selectPerThread[i]));
                std::fprintf(stderr, "\n");
            }
        }
        guestWatchTick(rt);
        storeWatchSetLiveContext(rt.eeScheduler().currentContext());
        live.tick(rt, s.eeCycle);
        fps.tick(std::chrono::duration<double>(now - start).count(), rt.eeScheduler().currentVSyncTick());
        std::fflush(stderr);
    }
};
} // namespace

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "usage: " << argv[0] << " path/to/SLUS_214.41 [disc.iso]  (ELF in a folder with the whole disc)\n";
        return 2;
    }
    const std::filesystem::path elf = argv[1];

    Watchdog watchdog;
    if (const char *w = std::getenv("BT2_WATCH"))
        watchdog.period = std::atof(w);
    if (const char *in = std::getenv("BT2_INPUT"))
        watchdog.input.parse(in);
    if (const char *ctl = std::getenv("BT2_CONTROL"))
        watchdog.control.open(ctl);

    try
    {
        PS2Runtime runtime;
        // The draw hook only runs once an init hook has run, so pass an empty one.
        runtime.setDebugUiCallbacks(
            [](PS2Runtime &, void *) {},
            [](PS2Runtime &rt, void *user) { static_cast<Watchdog *>(user)->tick(rt); },
            nullptr, &watchdog);
        if (!runtime.initialize("Dragon Ball Z: Budokai Tenkaichi 2 (native)"))
        {
            std::cerr << "runtime initialisation failed\n";
            return 1;
        }
        if (!runtime.loadELF(elf.string()))
        {
            std::cerr << "cannot load " << elf << "\n";
            return 1;
        }
        installMovieHle(runtime);
        installIdentityHle(runtime);
        // The scripted pad (BT2_INPUT) advances from the guest's own pad reads so a press is not tied to the
        // host's frame rate.
        g_inputScript = &watchdog.input;
        g_inputRuntime = &runtime;
        ps2_stubs::ps2PadReadHook = inputOnPadRead;
        // Before the natives: a native C function installed below wins over a trace wrapper at the same address.
        installColTrace(runtime);
        installCallCounters(runtime);
        installGuestWatch(runtime);
        installStoreWatch(runtime);
#ifdef BT2_HAVE_NATIVE
        // Native C needs guest RAM at its own addresses (the game's pointers are used as host pointers).
        // BT2_NATIVE=1 turns them on; unset or 0 keeps every function recompiled.
        const char *nat = std::getenv("BT2_NATIVE");
        const char *ident = std::getenv("PS2X_IDENTITY_RDRAM");
        if (nat && nat[0] == '1' && ident && ident[0] == '1')
            std::fprintf(stderr, "[native] %d functions run as native C\n", installNativeFunctions(runtime));
        else
            std::fprintf(stderr, "[native] off (BT2_NATIVE=1 with PS2X_IDENTITY_RDRAM=1 turns it on)\n");
#endif
        if (argc > 2)
        {
            PS2Runtime::IoPaths paths = PS2Runtime::getIoPaths();
            paths.cdImage = std::filesystem::absolute(argv[2]);
            PS2Runtime::setIoPaths(paths);
        }
        runtime.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "[main] fatal exception: " << e.what() << std::endl;
        std::cout.flush();
        std::_Exit(1);
    }
    std::cout.flush();
    std::cerr.flush();
    std::_Exit(0);
}
