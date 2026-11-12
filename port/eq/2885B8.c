#include "common.h"

s32 sceMcGetInfo(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 sceMcSync(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_003B0AA8[] __attribute__((section(".data")));
extern u8 gMcCardPort[] __attribute__((section(".data")));
extern s32 gMcCardCmd;
extern s32 gMcCardStep;

s32 McCard_CheckChange(s32 arg0) {
    s32 step;
    s32 res;
    u8 *p;

    if (gMcCardCmd != 0) {
        step = ((gMcCardCmd ^ 0xB) != 0) ? 0 : gMcCardStep;
        gMcCardStep = step;
    } else {
        step = gMcCardStep;
    }
    if (step == 0) {
        p = gMcCardPort + arg0 * 0x24;
        *(s32 *)(p + 8) = 0;
        gMcCardCmd = 0xB;
        res = sceMcGetInfo(arg0, 0, 0, 0, 0);
        *(s32 *)(p + 4) = res;
        if (res >= 0) {
            gMcCardStep += 1;
            return 0;
        }
        if (res == -0xC8) {
            sceMcSync(1, 0, 0);
        }
        return 0;
    }
    if (step == 1) {
        res = sceMcSync(1, 0, (s32)(D_003B0AA8 + arg0 * 0x24));
        if (res != 0) {
            gMcCardStep += 1;
            return 1;
        }
        return 0;
    }
    return 1;
}
