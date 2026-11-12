#include "common.h"

/* cvt.w.s: truncates toward zero (r = dst) */
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(dst, x) do { (dst) = (s32)(x); } while (0)

f32 Stg_FadeRatio(f32 farg0, f32 farg1);
f32 func_00273B80(void *pos, f32 farg0);
extern u8 *gBtlStage;

void func_002746C0(u8 *arg0) {
    s32 i;
    s32 j;
    s32 k;
    s32 a2;
    s32 idx8;
    s32 idx4;
    s32 r32;
    s32 t32;
    f32 f20;
    f32 r;
    f32 v;
    f32 t;
    u8 *base;
    u8 *s2;
    u8 *s3;
    u8 *s1;
    u8 *ep;
    u8 *s4;
    u8 *a1p;
    u8 *e;

    if (*(s32 *)(gBtlStage + 0x44) == 0) {
        return;
    }
    base = (u8 *)*(s32 *)(gBtlStage + 0x5C);
    s2 = base + *(s32 *)(gBtlStage + 0x48) * 4;
    i = 0;
    do {
        if (*(s32 *)s2 & 2) {
            f20 = Stg_FadeRatio((f32)*(s32 *)(s2 + 0x30), (f32)*(s32 *)(s2 + 0x2C));
            j = 0;
            if (*(s32 *)(s2 + 0x24) != 0) {
                s3 = base + *(s32 *)(s2 + 0x28) * 4;
                do {
                    s1 = base + *(s32 *)s3 * 4;
                    idx8 = *(s32 *)(s1 + 8);
                    if (idx8 != 0) {
                        ep = base + idx8 * 4;
                        idx4 = *(s32 *)(s1 + 4);
                        s4 = base + idx4 * 4;
                        if (*(s32 *)(ep + 0x4C) >= 0) {
                            r = func_00273B80(ep + 0x30, f20);   /* asm: addiu a0, v0, 0x30 */
                            a2 = 0x80;
                            if (r < 1.0f) {
                                v = r * 128.0f;
                                if (v >= 2147483648.0f) {
                                    t = v - 2147483648.0f;
                                    CVT_W_S(t32, t);
                                } else {
                                    CVT_W_S(t32, v);
                                }
                                a2 = t32 & 0xFF;
                            }
                            if (a2 != 0) {
                                k = 0;
                                if (*(u16 *)s1 != 0) {
                                    a1p = s4;
                                    do {
                                        k += 1;
                                        e = base + *(s32 *)a1p * 4;
                                        *(u8 *)(e + 4) = (u8)a2;
                                        arg0[*(u16 *)e] = 1;
                                        a1p += 4;
                                    } while (k < (s32)*(u16 *)s1);
                                }
                            }
                        }
                    }
                    j += 1;
                    s3 += 4;
                } while ((u32)j < (u32)*(s32 *)(s2 + 0x24));
            }
        }
        s2 += 0x50;
        i += 1;
    } while ((u32)i < (u32)*(s32 *)(gBtlStage + 0x44));
}
