#define BtlObj_RebuildTable func_002EC478  /* fix_targets */ /* the original uses 0x2ec478 here */
#define Dbg_BeginFrame func_002ED118  /* fix_targets */ /* the original uses 0x2ed118 here */
#define Fade_UpdateAll func_002ED130  /* fix_targets */ /* the original uses 0x2ed130 here */
#include "common.h"
#include "sys/gfx.h"
#include "sys/debug.h"
#include "sys/file.h"
#include "sys/save.h"

/*
 * Graphics core (0x101D40..0x102458): GS set-up, frame begin/end, default draw state.
 * The ordering table for sorted primitives that follows it is src/sys/gfx_ot.c.
 *
 * What a renderer on another platform needs to know
 * -------------------------------------------------
 * Frame buffers (Gfx_InitDrawEnv, verified by the matching code):
 *   - Two 512x448 PSMCT32 colour buffers at GS pages 0x00 (A) and 0x70 (B), buffer width 8 (x64 pixels),
 *     and one PSMZ24 depth buffer at page 0xE0 shared by both. Bigger Z is nearer: the clear writes
 *     Z = 0, the libgraph draw env is created with ztest 3 (GREATER) and Gfx_PutDefaultEnv sets TEST to
 *     0x50000 (depth test on, GEQUAL).
 *   - Primitive coordinates are offset by XYOFFSET (1792, 1824) = (2048 - 256, 2048 - 224), so the screen is
 *     x 1792..2303, y 1824..2271 in GS units/16. Dma_AddFillRect and friends add these themselves.
 *   - The mode is NTSC interlaced, field mode (sceGsResetGraph(0, 1, 2, 0)): all 448 lines are stored and
 *     the GS shows alternate lines each field. There is no half-pixel field offset anywhere in this code;
 *     the same full-height picture is simply displayed for however many fields a frame lasts.
 *   - Display (Gfx_SetDisplayRegs): both read circuits show the same buffer with MAGH = 5 (512 -> 2560 VCK
 *     units, i.e. the 512-pixel picture is stretched to the full 640-wide area), DW = 2560, DH = 448.
 *     DX = 636 + 4 * screenX, DY = 50 + 2 * screenY for circuit 2 and one line lower for circuit 1; PMODE
 *     blends the two circuits 50/50 (ALP 0x7F), which is a vertical flicker filter. With blend == 0 ALP is
 *     0xFF (circuit 1 only); Gfx_EndFrame always passes 1. A port can ignore the filter and should apply
 *     screenX/screenY as a picture offset of (screenX, screenY) pixels at most (4 VCK = 0.8 buffer pixel).
 *
 * Buffer selection: everything keys off bit 0 of gGfx.frame, the count of ended frames.
 *   - Display lists built while the counter is c draw into page (c odd ? 0x00 : 0x70) (Gfx_PutDefaultEnv,
 *     Gfx_ClearScreen, Ot_AddEnv, Dma users elsewhere).
 *   - Gfx_SetDisplayRegs shows that same page while the counter is c. The main loops call Gfx_EndFrame and
 *     only then Dma_Flush, so the list built during c is drawn while c + 1 is on screen: ordinary double
 *     buffering, with the picture appearing one frame after it was built.
 *
 * func_002EC450, in order: Dbg_BeginFrame (empty), 0x248F38 (rebuilds the 12-entry battle object table when
 * the battle is up), Fade_UpdateAll (advances the 3 screen fades).
 *
 * Gfx_EndFrame(vsyncs), in order:
 *   1. Fade_DrawScreen: queues the fade rectangles of slots 0 and 1 on top of everything.
 *   2. 0x23D160(vsyncs): frame counters at gp 0x2FEBC4/0x2FEBC8 (with vsyncs == 1 the first only counts every
 *      other call, i.e. it counts 1/30 s units).
 *   3. 0x267DC0, 0x268208: per-frame services (two-entry state polled through 0x267B90; not looked into).
 *   4. Dbg_ProfColor / Dbg_EndFrame (debug, empty), 0x121DE0 (identity matrix check + 0x120B48).
 *   5. sceGsSyncPath(0, 0): waits until the GS finished the list sent by the previous frame's Dma_Flush.
 *   6. Vsync_Wait(vsyncs): waits until `vsyncs` vertical blanks passed since the last frame (1 = 60 fps,
 *      2 = 30 fps) and resets the counter.
 *   7. gGfx.frame++, gGfx.field ^= 1.
 *   8. sceGsSwapDBuff(&gGfx.db, frame): writes disp[frame & 1] and sends draw env + clear of buffer
 *      (frame odd ? B : A), i.e. the buffer the list about to be flushed draws into: it is cleared to
 *      black with alpha 0 and Z 0 here, before that list runs.
 *   9. Gfx_SetDisplayRegs(field, 1): overrides the display registers (shows the other buffer, see above).
 *  10. sceGsSyncPath(0, 0): waits for the clear.
 * The caller then calls Dma_Flush, which sends the frame's list and swaps the two list buffers.
 *
 * Draw "passes": Gfx_MarkPass(pass) is an empty function in the retail build (a profiler/debug marker that
 * sits next to the Dbg_ProfMark calls of Battle_Draw); it sets nothing up. Battle_Draw's sequence is
 * MarkPass(1) stage, MarkPass(3) 0x247720, MarkPass(2) 0x10FF40, MarkPass(0), MarkPass(4),
 * Gfx_AddDefaultEnv, 0x12CCD0(1), Ot_Draw, MarkPass(0). The real state changes are:
 *   - Gfx_AddDefaultEnv / Gfx_PutDefaultEnv: full-screen scissor and offset, FRAME = current buffer,
 *     Z test GEQUAL with Z writes on, no alpha test, FBA off, source-alpha blending (ALPHA 0x44), texture
 *     clamp on both axes, bilinear filtering, colour clamp on, PRIM attributes from the PRIM register,
 *     TEXA TA1 = 0x80 (16-bit texels with the alpha bit set read as alpha 0x80).
 *   - Ot_Draw (gfx_ot.c): the depth-sorted translucent primitives, Z test on but Z writes off.
 */

/* libc / Sony kernel */
extern void *memset(void *dst, s32 c, u32 size);
extern void FlushCache(s32 mode);

/* Other modules (local declarations). */
extern void Dbg_ProfColor(void *prof, u32 rgba);
extern u8 gBattleProf[];
extern void BtlObj_RebuildTable(void);
extern void Fade_UpdateAll(void);
extern void Fade_DrawScreen(void);
extern void FontIcon_Tick(s32 vsyncs);
extern void PadWatch_Update(void);
extern void PadWatch_Draw(void);
extern void Vu0_CheckState(void);

/* GS privileged (display) registers. */
#define GS_PMODE ((volatile u64 *)0x12000000)
#define GS_DISPFB1 ((volatile u64 *)0x12000070)
#define GS_DISPLAY1 ((volatile u64 *)0x12000080)
#define GS_DISPFB2 ((volatile u64 *)0x12000090)
#define GS_DISPLAY2 ((volatile u64 *)0x120000A0)
#define GS_EXTWRITE ((volatile u64 *)0x120000D0)

/* Switches the GS to interlaced NTSC field mode and builds the 512x448 double buffer in gGfx. */
void Gfx_InitDrawEnv(void);

/* Waits for a vertical blank and records which field it started (1 when the GS reports field 0). */
void Gfx_SyncField(void);

/*
 * Programs the display: both read circuits show the current colour buffer, circuit 1 one scanline lower
 * than circuit 2, and `blend` mixes them 50/50 (flicker filter) instead of showing circuit 1 alone.
 * The picture position comes from the save data's screen offsets. `field` is not used.
 */
void Gfx_SetDisplayRegs(s32 field, s32 blend);

/* Resets the GS and the VIF/GIF paths, clears both frame buffers and sets up gGfx. Called once at boot. */
void Gfx_Init(void);

/* Start of a frame: debug hook, rebuilds the battle object table, advances the screen fades. */
void func_002EC450(void) {
    Dbg_BeginFrame();
    BtlObj_RebuildTable();
    Fade_UpdateAll();
}

/*
 * End of a frame: queues the screen fade, runs the end-of-frame services, waits for the GS to finish the
 * previous display list and for `vsyncs` vertical blanks, then swaps the buffers and reprograms the display.
 */
void Gfx_EndFrame(s32 vsyncs);

/* Always 1. */
s32 Gfx_Stub102118(void);

/* Queues a full-screen rectangle of colour `rgba` on the current buffer, with depth writes off and `fbmsk` as write mask. */
void Gfx_ClearScreen(s32 fbmsk, u32 rgba);

/* Queues the default drawing state (Gfx_PutDefaultEnv) as one packet. */
void Gfx_AddDefaultEnv(void);

/* Writes the 13 quadwords that put GS context 1 back to the default full-screen drawing state. */
void Gfx_PutDefaultEnv(GsQword **pp);

/* Empty in the retail build. */
void Gfx_Stub102438(void);

/* Empty in the retail build. */
void Gfx_Stub102440(void);

/* Empty in the retail build: the battle draw code calls it with a pass number between its Dbg_ProfMark calls. */
void Gfx_MarkPass(s32 pass);

/* Empty in the retail build. */
void Gfx_Stub102450(void);
