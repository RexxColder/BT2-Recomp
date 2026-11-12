#include "common.h"

s32 func_0011E1C8(void *arg0);
void *func_0011E310(s32 arg0);
f32 func_00272FA8(void);
f32 func_00273000(void);
f32 func_00273048(void);
void func_003126C8(f32 *arg0, void *arg1);

void func_001257E0(s32 *arg0, u8 *arg1, f32 farg0) {
    f32 sp[4];
    f32 f20;
    f32 f21;
    f32 f22;
    f32 x;
    f32 y;
    f32 z;
    u8 *r;

    f21 = func_00272FA8();
    f20 = func_00273000() - farg0;
    f22 = func_00273048();
    *arg0 = 0;
    *(f32 *)(arg1 + 0x1C) = 1.0f;
    *(f32 *)(arg1 + 0xC) = 1.0f;
    if (func_0011E1C8(arg1) == 0) {
        x = *(f32 *)(arg1 + 0x10);
        z = *(f32 *)(arg1 + 0x18);
        y = *(f32 *)(arg1 + 0x14);
        if ((f21 * f21) < ((x * x) + (z * z))) {
            *arg0 |= 2;
        }
        if (y < f20) {
            *arg0 |= 2;
        }
        if (f22 < y) {
            *arg0 |= 2;
        }
    } else {
        r = (u8 *)func_0011E310(0);
        func_003126C8(sp, r + 0x10);
        if ((f21 * f21) < ((sp[0] * sp[0]) + (sp[2] * sp[2]))) {
            *arg0 |= 2;
        }
        if (sp[1] < f20) {
            *arg0 |= 2;
        }
        if (f22 < sp[1]) {
            *arg0 |= 2;
        }
        if (*arg0 == 0) {
            *arg0 = 1;
            r = (u8 *)func_0011E310(0);
            if (*(s32 *)(r + 0x20) & 0x40000000) {
                *arg0 |= 4;
            }
            r = (u8 *)func_0011E310(0x40000000);
            if (*(s32 *)(r + 0x20) & 0x10000000) {
                *arg0 |= 8;
            }
        }
    }
}
