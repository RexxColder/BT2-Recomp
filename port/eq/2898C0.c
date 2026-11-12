#include "common.h"

extern s32 sceMcOpen();
extern s32 sceMcSync();
extern s32 sceMcSeek();
extern s32 sceMcRead();
extern s32 sceMcClose();
extern s32 func_0028BAA8(s32 size);
extern s32 gMcCardCmd;
extern s32 gMcCardStep;
extern u8 gMcCardPort[];

/* One step of the memory card load state machine; returns 1 when finished */
s32 func_002898C0(s32 port, u8 *info) {
    u8 *p;
    s32 r;
    s32 ret;

    if (gMcCardCmd != 0) {
        gMcCardStep = (gMcCardCmd == 0x11) ? gMcCardStep : 0;
    }
    ret = 1;
    p = gMcCardPort + port * 36;
    switch ((u32)gMcCardStep) {
    case 0:
        *(s32 *)(p + 0x20) = 0;
        gMcCardCmd = 0x11;
        *(s32 *)(p + 0) = 0;
        *(s32 *)(p + 8) = 0;
        r = sceMcOpen(port, 0, info + 0x298, 1);
        *(s32 *)(p + 4) = r;
        if (r < 0) {
            if (r == -200) {
                sceMcSync(1, 0, 0);
            }
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 1:
        if (sceMcSync(1, 0, p + 8) == 0) {
            return 0;
        }
        r = *(s32 *)(p + 8);
        if (r < 0) {
            return 0;
        }
        *(s32 *)(p + 0x18) = r;
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 2:
        r = sceMcSeek(*(s32 *)(p + 0x18), 0, 2);
        *(s32 *)(p + 4) = r;
        if (r < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 3:
        if (sceMcSync(1, 0, p + 8) == 0) {
            return 0;
        }
        r = *(s32 *)(p + 8);
        if (r < 0) {
            return 0;
        }
        *(s32 *)(p + 0x1C) = r;
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 4:
        r = sceMcSeek(*(s32 *)(p + 0x18), 0, 0);
        *(s32 *)(p + 4) = r;
        if (r < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 5:
        if (sceMcSync(1, 0, p + 8) == 0) {
            return 0;
        }
        if (*(s32 *)(p + 8) < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 6:
        r = func_0028BAA8(*(s32 *)(p + 0x1C));
        *(s32 *)(p + 0x20) = r;
        r = sceMcRead(*(s32 *)(p + 0x18), r, *(s32 *)(p + 0x1C));
        *(s32 *)(p + 4) = r;
        if (r < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 7:
        if (sceMcSync(1, 0, p + 8) == 0) {
            return 0;
        }
        r = *(s32 *)(p + 8);
        if (r < 0) {
            return 0;
        }
        if (r != *(s32 *)(p + 0x1C)) {
            *(s32 *)p |= 1;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 8:
        r = sceMcClose(*(s32 *)(p + 0x18));
        *(s32 *)(p + 4) = r;
        if (r < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 9:
        if (sceMcSync(1, 0, p + 8) == 0) {
            return 0;
        }
        if (*(s32 *)(p + 8) < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 1;
    default:
        return ret;
    }
}
