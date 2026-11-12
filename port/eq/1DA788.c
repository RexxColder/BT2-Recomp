#include "common.h"

void Mtx_StoreIdentity(void *arg0);

void func_001DA788(u8 *arg0, u8 *arg1) {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    f32 xx;
    f32 yy;
    f32 zz;
    f32 xy;
    f32 xz;
    f32 yz;
    f32 wx;
    f32 wy;
    f32 wz;

    x = *(f32 *)(arg1 + 0x0);
    y = *(f32 *)(arg1 + 0x4);
    z = *(f32 *)(arg1 + 0x8);
    w = *(f32 *)(arg1 + 0xC);

    xx = x * x;
    zz = z * z;
    yy = y * y;
    wz = w * z;
    wx = w * x;
    xy = x * y;
    wy = w * y;
    xz = x * z;
    yz = y * z;

    Mtx_StoreIdentity(arg0);
    *(f32 *)(arg0 + 0x10) = 2.0f * (xy - wz);
    *(f32 *)(arg0 + 0x00) = 1.0f - (2.0f * (yy + zz));
    *(f32 *)(arg0 + 0x20) = 2.0f * (wy + xz);
    *(f32 *)(arg0 + 0x28) = 1.0f - (2.0f * (xx + yy));
    *(f32 *)(arg0 + 0x04) = 2.0f * (xy + wz);
    *(f32 *)(arg0 + 0x24) = 2.0f * (yz - wx);
    *(f32 *)(arg0 + 0x14) = 1.0f - (2.0f * (xx + zz));
    *(f32 *)(arg0 + 0x08) = 2.0f * (xz - wy);
    *(f32 *)(arg0 + 0x18) = 2.0f * (yz + wx);
}
