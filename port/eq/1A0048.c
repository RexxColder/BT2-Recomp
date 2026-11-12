#include "common.h"

void func_001F0418(f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7,
                   s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 arg9, s32 arg10);
extern s32 D_00387808;

/* cvt.w.s (truncates toward zero) written inline */
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(x, out) do { \
    (out) = (s32)(x); \
} while (0)

void func_001A0048(u8 *arg0) {
    u8 *temp_s0;
    s16 temp_v1;
    s32 temp_v0;
    f32 sp20;
    f32 sp24;
    f32 sp28;
    f32 sp2C;
    f32 temp_f0;
    s32 t3;

    temp_s0 = *(u8 **)(arg0 + 0x38);
    if (*(s32 *)(temp_s0 + 0x28) & 8) {
        temp_v1 = *(s16 *)(temp_s0 + 0x40);
        sp20 = (f32)(temp_v1 - (((temp_v1 < 0 ? temp_v1 + 3 : temp_v1) >> 2) * 4)) * 0.25f;
        temp_v0 = *(s16 *)(temp_s0 + 0x40);
        sp24 = (f32)((temp_v0 < 0 ? temp_v0 + 3 : temp_v0) >> 2) * 0.5f;
        sp28 = sp20 + 0.25f;
        sp2C = sp24 + 0.5f;

        temp_f0 = *(f32 *)(temp_s0 + 0x24) * 4096.0f;
        if (temp_f0 >= 2147483648.0f) {
            CVT_W_S(temp_f0 - 2147483648.0f, t3);
            t3 = (s32)((u32)t3 | 0x80000000u);
        } else {
            CVT_W_S(temp_f0, t3);
        }
        func_001F0418(*(f32 *)(temp_s0 + 0x10), *(f32 *)(temp_s0 + 0x14), *(f32 *)(temp_s0 + 0x18),
                      sp20, sp24, sp28, sp2C, 0.0f,
                      0x80, 0x80, 0x80, 0x60, 0x10, 0x10, 0, t3,
                      0, 1, D_00387808 + 0x3A8);

        temp_f0 = *(f32 *)(temp_s0 + 0x24) * 4096.0f;
        if (temp_f0 >= 2147483648.0f) {
            CVT_W_S(temp_f0 - 2147483648.0f, t3);
            t3 = (s32)((u32)t3 | 0x80000000u);
        } else {
            CVT_W_S(temp_f0, t3);
        }
        func_001F0418(*(f32 *)(temp_s0 + 0x10), *(f32 *)(temp_s0 + 0x14), *(f32 *)(temp_s0 + 0x18),
                      sp20, sp24, sp28, sp2C, 0.0f,
                      0x80, 0x80, 0x80, 0x20, 0x40, 0x40, 0, t3,
                      0, 1, D_00387808 + 0x3A8);
    }
}
