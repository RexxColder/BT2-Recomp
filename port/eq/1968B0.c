#include "common.h"

/* cvt.w.s: truncates toward zero */
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(dst, x) do { (dst) = (s32)(x); } while (0)

#define FS(off) (*(f32 *)(S + (off)))
#define FSW(off, v) (*(f32 *)(S + (off)) = (v))
#define IS(off) (*(s32 *)(S + (off)))

f32 EftMath_WrapAngle(f32 farg0);
void EftMesh_SetColor(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00196C58(s32 arg0);
void func_00196DC0(s32 arg0);

void func_001968B0(s32 arg0) {
    u8 *self;
    u8 *P;
    u8 *S;
    s32 F;
    s32 r;
    s32 t;
    f32 f;
    f32 p90;

    self = (u8 *)arg0;
    P = (u8 *)*(s32 *)(self + 0x38);
    S = P + 0xA10;
    F = IS(0xB0);

    if ((F & 0x2000) != 0) {
        FSW(0xAC, FS(0xAC) - 1.0f);
        if ((F & 0x10) != 0) {
            F = F | 0x20;
            IS(0xB0) = F;
        }
    }

    if ((F & 1) != 0) {
        if ((F & 0x80) != 0) {
            f = FS(0x80) + FS(0x84);
            FSW(0x80, f);
            if (FS(0x88) <= f) {
                FSW(0x80, FS(0x88));
                F = F & -0x81;
                IS(0xB0) = F;
            }
        } else if ((F & 0x100) != 0) {
            f = FS(0x80) + FS(0x84);
            FSW(0x80, f);
            if (f <= FS(0x88)) {
                FSW(0x80, FS(0x88));
                F = F & -0x101;
                IS(0xB0) = F;
            }
        }
        if ((F & 0x10) == 0) {
            if ((F & 0x200) != 0) {
                f = FS(0x90) + FS(0x94);
                FSW(0x90, f);
                if (FS(0x98) <= f) {
                    FSW(0x90, FS(0x98));
                    F = F & -0x201;
                    IS(0xB0) = F;
                }
            } else if ((F & 0x400) != 0) {
                f = FS(0x90) - FS(0x94);
                FSW(0x90, f);
                if (f <= FS(0x98)) {
                    FSW(0x90, FS(0x98));
                    F = F & -0x401;
                    IS(0xB0) = F;
                }
            }
        }
        if ((F & 0x800) != 0) {
            FSW(0x9C, EftMath_WrapAngle(FS(0x9C) - FS(0xA0)));
        }
        FSW(0xA4, EftMath_WrapAngle(FS(0xA4) - FS(0xA8)));

        /* colour byte from the 0x90 value (cvt.w.s, then low byte) */
        p90 = FS(0x90);
        if (p90 >= 2147483648.0f) {
            f = p90 - 2147483648.0f;
            CVT_W_S(r, f);
        } else {
            CVT_W_S(r, p90);
        }
        t = r & 0xFF;
        EftMesh_SetColor((s32)S, 0x80, 0x80, 0x80, t);
        if ((*(s32 *)(P + 0xB70) & 0x200) != 0) {
            func_00196DC0((s32)P);
        } else {
            func_00196C58((s32)P);
        }
        F = IS(0xB0);
    }

    if ((F & 0x10) != 0) {
        f = FS(0x90) - FS(0x94);
        FSW(0x90, f);
        if (f <= 0.0f) {
            FSW(0x90, 0.0f);
            IS(0xB0) = F | 0x20;
        }
    }
}
