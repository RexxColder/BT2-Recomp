#include "common.h"

extern s32 gFontGlyphGap;
s32 Font_FindGlyph(s32 arg0, u8 **arg1);

#define M64 0x00FFFFFF00000000ULL
#define W(x) ((u64)(s64)(s32)(x))

/* 0x002A2420: emit a GIF sprite (3 qwords per quad) for glyph t0 at (a2,a3) with outline offsets;
 * returns the advance. a0 = u8 ** cursor in the packet buffer. */
s32 func_002A2420(u8 **arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u8 *sp[4];
    u8 *g;
    u16 h2, h4;
    s32 t2, t1, t5, t6, t3, t4, t7, t8, t9, s1, s5, s6, s7, fp, s2;
    u64 s4, a0v, ex;
    f32 f0, f1;
    s32 v0;

    g = (u8 *)Font_FindGlyph(arg4 & 0xFFFF, sp);
    if (g == 0) {
        return 0;
    }
    h4 = *(u16 *)(g + 4);
    h2 = *(u16 *)(g + 2);
    t2 = (h4 >> 10) & 0x1F;
    t1 = (h2 >> 10) & 0x1F;
    f0 = (f32)t2;
    f1 = (f32)t1;
    f0 = f0 * *(f32 *)(arg1 + 0x14);
    f1 = f1 * *(f32 *)(arg1 + 0x10);
    f0 = f0 * 16.0f;
    f1 = f1 * 16.0f;
    t3 = *(u16 *)(arg1 + 0x28);
    {
        u8 *fnt = sp[0];
        s32 gx = (s32)(*(u32 *)(fnt + 8)) + (((h4 >> 15) << 1) + (h2 >> 15));
        a0v = *(u64 *)(*(u8 **)(*(u8 **)fnt + 8) + 0x30);
        a0v |= (u64)(s64)gx << 37;
        a0v |= *(u32 *)(fnt + 4);
    }
    t4 = (s32)f0;
    {
        s32 a1c = (s32)f1;
        t5 = (arg2 + 0x700) << 4;
        s2 = *(s32 *)(arg1 + 0x20);
        t6 = (arg3 + 0x720) << 4;
        s6 = ((h2 & 0x3FF) << 4) + 8;
        s5 = ((h4 & 0x3FF) << 4) + 8;
        t9 = t6 + t4;
        fp = s6 + (t1 << 4);
        s7 = s5 + (t2 << 4);
        s4 = a0v | 0x400000000ULL;
        s1 = t5 + a1c;
    }
    t1 = *(u16 *)(arg1 + 0x2A) << 4;
    t3 <<= 4;
    t8 = 0;
    t7 = 0;
    t4 = 0;
    t2 = 0;
    ex = (u64)*(u32 *)(arg1 + 0x24) | 0x3F80000000000000ULL;

#define EMIT(A, B, C, D)                                                                   \
    do {                                                                                   \
        *(u64 *)*arg0 = s4;                                                                \
        *(u64 *)(*arg0 + 8) = ex;                                                          \
        *arg0 += 0x10;                                                                     \
        *(u64 *)*arg0 = (u64)s6 | ((u64)(s64)s5 << 16);                                    \
        *(u64 *)(*arg0 + 8) = W(A) | (W(B) << 16) | M64;                                   \
        *arg0 += 0x10;                                                                     \
        *(u64 *)*arg0 = (u64)fp | ((u64)(s64)s7 << 16);                                    \
        *(u64 *)(*arg0 + 8) = W(C) | (W(D) << 16) | M64;                                   \
        *arg0 += 0x10;                                                                     \
    } while (0)

    if (s2 == 2) {
        s2 = 0;
        do {
            switch (s2) {
            case 0: t8 = t5 + t3; t4 = t6 + t1; t7 = s1 + t3; t2 = t9 + t1; break;
            case 1: t8 = t5 - t3; t4 = t6 + t1; t7 = s1 - t3; t2 = t9 + t1; break;
            case 2: t8 = t5 + t3; t4 = t6 - t1; t7 = s1 + t3; t2 = t9 - t1; break;
            case 3: t8 = t5 - t3; t4 = t6 - t1; t7 = s1 - t3; t2 = t9 - t1; break;
            case 4: t8 = t5 + t3; t4 = t6; t7 = s1 + t3; t2 = t9; break;
            case 5: t8 = t5 - t3; t4 = t6; t7 = s1 - t3; t2 = t9; break;
            case 6: t8 = t5; t4 = t6 + t1; t7 = s1; t2 = t9 + t1; break;
            case 7: t8 = t5; t4 = t6 - t1; t7 = s1; t2 = t9 - t1; break;
            default: break;
            }
            s2++;
            if (t8 > 0 && !(0xFFFF < t7) && t4 > 0 && !(0xFFFF < t2)) {
                EMIT(t8, t4, t7, t2);
            }
        } while (s2 < 8);
    } else if (s2 == 1) {
        t8 = t5 + t3;
        t7 = s1 + t3;
        t2 = t9 + t1;
        t4 = t6 + t1;
        if (t8 > 0 && !(0xFFFF < t7) && t4 > 0 && !(0xFFFF < t2)) {
            EMIT(t8, t4, t7, t2);
        }
    } else if (s2 == 3) {
        s2 = 0;
        do {
            switch (s2) {
            case 0: t8 = t5 - t3; t4 = t6 - t1; t7 = s1 - t3; t2 = t9 + t1; break;
            case 1: t8 = t5 + t3; t4 = t6 - t1; t7 = s1 + t3; t2 = t9 + t1; break;
            case 2: t8 = t5 - t3; t4 = t6 - t1; t7 = s1 + t3; t2 = t9 - t1; break;
            case 3: t8 = t5 - t3; t4 = t6 + t1; t7 = s1 + t3; t2 = t9 + t1; break;
            default: break;
            }
            s2++;
            if (t8 > 0 && !(0xFFFF < t7) && t4 > 0 && !(0xFFFF < t2)) {
                EMIT(t8, t4, t7, t2);
            }
        } while (s2 < 4);
    }

    if (!((u64)(s64)(t5 - 1) > 0xFFFE)) {
        if (t6 > 0 && !(0xFFFF < t6)) {
            u64 exa = (u64)(u32)arg5 | 0x3F80000000000000ULL;
            *(u64 *)*arg0 = s4;
            *(u64 *)(*arg0 + 8) = exa;
            *arg0 += 0x10;
            *(u64 *)*arg0 = (u64)s6 | ((u64)(s64)s5 << 16);
            *(u64 *)(*arg0 + 8) = W(t5) | (W(t6) << 16) | M64;
            *arg0 += 0x10;
            *(u64 *)*arg0 = (u64)fp | ((u64)(s64)s7 << 16);
            *(u64 *)(*arg0 + 8) = W(s1) | (W(t9) << 16) | M64;
            *arg0 += 0x10;
        }
    }
    f1 = *(f32 *)(arg1 + 0x10);
    f0 = (f32)((*(u16 *)(g + 2) >> 10) & 0x1F);
    f0 = f0 * f1;
    v0 = (s32)f0;
    return v0 + gFontGlyphGap + *(u16 *)(arg1 + 0x18);
}
