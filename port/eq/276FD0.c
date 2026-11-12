#include "common.h"

void func_001014E8(s32 arg0);
extern s32 D_00387F2C __attribute__((section(".data")));

void func_00276FD0(f32 arg0) {
    f32 var_f3;
    s32 temp_v0;
    s32 t;
    f32 r;

    temp_v0 = *(s32 *) (D_00387F2C + 0x10B0);
    if (temp_v0 == 0) {
        func_001014E8(-0x3C0);
        return;
    }
    var_f3 = -300.0f;
    if (arg0 != 0.0f) {
        var_f3 = (1.0f - (arg0 * ((f32) temp_v0 / 9.0f))) * var_f3;
    }
    t = (s32) var_f3;
    r = var_f3 - (f32) t;
    if ((r > 0.5f) || ((r == 0.5f) && (t & 1))) {
        t += 1;
    }
    if ((r < -0.5f) || ((r == -0.5f) && (t & 1))) {
        t -= 1;
    }
    func_001014E8(t);
}
