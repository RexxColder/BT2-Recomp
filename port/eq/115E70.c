#include "common.h"

f32 sinf(f32 arg0);
f32 cosf(f32 arg0);
extern f32 D_00383F18;

/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(x, r) do { \
    (r) = (s32)(x); \
} while (0)

s64 *func_00115E70(u8 *arg0, s32 *arg1, s64 arg2, s32 arg3, f32 farg0, f32 farg1) {
    u8 *var_s2;
    u8 *temp_s1;
    s32 var_s4;
    s32 var_s5;
    s32 temp_ival;
    s32 temp_rs;
    s32 temp_rc;
    s32 temp_s0;
    s32 temp_v0;
    f32 temp_f;
    f32 temp_f20;

    var_s2 = arg0;
    *(s64 *)(var_s2 + 0) = ((s64)0x24000000 << 32) | 0x8001;
    *(s64 *)(var_s2 + 8) = 0x10;
    var_s2 += 0x10;
    *(s64 *)(var_s2 + 0) = 0x45;
    temp_f = ((farg1 - farg0) / farg1) * (f32)(u8)arg3;
    CVT_W_S(temp_f, temp_ival);
    *(s64 *)(var_s2 + 8) = ((s64)(u32)arg2) | ((s64)temp_ival << 24) | ((s64)0xFE00 << 46);
    var_s2 += 0x10;
    *(s64 *)(var_s2 + 0) = ((s64)0x14000000 << 32) | 0x8014;
    *(s64 *)(var_s2 + 8) = 5;
    var_s2 += 0x10;

    var_s4 = 0;
    do {
        if (var_s4 == 0) {
            var_s5 = 0;
            *(s64 *)(var_s2 + 0) = (s64)(arg1[0] * 0x10) | ((s64)(arg1[1] * 0x10) << 16);
        } else {
            var_s5 = var_s4 & 1;
            temp_s1 = var_s2 + (var_s5 * 8);
            temp_f20 = (((f32)(var_s4 - 1)) * D_00383F18) / 18.0f;
            temp_f = farg0 * sinf(temp_f20);
            CVT_W_S(temp_f, temp_rs);
            temp_s0 = arg1[0] - temp_rs;
            temp_f = farg0 * cosf(temp_f20);
            CVT_W_S(temp_f, temp_rc);
            temp_v0 = arg1[1] - temp_rc;
            *(s64 *)(temp_s1 + 0) = (s64)(temp_s0 * 0x10) | ((s64)(temp_v0 * 0x10) << 16);
        }
        var_s4 += 1;
        if (var_s5 != 0) {
            var_s2 += 0x10;
        }
    } while (var_s4 < 0x14);
    return (s64 *)var_s2;
}
