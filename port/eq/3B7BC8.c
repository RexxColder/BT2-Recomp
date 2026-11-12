#include "common.h"

void func_003B7688(u8 *a0, s32 a1, s32 a2, s32 a3, s32 t0);
void func_003B7720(u8 *a0, s32 a1, s32 a2, s32 a3, s32 t0, f32 f12);
void func_003B77C8(u8 *a0, s32 a1, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17);
void func_003B7848(u8 *a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13);
void func_003B7940(u8 *a0, s32 a1, s32 a2, s32 a3, s32 t0);
void func_003B79E0(u8 *a0, s32 a1);
void func_003B7A38(u8 *a0, s32 a1, s32 a2, s32 a3);
void func_003B7AE0(u8 *a0, s32 a1, s32 a2, s32 a3, s32 t0);

#define EI(off) (*(s32 *)(e + (off)))
#define EF(off) (*(f32 *)(e + (off)))

/* cvt.w.s: truncation */
static s32 ftoi(f32 f) {
    return (s32)f;
}

/* cvt.w.s with the 2^31 split (f >= 2^31 -> (int)(f - 2^31) | 0x80000000) */
static s32 ftoi_sat(f32 f) {
    if (f >= 2147483648.0f) {
        return (s32)(((u32)(s32)(f - 2147483648.0f)) | 0x80000000u);
    }
    return (s32)f;
}

/* 0x003B7BC8: walks a table of 36-byte entries (tbl at +0x10, 65 steps) gated by the u64 bitmask at +0,
   the timer float at +0xC, flags u16 at +8 (bit 0 = active). Each due step sets its mask bit and
   dispatches on entry type (0..6) to an effect function with the object at +0x14. */
s32 func_003B7BC8(u8 *s0) {
    u8 *tbl;
    u8 *e;
    u8 *obj14;
    s32 s1;
    s32 s2;
    s32 result;
    s32 type;
    s32 bit;
    u64 mask;
    f32 timer;

    if ((*(u16 *)(s0 + 8) & 1) == 0) {
        return 0;
    }

    tbl = *(u8 **)(s0 + 0x10);
    if (tbl == 0) {
        return 0;
    }

    s2 = 1;
    if (*(s32 *)tbl < 0) {
        *(u16 *)(s0 + 8) = 0;
        timer = *(f32 *)(s0 + 0xC);
        *(f32 *)(s0 + 0xC) = timer + 1.0f;
        return *(s32 *)tbl;
    }

    mask = *(u64 *)s0;
    timer = *(f32 *)(s0 + 0xC);
    s1 = 0;
    e = tbl;

    for (;;) {
        if (((mask >> (s1 & 63)) & 1) == 0) {
            if ((f32)*(s32 *)(e + 0x20) <= timer) {
                mask |= (u64)1 << (s1 & 63);
                *(u64 *)s0 = mask;
                type = EI(4);
                obj14 = *(u8 **)(s0 + 0x14);
                switch (type) {
                case 0: {
                    f32 v11 = EF(0x14);
                    if (v11 == 0.0f) {
                        func_003B7688(obj14, EI(0), ftoi(EF(8)), ftoi(EF(0xC)), ftoi(EF(0x10)));
                    } else {
                        func_003B7720(obj14, EI(0), ftoi(EF(8)), ftoi(EF(0xC)), ftoi(EF(0x10)), v11);
                    }
                    break;
                }
                case 1:
                    func_003B77C8(obj14, EI(0), EF(8), EF(0xC), EF(0x10), EF(0x14), EF(0x18), EF(0x1C));
                    break;
                case 2:
                    func_003B7848(obj14, EI(0), ftoi(EF(8)), ftoi(EF(0x14)), EF(0xC), EF(0x10));
                    break;
                case 3:
                    func_003B7940(obj14, EI(0), ftoi(EF(8)), ftoi(EF(0xC)), ftoi(EF(0x10)));
                    break;
                case 4:
                    func_003B79E0(obj14, EI(0));
                    break;
                case 5:
                    if (EF(0x10) == 0.0f) {
                        s32 a2 = ftoi_sat(EF(8));
                        func_003B7A38(obj14, EI(0), a2 & 0xFF, ftoi(EF(0xC)));
                    } else {
                        s32 a2 = ftoi_sat(EF(8));
                        func_003B7AE0(obj14, EI(0), a2 & 0xFF, ftoi(EF(0xC)), ftoi(EF(0x10)));
                    }
                    break;
                default:
                    break;
                }
                if ((u32)type < 7) {
                    mask = *(u64 *)s0;
                }
            }
        }

        bit = (mask >> (s1 & 63)) & 1;
        s1 += 1;
        result = bit;
        if (s1 >= 0x41) {
            goto ecc;
        }
        if (bit == 0) {
            s2 = 0;
        }
        e = tbl + 36 * s1;
        if (*(s32 *)e >= 0) {
            continue;
        }
        if (s2 != 0) {
            *(u16 *)(s0 + 8) = 0;
        }
        break;
    }

ecc:
    *(f32 *)(s0 + 0xC) = timer + 1.0f;
    return result;
}
