#include "common.h"

void func_0029DD78(u8 *arg0, u8 *arg1) {
    f32 x = *(f32 *)(arg1 + 0);
    f32 y = *(f32 *)(arg1 + 4);
    f32 z = *(f32 *)(arg1 + 8);
    f32 w = *(f32 *)(arg1 + 0xC);
    f32 x2 = 2.0f * x;
    f32 y2 = 2.0f * y;
    f32 z2 = 2.0f * z;
    f32 xx = x * x2;
    f32 yy = y * y2;
    f32 zz = z * z2;
    f32 wz = w * z2;
    f32 xy = x * y2;
    f32 yz = y * z2;
    f32 xz = z * x2;
    f32 xw = w * x2;
    f32 yw = w * y2;
    *(f32 *)(arg0 + 4) = xy + wz;
    *(f32 *)(arg0 + 0x14) = yz + xw;
    *(f32 *)(arg0 + 0x20) = 1.0f - (xx + yy);
    *(f32 *)(arg0 + 8) = xz - yw;
    *(f32 *)(arg0 + 0) = 1.0f - (yy + zz);
    *(f32 *)(arg0 + 0x10) = 1.0f - (xx + zz);
    *(f32 *)(arg0 + 0xC) = xy - wz;
    *(f32 *)(arg0 + 0x18) = xz + yw;
    *(f32 *)(arg0 + 0x1C) = yz - xw;
}
