#include "common.h"

s32 sceMcGetDir(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
s32 sceMcSync(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_00387D40[] __attribute__((section(".data")));
extern u8 D_003B0AA8[] __attribute__((section(".data")));
extern s32 gMcCardCmd;
extern u8 gMcCardPort[] __attribute__((section(".data")));
extern s32 gMcCardStep;

s32 McCard_ReadDir(s32 arg0, s32 arg1, s32 arg2) {
    u8 *port;
    s32 temp_v0;
    s32 var_v0;
    s32 var_v1;

    if (gMcCardCmd != 0) {
        var_v1 = ((gMcCardCmd ^ 0x16) != 0) ? 0 : gMcCardStep;
        gMcCardStep = var_v1;
    } else {
        var_v1 = gMcCardStep;
    }

    if (var_v1 == 0) {
        port = gMcCardPort + arg0 * 0x24;
        *(s32 *)(port + 8) = 0;
        gMcCardCmd = 0x16;
        temp_v0 = sceMcGetDir(arg0, 0, (s32)D_00387D40, 0, arg1, arg2);
        *(s32 *)(port + 4) = temp_v0;
        if (temp_v0 < 0) {
            if (temp_v0 == -0xC8) {
                sceMcSync(1, 0, 0);
            }
            return 0;
        }
        gMcCardStep += 1;
        return 0;
    }

    if (var_v1 != 1) {
        gMcCardStep = 0;
        gMcCardCmd = 0;
        return 1;
    }

    var_v0 = sceMcSync(1, 0, (s32)(D_003B0AA8 + arg0 * 0x24));
    if (var_v0 != 0) {
        gMcCardStep = 0;
        var_v0 = 1;
        gMcCardCmd = 0;
    }
    return var_v0;
}
