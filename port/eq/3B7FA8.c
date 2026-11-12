#include "common.h"

extern u8 *D_3876A0 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern s32 D_0042138C __attribute__((section(".data")));
extern u8 *D_0042139C __attribute__((section(".data")));
extern u8 *D_3876AC __attribute__((section(".data")));
extern u8 *D_00421390 __attribute__((section(".data")));
extern u8 *D_00421394 __attribute__((section(".data")));
extern u8 *D_00421398 __attribute__((section(".data")));
extern u8 *D_004213A0 __attribute__((section(".data")));
extern u8 *D_004213A4 __attribute__((section(".data")));
extern u8 *D_004213A8 __attribute__((section(".data")));
extern u8 *D_004213AC __attribute__((section(".data")));

void BtlWork_InitOnce(void);
void func_003BC310(void);
s32 func_003B4250();
s32 func_003BAFE8(s32 a0);
s32 func_003C0700(void);
s32 func_003CB1D0(void);
s32 func_003DB6A8(void);
s32 func_003DF9E8(void);
s32 func_003E3B98(void);
s32 func_003EC690(void);
s32 func_003F9300(void);
s32 func_00418410(void);
s32 func_0041BF08(void);
s32 func_100D58(s32 a0, s32 a1, s32 a2);
void func_1012D0(void);
void func_101438(s32 a0);
void func_247CC0(void);
void func_24BE18(void);
s32 func_24BE80(void);
void func_28BB60(void *a0);
void func_28BCB0(void);
void func_28BCE8(void);
void func_297A30(void);
void func_297A60(s32 a0, s32 a1);
void func_297EC8(void);
void func_298158(s32 a0);
int Port_SkipIntro(void);   /* F4 */

s32 func_003B7FA8(void) {
    s32 s2 = 0;
    s32 r;
    s32 f4;
    s32 st;
    s32 m;
    u8 *ctl;

    if (*(s32 *)(D_3876A4 + 0x18) & 0x40) {
        func_003BC310();
        BtlWork_InitOnce();
        *(s32 *)(D_3876A4 + 0x18) &= ~0x40;
    }

    ctl = D_3876A0 + 0x480;
    if (*(s32 *)(ctl + 0) & 0x8) {
        f4 = *(s32 *)(ctl + 4);
        if (f4 & 0x10) {
            *(s32 *)(D_3876A4 + 0x18) &= ~0x10;
            *(s32 *)(D_3876A4 + 0x18) &= ~0x20;
            *(s32 *)(D_3876A4 + 0x18) &= ~0x80;
            *(s32 *)(D_3876A4 + 0x1C) = 4;
        } else if (f4 & 0x20) {
            st = *(s32 *)(D_3876A4 + 0x1C);
            if ((u32)(st - 0x1E) < 6) {
                m = *(s32 *)(D_3876A4 + 0x464);
                if (m == 1) {
                    *(s32 *)(D_3876A4 + 0x1C) = 0x20;
                } else if (m < 2) {
                    if (m == 0) {
                        *(s32 *)(D_3876A4 + 0x1C) = 0x1F;
                    }
                } else if (m == 2) {
                    *(s32 *)(D_3876A4 + 0x1C) = 0x21;
                }
            } else if ((u32)(st - 0x3D) < 4) {
                *(s32 *)(D_3876A4 + 0x1C) = 0x3F;
            }
        } else if (!(f4 & 0x400) && !(f4 & 0x800) && (f4 & 0x100)) {
            *(s32 *)(D_3876A4 + 0x1C) = 0x1E;
        }
    }

    st = *(s32 *)(D_3876A4 + 0x1C);
    if (st == 1 || st == 4) {
        if (D_0042138C == 0) {
            func_100D58(*(s32 *)(D_3876A4 + 0x4) + 1, 0, 1);
            do {
                D_0042138C = func_100D58(0, 0, 0);
            } while (D_0042138C == 0);
        }
        func_298158(0);
    }

    func_28BCB0();
    func_297A60(0x33D1, 0);

    while (s2 == 0) {
        u32 idx = (u32)(*(s32 *)(D_3876A4 + 0x1C) - 1);

        if (idx >= 64) {
            continue;
        }
        switch (idx) {
            case 0:
                if (D_0042138C == 0) {
                    func_100D58(*(s32 *)(D_3876A4 + 0x4) + 1, 0, 1);
                    do {
                        D_0042138C = func_100D58(0, 0, 0);
                    } while (D_0042138C == 0);
                }
                func_28BCB0();
                func_297A60(0x33E5, 0);
                func_101438(0x3E1F);
                r = func_003BAFE8(2);
                func_1012D0();
                func_297EC8();
                func_28BCE8();
                if (r == 0) {
                    *(s32 *)(D_3876A4 + 0x1C) = 4;
                } else if (r == 1) {
                    *(s32 *)(D_3876A4 + 0x1C) = 1;
                    s2 = 1;
                } else {
                    func_28BB60((void *)D_0042138C);
                    D_0042138C = 0;
                    *(s32 *)(D_3876A4 + 0x1C) = 2;
                }
                break;

            case 1:
                func_24BE18();
                if (!Port_SkipIntro()) {
                    func_24BE80();   /* F4: el opening que se repite al quedar idle */
                }
                *(s32 *)(D_3876A4 + 0x1C) = 1;
                break;

            case 3:
                func_101438(0x3E20);
                r = func_003B4250(1);
                if (r != 0) {
                    func_1012D0();
                    func_28BB60((void *)D_0042138C);
                    D_0042138C = 0;
                } else {
                    func_1012D0();
                    *(s32 *)(D_3876A4 + 0x1C) = 1;
                }
                break;

            case 4:
                func_101438(0x3E2C);
                func_247CC0();
                func_1012D0();
                *(s32 *)(D_3876A4 + 0x1C) = 4;
                break;

            case 5:
            case 6:
            case 7:
                r = func_0041BF08();
                if (r != 0) {
                    s2 = 1;
                }
                break;

            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
                r = func_003F9300();
                if (r != 0) {
                    s2 = 1;
                }
                break;

            case 23:
            case 24:
            case 25:
            case 26:
                r = func_003CB1D0();
                if (r != 0) {
                    s2 = 1;
                }
                break;

            case 29:
            case 30:
            case 31:
            case 32:
            case 33:
            case 34:
                r = func_00418410();
                if (r != 0) {
                    s2 = 1;
                }
                break;

            case 37:
            case 38:
            case 39:
            case 40:
                func_003C0700();
                break;

            case 42:
            case 43:
            case 44:
            case 45:
            case 46:
                func_003DF9E8();
                break;

            case 47:
            case 48:
            case 49:
            case 50:
                func_003E3B98();
                break;

            case 52:
            case 53:
            case 55:
            case 56:
            case 57:
                func_003DB6A8();
                break;

            case 60:
            case 61:
            case 62:
            case 63:
                r = func_003EC690();
                if (r != 0) {
                    s2 = 1;
                }
                break;

            default:
                break;
        }
    }

    func_297EC8();
    func_28BCE8();
    func_297A30();
    func_28BB60((void *)D_0042138C);
    D_0042138C = 0;
    func_28BB60(D_0042139C);
    D_0042139C = 0;
    func_28BB60(D_3876AC);
    D_3876AC = 0;
    func_28BB60(D_00421390);
    D_00421390 = 0;
    func_28BB60(D_00421394);
    D_00421394 = 0;
    func_28BB60(D_00421398);
    D_00421398 = 0;
    func_28BB60(D_004213A4);
    D_004213A4 = 0;
    func_28BB60(D_004213A0);
    D_004213A0 = 0;
    func_28BB60(D_004213A8);
    D_004213A8 = 0;
    func_28BB60(D_004213AC);
    D_004213AC = 0;
    return 0;
}
