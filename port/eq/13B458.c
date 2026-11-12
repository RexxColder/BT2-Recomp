#include "common.h"

extern u8 *gEftDust;
extern u8 *D_003876A0;
extern f32 D_00384310;
extern f32 D_00384314;
extern f32 D_00384318;
extern f32 D_0038431C;
extern f32 D_00384320;
extern f32 D_00384324;

void func_003126C8(void *arg0, s32 arg1);
s32 func_0013B350(f32 *out);
f32 BtlCharApi_GetHeight(u8 *arg0);
f32 sqrtf(f32 arg0);
void EftWater_AddSplash(u8 *arg0, u8 *arg1, f32 *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, f32 farg0);

s32 func_0013B458(u8 *arg0, s32 arg1, s32 arg2, f32 farg0) {
    f32 buf[8];
    s32 s0;
    s32 v;
    f32 f0;
    f32 f1;
    f32 f20;
    f32 h;
    u8 *g;

    s0 = arg2 & 0xFF;
    f20 = farg0;
    if (gEftDust == NULL) {
        return 0;
    }
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x2) != 0) {
        return 0;
    }

    func_003126C8(buf, arg1);
    v = func_0013B350(&buf[4]);
    if (v != 0) {
        buf[1] = buf[4] + -1.0f;
    }

    f1 = sqrtf(fabsf(f20));
    f20 = f1 * D_00384310;

    if (s0 == 1) {
        h = BtlCharApi_GetHeight(arg0);
        f0 = h * D_00384318;
        f0 = f0 * f20;
        g = gEftDust;
        EftWater_AddSplash(g + 0x3C, g + 0x40, buf, 4, 3, 2, 2, f0 * D_0038431C);
        return 1;
    }
    if (s0 == 0) {
        h = BtlCharApi_GetHeight(arg0);
        f0 = h * D_00384314;
        g = gEftDust;
        EftWater_AddSplash(g + 0x3C, g + 0x40, buf, 7, 4, 3, 2, f0 * f20);
        return 1;
    }
    if (s0 == 2) {
        h = BtlCharApi_GetHeight(arg0);
        f0 = h * D_00384320;
        g = gEftDust;
        f0 = f0 * f20;
        EftWater_AddSplash(g + 0x3C, g + 0x40, buf, 7, 4, 3, 2, f0 * D_00384324);
        return 1;
    }
    return 1;
}
