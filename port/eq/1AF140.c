#include "common.h"

void func_001B07D0(s32 arg0);
f32 func_00272FA8(void);
void func_003126C8(s32 arg0, s32 arg1);
void sceVu0CopyMatrix(s32 arg0, s32 arg1);

s32 func_001AF140(void *arg0) {
    u8 *s1;
    u8 *s0;
    s32 v0;
    f32 f1;
    f32 f4;
    f32 t;
    f32 a;
    f32 b;

    s1 = (u8 *)arg0;
    s0 = s1 + 0x10;
    v0 = 1;

    func_003126C8((s32)(s1 + 0x20), (s32)s0);
    func_003126C8((s32)s0, (s32)s1);
    sceVu0CopyMatrix((s32)(s1 + 0x80), (s32)(s1 + 0xC0));
    if (*(u8 *)(s1 + 0x59) != 0) {
        func_001B07D0((s32)s1);
    }

    f4 = *(f32 *)(s1 + 0x48);
    f1 = *(f32 *)(s1 + 0x50) - 1.0f;
    *(f32 *)(s1 + 0xC) = 1.0f;
    *(f32 *)(s1 + 0x50) = f1;
    *(f32 *)(s1 + 0x00) = *(f32 *)(s1 + 0x00) + (*(f32 *)(s1 + 0x30) * f4);
    *(f32 *)(s1 + 0x04) = *(f32 *)(s1 + 0x04) + (*(f32 *)(s1 + 0x34) * f4);
    *(f32 *)(s1 + 0x08) = *(f32 *)(s1 + 0x08) + (*(f32 *)(s1 + 0x38) * f4);

    if (!(f1 <= 0.0f)) {
        t = func_00272FA8() + 50.0f;
        a = *(f32 *)(s1 + 0x08);
        b = *(f32 *)(s1 + 0x00);
        v0 = 1;
        if (!((t * t) < ((b * b) + (a * a)))) {
            v0 = 0;
        }
    }
    return v0;
}
