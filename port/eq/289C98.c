#include "common.h"
extern s32 gMcCardCmd;
extern s32 gMcCardStep;
extern u8 gMcCardPort[];
extern s32 sceMcOpen();
extern s32 sceMcClose();
extern s32 sceMcSync();

s32 func_00289C98(s32 port, u8 *path) {
    u8 *e;
    s32 r, h;
    if (gMcCardCmd != 0) {
        gMcCardStep = (gMcCardCmd != 0x12) ? 0 : gMcCardStep;
    }
    switch ((u32)gMcCardStep) {
    case 0: case 4: case 8: {
        s32 off = (gMcCardStep == 0) ? 0x298 : (gMcCardStep == 4) ? 0x98 : 0x118;
        e = gMcCardPort + port * 36;
        if (gMcCardStep == 0) {
            *(s32 *)(e + 8) = 0;
            gMcCardCmd = 0x12;
        }
        r = sceMcOpen(port, 0, path + off, 1);
        *(s32 *)(e + 4) = r;
        if (r < 0) {
            if (r == -200) sceMcSync(1, 0, 0);
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    }
    case 1: case 5: case 9:
        e = gMcCardPort + port * 36;
        if (sceMcSync(1, 0, e + 8) != 1) return 0;
        h = *(s32 *)(e + 8);
        if (h < 0) return 0;
        *(s32 *)(e + 0x18) = h;
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 2: case 6: case 10:
        e = gMcCardPort + port * 36;
        r = sceMcClose(*(s32 *)(e + 0x18));
        *(s32 *)(e + 4) = r;
        if (r < 0) return 0;
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 3: case 7: case 11:
        e = gMcCardPort + port * 36;
        if (sceMcSync(1, 0, e + 8) == 0) return 0;
        if (*(s32 *)(e + 8) < 0) return 0;
        {
            s32 st = gMcCardStep;
            gMcCardStep = st + 1;
            return st == 11;
        }
    default:
        return 1;
    }
}
