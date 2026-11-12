#include "common.h"

u8 *func_00269A40(u8 *arg0, s32 arg1);
void func_003126C8(s32 arg0, s32 arg1);
extern f32 D_00386E88;

void func_00260260(u8 *arg0, u8 *arg1) {
    u8 *s0;
    u8 *v1;
    u8 *v2;
    f32 f20;
    f32 f0;
    f32 f1;
    f32 f2;

    s0 = *(u8 **)(arg1 + 0x50);
    v1 = func_00269A40(arg0, 0);
    if (v1 == NULL) {
        return;
    }
    f20 = *(f32 *)(v1 + 0x34);
    func_003126C8((s32)s0, (s32)(v1 + 0x30));
    v2 = func_00269A40(arg0, 0x11);
    if (v2 == NULL) {
        return;
    }
    f1 = *(f32 *)(*(u8 **)(arg0 + 0x958) + 0x44);
    if (f1 < 0.0f) {
        f0 = *(f32 *)(arg1 + 0xC8) + *(f32 *)(arg1 + 0xC8);
        *(f32 *)(s0 + 0x10) = f0;
        *(f32 *)(s0 + 0x14) = f0 * f0;
    } else {
        *(f32 *)(s0 + 0x10) = f1;
        *(f32 *)(s0 + 0x14) = f1 * f1;
    }
    f2 = *(f32 *)(s0 + 0x10);
    f0 = *(f32 *)(v2 + 0x34) - D_00386E88;
    *(f32 *)(s0 + 0x4) = f0;
    if (f20 < f0 + f2) {
        *(f32 *)(s0 + 0x4) = (f20 - f2) - D_00386E88;
    }
}
