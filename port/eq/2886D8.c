#include "common.h"

s32 sceMcFormat(s32 arg0, s32 arg1);
s32 sceMcSync(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_003B0AA8[] __attribute__((section(".data")));
extern u8 gMcCardPort[] __attribute__((section(".data")));
extern s32 gMcCardCmd;
extern s32 gMcCardStep;

s32 McCard_Format(s32 arg0) {
    s32 step;
    s32 res;
    u8 *p;

    if (gMcCardCmd != 0) {
        step = ((gMcCardCmd ^ 0xC) != 0) ? 0 : gMcCardStep;
        gMcCardStep = step;
    } else {
        step = gMcCardStep;
    }
    if (step == 0) {
        p = gMcCardPort + arg0 * 0x24;
        *(s32 *)(p + 8) = 0;
        gMcCardCmd = 0xC;
        res = sceMcFormat(arg0, 0);
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
        p = D_003B0AA8 + arg0 * 0x24;
        res = sceMcSync(1, 0, (s32)p);
        if (res != 0) {
            if (*(s32 *)p >= 0) {
                gMcCardStep = 0;
                gMcCardCmd = 0;
                return 1;
            }
            return 0;
        }
        return 0;
    }
    gMcCardStep = 0;
    gMcCardCmd = 0;
    return 1;
}
