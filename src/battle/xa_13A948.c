#include "common.h"

/* Callees: the effect stage draw check, the steam draw, and the original's func_ labels for the surrounding calls. */
extern s32 EftStage_IsDrawOn(void);
extern void EftSteam_DrawParts(void *steam, s64 arg);
extern void func_00128EF0(void);
extern void func_00128F08(void);
extern void func_00128F90(s32 view);

/* Camera view block (gBtlCamView, gp-relative): the view is read at +0x100 by the draw call. */
extern s32 gBtlCamView;

/* Draws the steam of an effect block (block at obj+0x38) while the effect stage draw is on: the draw state is
 * set up around the call, and the steam parts are drawn with the 64-bit word at +0x30 of the block at +0x60. */
void EftSteam_DrawStage(void *obj) {
    void *steam;

    steam = *(void **)((u8 *)obj + 0x38);
    if (EftStage_IsDrawOn() == 0) {
        return;
    }
    func_00128EF0();
    func_00128F90(gBtlCamView + 0x100);
    EftSteam_DrawParts(steam, *(s64 *)(*(u8 **)((u8 *)steam + 0x60) + 0x30));
    func_00128F08();
}
