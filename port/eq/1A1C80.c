#include "common.h"

extern f32 D_00384E40;
extern f32 D_00384E44;
extern f32 D_00384E48;
extern f32 D_00384E4C;
extern f32 D_00384E50;
extern f32 D_00384E54;
extern f32 D_00384E58;
extern f32 D_00384E5C;

void func_003126C8(s32 arg0, s32 arg1);
s32 rand(void);
void sceVu0Normalize(s32 arg0, s32 arg1);

void func_001A1C80(u8 *arg0, s32 arg1, f32 *arg2) {
    f32 f20 = D_00384E40;
    f32 f21 = D_00384E44;
    f32 f22 = D_00384E50;
    f32 f23 = D_00384E4C;
    f32 f24 = 0.5f;
    f32 f25 = D_00384E48;
    f32 x4;
    u8 *s0;
    s32 s2 = 0;
    s32 s3 = 0;

    s0 = arg0 + 0x30;
    for (;;) {
        if (*(s32 *)(s0 + 0x48) & 1) {
            s2++;
        } else {
            func_003126C8((s32)s0, arg1);
            s3++;
            *(f32 *)(s0 + 0x10) = arg2[0] + ((f32)rand() / f20 * f21 - f25);
            *(f32 *)(s0 + 0x14) = arg2[1] + ((f32)rand() / f20 - f24);
            *(f32 *)(s0 + 0x18) = arg2[2] + ((f32)rand() / f20 * f21 - f25);
            sceVu0Normalize((s32)(s0 + 0x10), (s32)(s0 + 0x10));
            *(f32 *)(s0 + 0x20) = f21;
            *(s32 *)(s0 + 0x48) = 1;
            *(f32 *)(s0 + 0x28) = 15.0f;
            *(f32 *)(s0 + 0x24) = f23;
            *(s32 *)(s0 + 0x44) = 0;
            x4 = (f32)rand() / f20 * f22;
            *(f32 *)(s0 + 0x2C) = (x4 + x4) - f22;
            *(f32 *)(s0 + 0x30) = (f32)rand() / f20 * D_00384E54 - D_00384E58;
            *(f32 *)(s0 + 0x38) = f23;
            *(f32 *)(s0 + 0x34) = (f32)rand() / f20 + 1.0f;
            *(s32 *)(s0 + 0x40) = 0;
            *(s32 *)(s0 + 0x4C) = 0;
            *(s32 *)(s0 + 0x50) = 0;
            *(s32 *)(s0 + 0x54) = 0;
            *(f32 *)(s0 + 0x3C) = (f32)rand() / f20 * f24 + D_00384E5C;
            if (!(s3 < 9)) {
                return;
            }
            s2++;
        }
        if (!(s2 < 8)) {
            break;
        }
        s0 += 0x60;
    }
}
