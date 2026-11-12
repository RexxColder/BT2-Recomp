#include "common.h"

s32 func_003126C8(s32 arg0, s32 arg1);
s32 rand(void);
extern u8 D_002C3630[] __attribute__((section(".data")));
extern f32 D_00386E14;
extern f32 D_00386E18;

void func_0025C2D8(s32 arg0, s32 arg1, s32 arg2) {
    u8 *p = (u8 *)arg0;
    s32 v0;
    f32 temp_f0;
    f32 var_f20;
    f32 var_f21;
    f32 var_f22;

    v0 = 3;
    var_f20 = 0.0f;
    var_f21 = 0.0f;
    do {
        temp_f0 = *(f32 *)(p + 0x10);
        v0 -= 1;
        if (var_f20 < temp_f0) {
            var_f21 = *(f32 *)(p + 0x0);
            var_f20 = temp_f0;
        }
        p += 4;
    } while (v0 >= 0);
    func_003126C8(arg1, (s32)D_002C3630);
    func_003126C8(arg2, (s32)D_002C3630);
    if (var_f20 > 0.0f) {
        var_f22 = var_f21 * D_00386E14 * var_f20;
        if (D_00386E18 < var_f22) {
            var_f22 = D_00386E18;
        }
        *(f32 *)(arg2 + 0) = (f32)((rand() & 0xFF) - 0x7F) * 0.0078125f * var_f22;
        *(f32 *)(arg2 + 4) = (f32)((rand() & 0xFF) - 0x7F) * 0.0078125f * var_f22;
        *(f32 *)(arg1 + 0) = (f32)((rand() & 0xFF) - 0x7F) * 0.5f * var_f22;
        *(f32 *)(arg1 + 4) = (f32)((rand() & 0xFF) - 0x7F) * 0.5f * var_f22;
        *(f32 *)(arg1 + 8) = (f32)((rand() & 0xFF) - 0x7F) * 0.5f * var_f22;
    }
}
