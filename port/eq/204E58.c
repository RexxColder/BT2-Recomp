#include "common.h"

void BtlOpp_GetDelta(void *arg0, void *arg1, s64 arg2, s32 arg3);
f32 BtlUtil_WrapAngle(f32 farg0);
void *EftRay_Create(void *arg0);
f32 atan2f(f32 farg0, f32 farg1);
f32 func_0029DFD0(void *arg0, f32 farg1);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern f32 D_00385928;
extern f32 D_0038592C;
extern f32 D_00385930;
extern f32 D_00385934;

void func_00204E58(u8 *arg0) {
    u8 fr[0xC0];
    s32 a3;
    s64 a2;
    s32 i;
    f32 var_f2;
    f32 f12v;
    f32 r;
    f32 t;
    f32 c;
    f32 sub;

    if ((*(s64 *)(arg0 + 0x338) & 0x20000) == 0) {
        return;
    }

    memset(fr + 0x60, 0, 0x10);
    *(f32 *)(fr + 0x6C) = 1.0f;
    a3 = *(s32 *)(arg0 + 0x1534);
    *(s32 *)(fr + 0x78) = 0x80;
    *(f32 *)(fr + 0x80) = 1.0f;
    *(f32 *)(fr + 0x84) = 800.0f;
    *(f32 *)(fr + 0x88) = 1.5f;
    *(f32 *)(fr + 0x90) = 50.0f;
    *(s32 *)(fr + 0x94) = 2;
    *(s32 *)(fr + 0x98) = 0x30;
    *(s32 *)(fr + 0x9C) = a3;
    *(u8 *)(fr + 0xB0) = 1;
    *(s32 *)(fr + 0x70) = 0x80;
    *(s32 *)(fr + 0x74) = 0x80;
    *(s32 *)(fr + 0x8C) = 0;
    *(s32 *)(fr + 0xA0) = 1;
    *(s32 *)(fr + 0xA4) = 1;
    *(s32 *)(fr + 0xA8) = 0;
    *(s32 *)(fr + 0xAC) = 0;
    *(s32 *)(fr + 0x7C) = 0x40;

    /* copy the 0x60 bytes at fr+0x60 down to fr+0; a2 keeps the last 8-byte load (fr+0xB8) */
    for (i = 0; i < 0x60; i++) {
        fr[i] = fr[0x60 + i];
    }
    a2 = *(s64 *)(fr + 0xB8);

    BtlOpp_GetDelta(arg0, fr + 0x60, a2, a3);

    var_f2 = 0.0f;
    f12v = *(f32 *)(fr + 0x60);
    if ((D_00385928 < fabsf(*(f32 *)(fr + 0x60))) || (D_00385928 < fabsf(*(f32 *)(fr + 0x68)))) {
        sub = atan2f(*(f32 *)(fr + 0x60), *(f32 *)(fr + 0x68)) - *(f32 *)(arg0 + 0x150);
        f12v = sub;
        var_f2 = BtlUtil_WrapAngle(sub);
    }

    c = (fabsf(var_f2) / D_0038592C) * 0.5f + D_00385930;
    *(f32 *)(fr + 0x20) = c;
    r = func_0029DFD0(fr + 0x60, f12v);

    t = -20.0f - (r * D_00385934);
    *(f32 *)(fr + 0x2C) = t;
    if (t < -50.0f) {
        *(f32 *)(fr + 0x2C) = -50.0f;
    }

    EftRay_Create(fr);
}
