#include "common.h"
#include <stdlib.h>

extern f32 D_00386C30;

extern s32 func_00211310();
extern s32 func_00211328();
extern s32 BtlMember_IsHealthEmpty_2127F8();
extern s32 func_0023F420();
extern s32 func_0023F410();
extern s32 func_0023F430();
extern s32 BtlPad_Test48();
extern s32 BtlPad_Test4C();
extern s32 func_0023D380();
extern s32 func_0023D600();
extern s32 func_0023D8C0();
extern s32 func_0023DC00();
extern s32 func_0023BD30();
extern f32 func_00207E80(s32 a);
extern f32 func_00207E88(s32 a);
extern s32 func_00203C58();
extern s32 BtlMember_HasKi();
extern s32 BtlMember_HasBlast();
extern u8 *BtlMember_GetActiveGauge();
extern f32 func_00217330(s32 a);
extern f32 BtlCharApi_GetHeight(s32 a);
extern s32 func_00217488();
extern s32 func_00217518();
extern s32 func_00218580(s32 a, f32 f12, f32 f13);
extern f32 func_00210A98(s32 a);

static s32 func_0023BDA8_real(u8 *a0, s32 a1);

/* Envoltorio del decide: con BT2_WATCH2C=<personaje> arma el watchpoint de gauge+0x2C (herramienta B3). */
s32 func_0023BDA8(u8 *a0, s32 a1)
{
    s32 r = func_0023BDA8_real(a0, a1);
    if (*(u32 *)(a0 + 0x48) | *(u32 *)(a0 + 0x4C)) {
        u8 *gg = BtlMember_GetActiveGauge(a0);
        if (gg && gg[0x2C] == 0 && getenv("BT2_WATCH2C") != NULL && (s32)strtoul(getenv("BT2_WATCH2C"), NULL, 0) == (s32)a0) {
            extern void bt2_watch_byte(unsigned long addr); bt2_watch_byte((unsigned long)(gg + 0x2C)); /* TEMP B3 */
        }
    }
    return r;
}

static s32 func_0023BDA8_real(u8 *a0, s32 a1)
{
    s32 a = (s32)a0;
    s32 v, t, r;
    f32 f;
    f32 g;

    if ((a1 & 0x4000000) && *(s32 *)(a0 + 0xB74) > 0) return 0x9F;
    if ((a1 & 0x2000000) && func_00211310(a0, 0, 0x4000)) return 0xA1;
    if (a1 & 0x80) {
        if (!func_00211310(a0, 0, 2) && !func_00211310(a0, 0, 4)) {
            if (!func_00211328(a0, 0, 4)) return 0xA;
        }
    }
    if ((a1 & 0x1000000) && BtlMember_IsHealthEmpty_2127F8(a0)) return 0xA0;

    if (func_0023F420(a0) & 1) {
        if ((a1 & 0x100) && BtlPad_Test48(a0, 7) && BtlPad_Test4C(a0, 3)) {
            if (!func_00211310(a0, 0, 1)) return 0xF;
            if (BtlPad_Test48(a0, 8)) return 0xF;
            return 0x10;
        }
        if ((a1 & 0x200) && BtlPad_Test48(a0, 7) && BtlPad_Test4C(a0, 4)) return 0x13;
        if (a1 & 0x400) {
            if (!func_00211310(a0, 0, 4)) {
                if (BtlPad_Test48(a0, 7) && BtlPad_Test4C(a0, 5)) return 0x14;
            }
        }
    }
    if ((a1 & 2) && func_00211310(a0, 0, 4)) {
        if (!func_00211310(a0, 0, 0x100)) {
            if (BtlPad_Test4C(a0, 4)) return 9;
        }
    }
    if ((a1 & 4) && BtlPad_Test4C(a0, 3)) {
        return func_0023D380(a0);
    }
    if ((a1 & 0x800) && func_00211310(a0, 0, 1) && BtlPad_Test4C(a0, 3)) {
        if (BtlPad_Test48(a0, 8)) {
            f = __builtin_fabsf(func_00207E88(a));
            g = __builtin_fabsf(func_00207E80(a));
            if (g < f) {
                if (!(func_00207E88(a) < 0.0f)) return 0x18;
            } else {
                if (!(func_00207E80(a) < 0.0f)) return 0x16;
                return 0x15;
            }
        } else if (a1 & 0x1000) {
            if (func_0023F420(a0) & 8) return 0x17;
        }
    }
    if (a1 & 0x10000) {
        if ((func_0023F420(a0) & 0x200) && func_00211310(a0, 0, 1) && BtlPad_Test4C(a0, 2)
            && !BtlPad_Test48(a0, 7)) {
            v = func_00203C58(a0, 0x4000);
            if (BtlMember_HasKi(a0, v ? 0 : 10000)) {
                if (BtlPad_Test48(a0, 8)) {
                    f = __builtin_fabsf(func_00207E88(a));
                    g = __builtin_fabsf(func_00207E80(a));
                    if (g < f) {
                        if (!(func_00207E88(a) < 0.0f)) return 0x1F;
                        return 0x1E;
                    }
                    if (!(func_00207E80(a) < 0.0f)) return 0x1D;
                    return 0x1C;
                }
            }
        }
    }
    if ((a1 & 0x2000) && func_00211310(a0, 0, 1) && func_00211310(a0, 0, 0x102)) {
        if (BtlPad_Test4C(a0, 4)) {
            t = func_0023F410(a0);
            return (t & 0x1000) ? 12 : 0x19;
        }
    }
    if ((a1 & 0x8000) && func_00211310(a0, 0, 1)) {
        if (!func_00211310(a0, 0, 4) && BtlPad_Test4C(a0, 5)) {
            s32 go = 1;
            if (!func_00211310(a0, 0, 0x100)) {
                if (func_00211310(a0, 0, 2)) {
                    if (func_0023F410(a0) & 0x1000) return 0xA;
                } else {
                    go = 0;
                }
            }
            if (go) {
                f = func_00217330(a);
                g = BtlCharApi_GetHeight(*(s32 *)(a0 + 0x1534));
                if (!(f < g)) return 0x1A;
                return 0x12;
            }
        }
    }
    if (a1 & 0x40000) {
        r = func_0023D600(a0);
        if (r != -1) return r;
    }
    if (a1 & 0x200000) {
        r = func_0023D8C0(a0);
        if (r != -1) return r;
    }
    if ((a1 & 0x20) && !func_00211310(a0, 0, 0x800) && !func_00211310(a0, 8, 1) && BtlPad_Test48(a0, 7)) {
        if (!(func_0023F430(a0) & 0x80)) return 0x2D;
        {
            u8 *gg = BtlMember_GetActiveGauge(a0);
            if (BtlMember_HasKi(a0, *(s32 *)(gg + 0x10))) {
                if (BtlMember_HasBlast(a0, 100000)) return 0x2D;
            }
        }
    }
    if ((a1 & 0x400000) && (func_0023F420(a0) & 0x100) && BtlPad_Test4C(a0, 2)) {
        r = func_00218580(a, 5.0f, 2.0f);
        if (r == 1) {
            t = func_0023F410(a0);
            return (t & 2) ? 0x47 : 0x43;
        }
        if (r == 2) {
            t = func_0023F410(a0);
            return (t & 2) ? 0x47 : 0x44;
        }
    }
    if ((a1 & 0x20000) && BtlPad_Test48(a0, 2)) {
        if (!func_00211310(a0, 0, 1)) return 0x3A;
        f = func_00210A98(a);
        if (D_00386C30 < __builtin_fabsf(f)) return func_00217518(0x41, 0x3A);
        return 0x3A;
    }
    if (a1 & 0x80000) {
        if (BtlPad_Test4C(a0, 6)) {
            if (*(s32 *)(a0 + 0xB8C) <= 0) {
                if (!func_00211310(a0, 0, 1)) return 0x42;
            }
        }
    }
    if ((a1 & 8) && func_00211310(a0, 0, 0x102)) {
        if (BtlPad_Test4C(a0, 4)) {
            t = func_0023F410(a0);
            return (t & 0x1000) ? 12 : 0x11;
        }
    }
    if ((a1 & 0x10) && func_00211310(a0, 0, 0x102) && !func_00211310(a0, 0, 4) && BtlPad_Test4C(a0, 5)) {
        if (!(func_0023F410(a0) & 0x1000)) return 0x12;
        if (func_00211310(a0, 0, 0x100)) return 0x12;
        return 0xA;
    }
    if ((a1 & 0x800000) && func_00211310(a0, 0, 1) && BtlPad_Test48(a0, 0xC) && BtlPad_Test4C(a0, 6)) return 0x48;
    if (a1 & 0x100000) {
        if (func_0023BD30(a0) && BtlPad_Test48(a0, 7)) {
            if (BtlPad_Test48(a0, 0x1C) && BtlPad_Test4C(a0, 0x1D)) return 0x32;
            if (BtlPad_Test48(a0, 0x1D) && BtlPad_Test4C(a0, 0x1C)) return 0x32;
        }
    }
    if (a1 & 0x40) {
        r = func_0023DC00(a0);
        if (r != -1) return r;
    }
    if ((a1 & 1) && BtlPad_Test48(a0, 8)) {
        if (func_00211310(a0, 0, 1) && func_00211310(a0, 1, 1)) {
            if (func_00217488(a0) != 8) return 8;
        } else {
            if (func_00217488(a0) == 7) return -1;
            return 7;
        }
    }
    return -1;
}
