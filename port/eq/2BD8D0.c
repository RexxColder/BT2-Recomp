#include "common.h"

f32 func_0030D640(f32 x);
void func_002F64A0(s32 arg0, s32 arg1, f32 farg0, s32 arg2);

void func_002BD8D0(s32 arg0, s32 arg1, f32 farg0) {
    s32 temp_s0;
    s32 var_a1;
    s32 var_a2;
    f32 v;
    f32 v2;

    temp_s0 = *(s32 *)(*(s32 *)((u8 *)arg0 + 0x2004));
    if (temp_s0 == 0) {
        return;
    }
    if (arg1 == 0x3E8) {
        func_002F64A0(temp_s0, 0, farg0, 0);
        return;
    }
    v = func_0030D640((f32)arg1);
    v = (v - 6.907755f) * 1731.234f;
    v2 = v * 0.01f;
    /* cvt.w.s truncates toward zero (saturating): plain cast */
    var_a2 = (s32)v;
    var_a1 = (s32)v2;
    var_a2 = var_a2 - var_a1 * 100;
    func_002F64A0(temp_s0, var_a1, (f32)arg1, var_a2);
}
