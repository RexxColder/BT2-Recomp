// BT2 port: trace of the collision BVH walk that stalls the attract demo (~500 s of guest time).
//
// The walk is ColMesh_CollectNode (0x28D990) / ColMesh_WalkNode (0x28DAA8): node = base + idx*32, the box test is
// ColNode_TestBox (0x28D968), the leaf test is ColNode_IsLeaf (0x28D260, "node->0x1C == -1") and the children are
// the words at +0x18/+0x1C. In the demo it never returns: the guest $sp grows 0x20 per level until it lands in the
// heap (it is what corrupts gBtlStage+0x5C), then func_002748B8 spins on that pointer.
//
// The self-recursion is compiled by PS2Recomp as a `goto label_28daa8` inside the same C++ function (it is a `jal`
// to its own address), so neither a breakpoint nor a replaced function can see the re-entry: the C++ frame never
// grows. What does go through the runtime's function table is the call to ColNode_IsLeaf/ColNode_TestBox at every
// node, and that is enough to rebuild the whole traversal from here.
//
// On: BT2_COL_TRACE=1 (summaries + abort on the first cycle), =2 (every visited node as well),
//     BT2_COL_MAXNODES=<n> visit cap per walk before giving up on a cycle (default 200000),
//     BT2_COL_REPORT=<n> print a walk's summary when it visits at least <n> nodes (default 2000).

#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"
#include <ps2_recompiled_functions.h>

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unordered_map>
#include <vector>

namespace
{
constexpr uint32_t kIsLeafPc = 0x0028D260u;      // ColNode_IsLeaf(node)
constexpr uint32_t kTestBoxPc = 0x0028D968u;     // ColNode_TestBox(box, node)
constexpr uint32_t kCollectNodePc = 0x0028D990u; // ColMesh_CollectNode(base, a1, idx), recurses in place
constexpr uint32_t kCollectBoxPc = 0x0028DA48u;  // ColMesh_CollectBox(max, buf, box, a3)
constexpr uint32_t kWalkNodePc = 0x0028DAA8u;    // ColMesh_WalkNode(base, a1, idx), recurses in place

struct Visit
{
    uint32_t node;
    uint32_t child18;
    uint32_t child1C;
    uint32_t depth;
    uint32_t sp;
};

struct Trace
{
    bool on = false;
    int verbose = 1;
    unsigned maxVisits = 200000;
    unsigned reportNodes = 2000;

    bool inWalk = false;
    uint32_t base = 0;
    uint32_t sp0 = 0;
    uint32_t box = 0;
    uint32_t which = 0;
    unsigned maxDepth = 0;
    std::unordered_map<uint32_t, uint32_t> firstVisit;
    std::vector<Visit> visits;

    unsigned long long walks = 0;
    unsigned worstVisits = 0;
    unsigned worstDepth = 0;
};

Trace g_t;

void colInit()
{
    if (g_t.on || g_t.verbose == -1)
        return;
    const char *e = std::getenv("BT2_COL_TRACE");
    g_t.on = (e != nullptr && e[0] != '\0' && e[0] != '0');
    g_t.verbose = (e != nullptr && e[1] >= '2') ? 2 : 1;
    const char *m = std::getenv("BT2_COL_MAXNODES");
    if (m != nullptr)
        g_t.maxVisits = static_cast<unsigned>(std::atoi(m));
    const char *r = std::getenv("BT2_COL_REPORT");
    if (r != nullptr)
        g_t.reportNodes = static_cast<unsigned>(std::atoi(r));
}

void colPrintVisits(size_t from, size_t to)
{
    for (size_t i = from; i < to && i < g_t.visits.size(); ++i)
    {
        const Visit &v = g_t.visits[i];
        std::fprintf(stderr, "[col]   %5zu node %08x  +0x18 %10d  +0x1C %10d  depth %u  sp %08x\n", i, v.node,
                     static_cast<int>(v.child18), static_cast<int>(v.child1C), v.depth, v.sp);
    }
}

// The walk never returns: report what the traversal looked like and stop, so the run does not have to reach the
// 500 s stall and a core lands with everything already printed.
[[noreturn]] void colGiveUp(const char *why, uint32_t node, uint32_t firstIndex, uint32_t sp)
{
    std::fprintf(stderr, "[col] GIVE UP: %s\n", why);
    std::fprintf(stderr, "[col] walk pc %08x base %08x box %08x visits %zu maxDepth %u sp0 %08x sp %08x\n", g_t.which,
                 g_t.base, g_t.box, g_t.visits.size(), g_t.maxDepth, g_t.sp0, sp);
    if (node != 0)
    {
        const size_t at = firstIndex < g_t.visits.size() ? firstIndex : g_t.visits.size();
        const size_t from = at > 40 ? at - 40 : 0;
        std::fprintf(stderr, "[col] node %08x was first visited at #%u; the last visits (repeat marked *):\n", node,
                     firstIndex);
        colPrintVisits(from, g_t.visits.size());
        for (size_t i = 0; i < g_t.visits.size(); ++i)
            if (g_t.visits[i].node == node)
                std::fprintf(stderr, "[col] * #%zu node %08x again (first at #%u)\n", i, node, firstIndex);
    }
    std::fflush(stderr);
    std::abort();
}

void colNoteNode(uint32_t node, uint32_t child18, uint32_t child1C, uint32_t sp)
{
    if (!g_t.inWalk)
        return;
    const auto it = g_t.firstVisit.find(node);
    if (it != g_t.firstVisit.end())
    {
        g_t.visits.push_back({node, child18, child1C, static_cast<uint32_t>(g_t.visits.size()), sp});
        colGiveUp("node visited twice in the same walk (the tree has a cycle)", node, it->second, sp);
    }
    const uint32_t depth = (g_t.sp0 - sp) / 0x20u;
    if (depth > g_t.maxDepth)
        g_t.maxDepth = depth;
    g_t.firstVisit.emplace(node, static_cast<uint32_t>(g_t.visits.size()));
    g_t.visits.push_back({node, child18, child1C, depth, sp});
    if (g_t.verbose >= 2)
    {
        std::fprintf(stderr, "[col]  visit %zu node %08x +0x18 %d +0x1C %d depth %u sp %08x\n", g_t.visits.size() - 1,
                     node, static_cast<int>(child18), static_cast<int>(child1C), depth, sp);
    }
    if (g_t.visits.size() > g_t.maxVisits)
        colGiveUp("too many visits with no repeated node (a shared subtree, not a cycle)", 0, 0, sp);
}

void colWalkBegin(uint32_t which, uint32_t base, uint32_t sp)
{
    g_t.which = which;
    g_t.base = base;
    g_t.sp0 = sp;
    g_t.maxDepth = 0;
    g_t.firstVisit.clear();
    g_t.visits.clear();
}

void colWalkEnd(uint32_t sp)
{
    const unsigned visits = static_cast<unsigned>(g_t.visits.size());
    g_t.maxDepth = (g_t.sp0 - sp) / 0x20u;
    ++g_t.walks;
    if (visits > g_t.worstVisits)
        g_t.worstVisits = visits;
    if (g_t.maxDepth > g_t.worstDepth)
        g_t.worstDepth = g_t.maxDepth;
    if (g_t.verbose >= 2 || visits >= g_t.reportNodes)
    {
        std::fprintf(stderr, "[col] walk #%llu pc %08x base %08x box %08x visits %u depth %u sp %08x\n", g_t.walks,
                     g_t.which, g_t.base, g_t.box, visits, g_t.maxDepth, sp);
        std::fflush(stderr);
    }
}

// ---- the replaced functions ---------------------------------------------------------------------------

void colIsLeaf(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
{
    if (g_t.on)
    {
        const uint32_t node = getRegU32(ctx, 4);
        // Read the fields before the call: the walk may change them.
        const uint32_t child18 = READ32(node + 0x18u);
        const uint32_t child1C = READ32(node + 0x1Cu);
        colNoteNode(node, child18, child1C, getRegU32(ctx, 29));
    }
    func_0028D260_0x28d260(rdram, ctx, runtime);
}

void colTestBox(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
{
    func_0028D968_0x28d968(rdram, ctx, runtime);
}

void colCollectNode(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
{
    const bool outer = !g_t.inWalk;
    if (outer)
    {
        colWalkBegin(kCollectNodePc, getRegU32(ctx, 4), getRegU32(ctx, 29));
        g_t.inWalk = true;
    }
    func_0028D990_0x28d990(rdram, ctx, runtime);
    if (outer)
    {
        g_t.inWalk = false;
        colWalkEnd(getRegU32(ctx, 29));
    }
}

void colWalkNode(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
{
    const bool outer = !g_t.inWalk;
    if (outer)
    {
        colWalkBegin(kWalkNodePc, getRegU32(ctx, 4), getRegU32(ctx, 29));
        g_t.inWalk = true;
    }
    func_0028DAA8_0x28daa8(rdram, ctx, runtime);
    if (outer)
    {
        g_t.inWalk = false;
        colWalkEnd(getRegU32(ctx, 29));
    }
}

// The box that starts the walk: which collision shape, and the node array it indexes into.
void colCollectBox(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
{
    if (g_t.on)
    {
        const uint32_t box = getRegU32(ctx, 6);
        const int32_t mesh = static_cast<int32_t>(READ32(box + 0xCu));
        // gColMeshBase is a gp-relative word (-0x4080): the node array the walk indexes with base + mesh*4.
        const uint32_t meshBase = READ32(ADD32(GPR_U32(ctx, 28), 0xFFFFBF80u)); // gColMeshBase = gp-0x4080
        g_t.box = box;
        std::fprintf(stderr, "[col] CollectBox box %08x count %d mesh %d meshBase %08x -> walk base %08x\n", box,
                     static_cast<int>(READ32(box + 0x0u)), mesh, meshBase, meshBase + 4u * static_cast<uint32_t>(mesh));
    }
    func_0028DA48_0x28da48(rdram, ctx, runtime);
}
} // namespace

int installColTrace(PS2Runtime &runtime)
{
    colInit();
    if (!g_t.on)
        return 0;
    int n = 0;
    // Before installNativeFunctions(): a native C function installed later wins over these wrappers.
    n += runtime.replaceFunction(kIsLeafPc, colIsLeaf) ? 1 : 0;
    n += runtime.replaceFunction(kTestBoxPc, colTestBox) ? 1 : 0;
    n += runtime.replaceFunction(kCollectNodePc, colCollectNode) ? 1 : 0;
    n += runtime.replaceFunction(kWalkNodePc, colWalkNode) ? 1 : 0;
    n += runtime.replaceFunction(kCollectBoxPc, colCollectBox) ? 1 : 0;
    std::fprintf(stderr, "[col] trace on: %d functions wrapped, report from %u nodes, cap %u (verbose %d)\n", n,
                 g_t.reportNodes, g_t.maxVisits, g_t.verbose);
    return n;
}

void colTraceStats()
{
    if (!g_t.on)
        return;
    std::fprintf(stderr, "[col] walks %llu worst visits %u worst depth %u\n", g_t.walks, g_t.worstVisits,
                 g_t.worstDepth);
    std::fflush(stderr);
}