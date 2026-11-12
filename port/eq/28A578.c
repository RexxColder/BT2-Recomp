#include "common.h"

s32 sceMcGetDir(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
s32 sceMcSync(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_00377660[] __attribute__((section(".data")));
extern u8 D_00377678[] __attribute__((section(".data")));
extern u8 D_003B0AA8[] __attribute__((section(".data")));
extern s32 gMcCardCmd;
extern u8 gMcCardPort[] __attribute__((section(".data")));
extern s32 gMcCardStep;

s32 func_0028A578(s32 arg0, s32 arg1) {
    s32 s0;
    s32 v0;
    s32 v1;
    s32 dir;

    if (gMcCardCmd != 0) {
        s0 = ((gMcCardCmd ^ 0x17) != 0) ? 0 : gMcCardStep;
        gMcCardStep = s0;
    } else {
        s0 = gMcCardStep;
    }
    if (s0 == 1) {
        v0 = sceMcSync(1, 0, (s32)(D_003B0AA8 + arg0 * 0x24));
        if (v0 != s0) {
            return 0;
        }
        gMcCardStep += 1;
        return v0;
    }
    if (s0 == 0) {
        gMcCardCmd = 0x17;
        *(s32 *)(gMcCardPort + arg0 * 0x24 + 8) = 0;
        if (arg1 == 0) {
            dir = (s32)D_00377660;
        } else {
            dir = (s32)D_00377678;
        }
        *(s32 *)(gMcCardPort + arg0 * 0x24 + 4) = sceMcGetDir(arg0, 0, dir, 0, -1, 0);
        v1 = *(s32 *)(gMcCardPort + arg0 * 0x24 + 4);
        if (v1 >= 0) {
            gMcCardStep += 1;
            return 0;
        }
        if (v1 != -0xC8) {
            return 0;
        }
        sceMcSync(1, 0, 0);
        return 0;
    }
    return 1;
}
