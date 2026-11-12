#include "common.h"

f32 cosf(f32 farg0);
f32 sinf(f32 farg0);
void func_00312638(u8 *arg0, u8 *arg1, f32 *arg2);

void func_002B11F0(u8 *arg0, f32 farg0, f32 farg1) {
    f32 sp[4];
    f32 f12;
    f32 f13;
    f32 f1;
    f32 f0;

    f12 = farg0;
    f13 = farg1;
    f1 = *(f32 *)(arg0 + 0x16C);
    if (1.0f < f1) {
        f12 = f12 * f1;
        f13 = f13 * f1;
    }
    f1 = *(f32 *)(arg0 + 0x154);
    f0 = f1 + f13;
    if (f0 < f12) {
        *(f32 *)(arg0 + 0x154) = f0;
    } else {
        f13 = f1 - f13;
        if (!(f12 < f13)) {
            *(f32 *)(arg0 + 0x154) = f12;
        } else {
            *(f32 *)(arg0 + 0x154) = f13;
        }
    }
    f0 = sinf(*(f32 *)(arg0 + 0x15C));
    f1 = *(f32 *)(arg0 + 0x154);
    sp[0] = f0 * f1;
    sp[1] = 0.0f;
    f0 = cosf(*(f32 *)(arg0 + 0x15C));
    f1 = *(f32 *)(arg0 + 0x154);
    sp[2] = f0 * f1;
    sp[3] = 0.0f;
    func_00312638(arg0 + 0xD0, arg0 + 0xD0, sp);
}
