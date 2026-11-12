#include "common.h"

f32 func_002EA050(s32 arg0, s32 arg1);
s32 func_002F2BD8(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0037CAD0[] __attribute__((section(".data")));

f32 func_002F57D8(s32 arg0, s32 arg1) {
    f32 var_f0;
    f32 temp_x;
    s32 temp_r;
    s16 temp_a2;
    s32 temp_v3;

    if (arg0 == 0) {
        return func_002EA050((s32)D_0037CAD0, arg1);
    }
    temp_a2 = *(s16 *)(arg0 + 0x3C);
    temp_x = (f32)temp_a2 * 0.84999996f;
    /* cvt.w.s truncates toward zero (saturating): plain cast */
    temp_r = (s32)temp_x;
    *(s16 *)(arg0 + 0x3E) = (s16)temp_r;
    var_f0 = temp_x;
    temp_v3 = *(s32 *)(arg0 + 0x8);
    if (temp_v3 != 0) {
        func_002F2BD8(temp_v3, ((s32)((u32)temp_r << 16)) >> 5, (s32)temp_a2 << 11); /* integer result in v0, unused: f0 is stale */
    }
    return var_f0;
}
