#include "common.h"

/* 0x00288F60: memory card save write state machine (20 steps). port record = 36 bytes: +4 ret, +8 result, +0x18 fd. */
extern s32 gMcCardCmd;
extern s32 gMcCardStep;
extern u8 gMcCardPort[];
extern s32 sceMcOpen();
extern s32 sceMcClose();
extern s32 sceMcSync();
extern s32 sceMcWrite();
extern s32 sceMcSeek();

s32 McCard_WriteSave(s32 port, u8 *data, s32 size, u8 *file) {
    u8 *e;
    s32 r;

    if (gMcCardCmd != 0) {
        gMcCardStep = (gMcCardCmd == 0xF) ? gMcCardStep : 0;
    }
    switch ((u32)gMcCardStep) {
    case 0:
        e = gMcCardPort + port * 36;
        *(s32 *)(e + 8) = 0;
        gMcCardCmd = 0xF;
        r = sceMcOpen(port, 0, file + 0x298, 0x202);
        *(s32 *)(e + 4) = r;
        if (r < 0) {
            if (r == -200) {
                sceMcSync(1, 0, 0);
            }
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 1:
        e = gMcCardPort + port * 36;
        if (sceMcSync(1, 0, e + 8) == 0) {
            return 0;
        }
        r = *(s32 *)(e + 8);
        if (r < 0) {
            *(s32 *)(e + 8) = 0;
            gMcCardStep = 2;
        } else {
            *(s32 *)(e + 0x18) = r;
            gMcCardStep = 4;
        }
        return 0;
    case 2:
        e = gMcCardPort + port * 36;
        r = sceMcOpen(port, 0, file + 0x298, 2);
        *(s32 *)(e + 4) = r;
        if (r < 0) {
            if (r == -200) {
                sceMcSync(1, 0, 0);
            }
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 3:
        e = gMcCardPort + port * 36;
        if (sceMcSync(1, 0, e + 8) == 0) {
            return 0;
        }
        r = *(s32 *)(e + 8);
        if (r < 0) {
            return 0;
        }
        *(s32 *)(e + 0x18) = r;
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 4:
        e = gMcCardPort + port * 36;
        r = sceMcWrite(*(s32 *)(e + 0x18), data, size);
        *(s32 *)(e + 4) = r;
        if (r < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 5:
        e = gMcCardPort + port * 36;
        if (sceMcSync(1, 0, e + 8) == 0) {
            return 0;
        }
        r = *(s32 *)(e + 8);
        if (r < 0) {
            return 0;
        }
        if (r == size) {
            gMcCardStep = gMcCardStep + 1;
        } else {
            *(s32 *)(e + 8) = -8;
        }
        return 0;
    case 6:
        e = gMcCardPort + port * 36;
        r = sceMcClose(*(s32 *)(e + 0x18));
        *(s32 *)(e + 4) = r;
        if (r < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 7:
        e = gMcCardPort + port * 36;
        if (sceMcSync(1, 0, e + 8) == 0) {
            return 0;
        }
        if (*(s32 *)(e + 8) < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 8:
        e = gMcCardPort + port * 36;
        r = sceMcOpen(port, 0, file + 0x118, 3);
        *(s32 *)(e + 4) = r;
        if (r < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 9:
        e = gMcCardPort + port * 36;
        if (sceMcSync(1, 0, e + 8) == 0) {
            return 0;
        }
        r = *(s32 *)(e + 8);
        if (r >= 0) {
            *(s32 *)(e + 0x18) = r;
            gMcCardStep = 12;
            return 0;
        }
        if (r == -4) {
            *(s32 *)(e + 8) = 0;
            gMcCardStep = gMcCardStep + 1;
        }
        return 0;
    case 10:
        e = gMcCardPort + port * 36;
        r = sceMcOpen(port, 0, file + 0x118, 0x202);
        *(s32 *)(e + 4) = r;
        if (r < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 11:
        e = gMcCardPort + port * 36;
        if (sceMcSync(1, 0, e + 8) == 0) {
            return 0;
        }
        r = *(s32 *)(e + 8);
        if (r < 0) {
            return 0;
        }
        *(s32 *)(e + 0x18) = r;
        gMcCardStep = 16;
        return 0;
    case 12:
        e = gMcCardPort + port * 36;
        r = sceMcSeek(*(s32 *)(e + 0x18), 0, 2);
        *(s32 *)(e + 4) = r;
        if (r < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 13:
        e = gMcCardPort + port * 36;
        if (sceMcSync(1, 0, e + 8) == 0) {
            return 0;
        }
        r = *(s32 *)(e + 8);
        if (r < 0) {
            return 0;
        }
        if (*(s32 *)(file + 0xC) != r) {
            gMcCardStep = gMcCardStep + 1;
        } else {
            gMcCardStep = 18;
        }
        return 0;
    case 14:
        e = gMcCardPort + port * 36;
        r = sceMcSeek(*(s32 *)(e + 0x18), 0, 0);
        *(s32 *)(e + 4) = r;
        if (r < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 15:
        e = gMcCardPort + port * 36;
        if (sceMcSync(1, 0, e + 8) == 0) {
            return 0;
        }
        if (*(s32 *)(e + 8) < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 16:
        e = gMcCardPort + port * 36;
        r = sceMcWrite(*(s32 *)(e + 0x18), *(u8 **)file, *(s32 *)(file + 0xC));
        *(s32 *)(e + 4) = r;
        if (r < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 17:
        e = gMcCardPort + port * 36;
        if (sceMcSync(1, 0, e + 8) == 0) {
            return 0;
        }
        if (*(s32 *)(e + 8) < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 18:
        e = gMcCardPort + port * 36;
        r = sceMcClose(*(s32 *)(e + 0x18));
        *(s32 *)(e + 4) = r;
        if (r < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;
    case 19:
        e = gMcCardPort + port * 36;
        if (sceMcSync(1, 0, e + 8) == 0) {
            return 0;
        }
        if (*(s32 *)(e + 8) < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 1;
    default:
        gMcCardStep = 0;
        gMcCardCmd = 0;
        return 1;
    }
}
