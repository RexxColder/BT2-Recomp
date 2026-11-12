// Intro/ending movies: HLE of the game's player func_0024BA78(const char *name), called for "logo_o.sfd" (from the
// overlay), "zs2usop.sfd" and "zs2used.sfd". The original drives CRI Sofdec, which decodes MPEG-2 with the IPU; the
// runtime's IPU is a stub. The .SFD files are MPEG program streams (mpeg2video 512x448 + adpcm_adx) that FFmpeg
// reads as they are, so the movie is decoded on the host and written to GS VRAM, one frame per call.
//
// One frame per call: a host loop cannot wait for a VBlank (EeScheduler waits throw and resume the guest thread at
// ctx->pc). Each call shows the next frame, points ctx->pc back at 0x24BA78 and waits two VBlanks (NTSC 59.94 Hz for
// 29.97 fps), so the next call is the next frame; at the end it returns to $ra like the original.
//
// Start or Cross (gamepad, keyboard or scripted input) skips the movie, as on the console.
//
// Environment: BT2_SKIP_MOVIES=1   return at once (as if the player had been skipped)
//              BT2_MOVIE_DIR=<dir> where the .SFD files are (default gamedata/DATA)
#include "ps2_runtime.h"
#include "runtime/ee_scheduler.h"
#include "runtime/ps2_pad.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

extern uint16_t g_bt2ScriptedButtons; // main.cpp

namespace
{
constexpr uint32_t kPlayerAddress = 0x24BA78u;
constexpr uint32_t kWidth = 512u, kHeight = 448u;

struct Movie
{
    AVFormatContext *format = nullptr;
    AVCodecContext *codec = nullptr;
    SwsContext *scale = nullptr;
    AVPacket *packet = nullptr;
    AVFrame *frame = nullptr;
    int stream = -1;
    std::vector<uint8_t> rgba;
    uint32_t frames = 0;
};

Movie *g_movie = nullptr;

void closeMovie()
{
    if (!g_movie)
        return;
    sws_freeContext(g_movie->scale);
    av_frame_free(&g_movie->frame);
    av_packet_free(&g_movie->packet);
    avcodec_free_context(&g_movie->codec);
    avformat_close_input(&g_movie->format);
    std::fprintf(stderr, "[movie] done, %u frames\n", g_movie->frames);
    delete g_movie;
    g_movie = nullptr;
}

bool openMovie(const std::string &path)
{
    auto *m = new Movie();
    g_movie = m;
    if (avformat_open_input(&m->format, path.c_str(), nullptr, nullptr) < 0 ||
        avformat_find_stream_info(m->format, nullptr) < 0)
        return false;
    m->stream = av_find_best_stream(m->format, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    if (m->stream < 0)
        return false;
    const AVCodecParameters *par = m->format->streams[m->stream]->codecpar;
    const AVCodec *decoder = avcodec_find_decoder(par->codec_id);
    m->codec = decoder ? avcodec_alloc_context3(decoder) : nullptr;
    if (!m->codec || avcodec_parameters_to_context(m->codec, par) < 0 || avcodec_open2(m->codec, decoder, nullptr) < 0)
        return false;
    m->packet = av_packet_alloc();
    m->frame = av_frame_alloc();
    m->rgba.resize(kWidth * kHeight * 4u);
    std::fprintf(stderr, "[movie] playing %s (%dx%d)\n", path.c_str(), par->width, par->height);
    return true;
}

// Decodes the next video frame into g_movie->rgba (512x448 RGBA). False at the end of the stream.
bool nextFrame()
{
    Movie &m = *g_movie;
    for (;;)
    {
        const int got = avcodec_receive_frame(m.codec, m.frame);
        if (got == 0)
        {
            m.scale = sws_getCachedContext(m.scale, m.frame->width, m.frame->height,
                                           static_cast<AVPixelFormat>(m.frame->format), kWidth, kHeight,
                                           AV_PIX_FMT_RGBA, SWS_BILINEAR, nullptr, nullptr, nullptr);
            uint8_t *dst[1] = {m.rgba.data()};
            const int dstStride[1] = {static_cast<int>(kWidth * 4u)};
            sws_scale(m.scale, m.frame->data, m.frame->linesize, 0, m.frame->height, dst, dstStride);
            ++m.frames;
            return true;
        }
        if (got == AVERROR_EOF)
            return false;
        if (av_read_frame(m.format, m.packet) < 0)
        {
            avcodec_send_packet(m.codec, nullptr); // drain
            continue;
        }
        if (m.packet->stream_index == m.stream)
            avcodec_send_packet(m.codec, m.packet);
        av_packet_unref(m.packet);
    }
}

// Frame buffer at FBP 0 (PSMCT32, FBW 8 = 512 pixels) shown on CRT1 at 512x448.
void showFrame(PS2Runtime *runtime)
{
    GS &gs = runtime->gs();
    const uint8_t *p = g_movie->rgba.data();
    for (uint32_t y = 0; y < kHeight; ++y)
        for (uint32_t x = 0; x < kWidth; ++x, p += 4)
            gs.WriteVram(0u, 0u, kWidth / 64u, x, y,
                         p[0] | (p[1] << 8) | (p[2] << 16) | (0x80u << 24));
    PS2Memory &mem = runtime->memory();
    mem.write64(0x12000000u, 0xFF25u);                // PMODE: CRT1 on, ALP 0xFF
    mem.write64(0x12000070u, (kWidth / 64u) << 9);   // DISPFB1: FBP 0, FBW 8, PSMCT32
    mem.write64(0x12000080u, 636ull | (50ull << 12) | (4ull << 23) |
                                 (static_cast<uint64_t>(kWidth * 5u - 1u) << 32) |
                                 (static_cast<uint64_t>(kHeight - 1u) << 44)); // DISPLAY1: MAGH 4 -> 512 wide
}

std::string moviePath(uint8_t *rdram, uint32_t nameAddr)
{
    const char *dir = std::getenv("BT2_MOVIE_DIR");
    std::string path = dir ? dir : "gamedata/DATA";
    path += '/';
    for (uint32_t a = nameAddr & 0x1FFFFFFu; rdram[a] && path.size() < 512u; ++a)
        path += static_cast<char>(std::toupper(rdram[a]));
    return path;
}

void returnToCaller(R5900Context *ctx)
{
    setReturnS32(ctx, 0);
    ctx->pc = getRegU32(ctx, 31);
}

bool skipPressed(PS2Runtime *runtime)
{
    constexpr uint16_t kSkip = (1u << 3) | (1u << 14); // Start, Cross
    uint8_t data[32]{};
    const uint16_t held = runtime->padBackend().readState(0, 0, data, sizeof(data))
                              ? static_cast<uint16_t>(~(data[2] | (data[3] << 8)))
                              : 0u;
    return ((held | g_bt2ScriptedButtons) & kSkip) != 0u;
}

void playMovie(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
{
    if (!g_movie)
    {
        static const bool skip = std::getenv("BT2_SKIP_MOVIES") != nullptr;
        const std::string path = moviePath(rdram, getRegU32(ctx, 4));
        if (skip || !openMovie(path))
        {
            std::fprintf(stderr, "[movie] %s %s\n", skip ? "skipped" : "cannot open", path.c_str());
            closeMovie();
            returnToCaller(ctx);
            return;
        }
    }
    if (g_movie->frames > 15u && skipPressed(runtime))
        std::fprintf(stderr, "[movie] skipped by the player\n");
    if ((g_movie->frames > 15u && skipPressed(runtime)) || !nextFrame())
    {
        closeMovie();
        returnToCaller(ctx);
        return;
    }
    showFrame(runtime);
    // Come back here for the next frame after two VBlanks; the wait does not return (see the top of the file).
    ctx->pc = kPlayerAddress;
    EeScheduler &ee = runtime->eeScheduler();
    ee.bindMainContextForSyscall(*ctx, rdram);
    ee.waitVSync(ee.currentVSyncTick() + 1u, 0);
}
} // namespace

void installMovieHle(PS2Runtime &runtime)
{
    runtime.replaceFunction(kPlayerAddress, playMovie);
}
