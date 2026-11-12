#include "common.h"

extern u8 *D_00423114;
extern u8 gMcCardPort[];
extern u8 *D_003876A4;
void func_0029C7C0();
s32 func_0029C640();
void func_0029C550();
s32 func_0029C830();
void func_0029C800();
s32 func_0029C1E8();
s32 McCard_GetInfo();
s32 McCard_IsFatalError();
s32 McCard_ReadFile();
s32 McCard_Checksum();
s32 func_00289C98();
s32 func_0028A578();
void func_00288348();
void func_003C64B8();

#define O D_00423114
#define OW(off) (*(s32 *)(O + (off)))
#define PORT(off) (*(s32 *)(gMcCardPort + (off)))
#define SET(st) do { OW(0x36EC) = (st); OW(0x36F0) = 0x78; } while (0)

s32 func_003CA688(void) {
    s32 t, r;

    if (OW(0x36EC) == 0) {
        return 0;
    }
    switch (OW(0x36EC)) {
    case 1:
        func_0029C7C0(0);
        OW(0x36E8) = 0x22;
        func_0029C640(0);
        t = OW(0x36F0) - 1;
        OW(0x36F0) = t;
        if (t >= 0) {
            if (!McCard_GetInfo(1)) {
                break;
            }
            if (OW(0x36F0) > 0) {
                break;
            }
            if (PORT(0x30) == 2) {
                if (!McCard_IsFatalError(PORT(0x2C))) {
                    break;
                }
            }
            SET(7);
        } else {
            if (func_00289C98(1, O + 0x36F8) != 0) {
                SET(3);
            } else {
                s32 s2 = PORT(0x30);
                if (s2 != 2) {
                    SET(7);
                } else if (McCard_IsFatalError(PORT(0x2C))) {
                    SET(7);
                } else {
                    t = PORT(0x2C);
                    if (t >= 0) {
                        break;
                    }
                    OW(0x36EC) = s2;
                }
            }
        }
        break;
    case 2:
        func_0029C7C0(0);
        OW(0x36E8) = 0x22;
        if (func_0028A578(1, 1) != 0) {
            if (PORT(0x2C) == 1) {
                SET(6);
            } else {
                SET(8);
            }
        } else {
            if (!McCard_IsFatalError(PORT(0x2C))) {
                break;
            }
            SET(7);
        }
        break;
    case 3:
        func_0029C7C0(0);
        OW(0x36E8) = 8;
        t = OW(0x36F0) - 1;
        OW(0x36F0) = t;
        if (t >= 0) {
            if (!McCard_GetInfo(1)) {
                break;
            }
            if (!McCard_IsFatalError(PORT(0x2C))) {
                break;
            }
            SET(5);
        } else {
            r = McCard_ReadFile(1, O + 0x7B18, 0x4000, O + 0x36F8);
            if (r == 0) {
                if (PORT(0x2C) >= 0) {
                    break;
                }
                SET(5);
            } else if (PORT(0x24) & 1) {
                SET(6);
            } else if (McCard_Checksum(O + 0x7B18, 0x4000, 0) != 0) {
                SET(6);
            } else {
                *(s32 *)(D_003876A4 + 0x4C8) = (s32)(O + 0x3B18);
                *(s32 *)(D_003876A4 + 0x4CC) = (s32)(O + 0x7B18);
                *(s32 *)(D_003876A4 + 0x18) = *(s32 *)(D_003876A4 + 0x18) | 0x2000;
                SET(4);
            }
        }
        break;
    case 4:
        func_0029C7C0(0);
        OW(0x36E8) = 0xA;
        t = OW(0x36F0) - 1;
        OW(0x36F0) = t;
        if (t >= 0) {
            break;
        }
        func_003C64B8();
        OW(0x36EC) = 9;
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        func_0029C7C0(0);
        if (OW(0x36EC) == 5) {
            OW(0x36E8) = 9;
        } else if (OW(0x36EC) == 6) {
            OW(0x36E8) = 0x19;
        } else if (OW(0x36EC) == 7) {
            OW(0x36E8) = 5;
        } else {
            OW(0x36E8) = 7;
        }
        t = OW(0x36F0) - 1;
        OW(0x36F0) = t;
        if (t >= 0) {
            break;
        }
        OW(0x36EC) = 0xB;
        break;
    case 9:
        func_0029C7C0(0);
        func_0029C550(1);
        OW(0x36EC) = 0xA;
        break;
    case 10:
        func_0029C7C0(0);
        func_0029C640(0);
        if (!func_0029C830()) {
            break;
        }
        OW(0x36EC) = 0;
        func_00288348();
        break;
    case 11:
        func_0029C7C0(1);
        OW(0x36E8) = 0x30;
        t = OW(0x36F4);
        if (t > 0) {
            OW(0x36EC) = 9;
            OW(0x36F4) = 0;
        } else if (t >= 0) {
            r = func_0029C640(0);
            OW(0x36F4) = r;
            OW(0x36F0) = 0xC;
        } else {
            t = OW(0x36F0) - 1;
            OW(0x36F0) = t;
            if (t >= 0) {
                break;
            }
            OW(0x36EC) = 1;
            OW(0x36F0) = 0x78;
            OW(0x36F4) = 0;
            func_00288348();
        }
        break;
    default:
        break;
    }
    func_0029C800(OW(0x36E8));
    return func_0029C1E8(1);
}
