#include "common.h"

void Mtx_StoreIdentity(void *arg0);
void Vec3_Cross(f32 *a0, f32 *a1, f32 *a2);
void Vec3_Normalize(f32 *a0, f32 *a1);
f32 func_00129CD8(f32 *a0, f32 *a1, s64 a2);
extern f32 D_00385610;
extern void *gBtlCamView;

void func_001DA8B8(void *arg0, void *arg1) {
    f32 sp0[4];
    f32 sp10[4];
    f32 sp20[4];
    f32 sp30[4];
    f32 sp40[4];
    f32 *a1f;
    u8 *cam;
    f32 r;
    f32 f0;
    u8 *m;
    s32 i;

    a1f = (f32 *)arg1;
    for (i = 0; i < 4; i++) {
        sp0[i] = a1f[i];
    }

    cam = (u8 *)gBtlCamView;
    sp10[0] = *(f32 *)(cam + 0x8);
    sp10[1] = *(f32 *)(cam + 0x18);
    sp10[2] = *(f32 *)(cam + 0x28);
    sp10[3] = 1.0f;

    r = func_00129CD8(sp10, sp0, *(s64 *)arg1);
    f0 = __builtin_fabsf(r);

    cam = (u8 *)gBtlCamView;
    sp40[0] = sp0[0] + (-*(f32 *)(cam + 0x4) * f0 * D_00385610);
    sp40[1] = sp0[1] + (-*(f32 *)(cam + 0x14) * f0 * D_00385610);
    sp40[2] = sp0[2] + (-*(f32 *)(cam + 0x24) * f0 * D_00385610);
    sp40[3] = 1.0f;

    Vec3_Normalize(sp40, sp40);
    Vec3_Cross(sp20, sp10, sp40);
    Vec3_Normalize(sp20, sp20);
    Vec3_Cross(sp30, sp20, sp40);
    Vec3_Normalize(sp30, sp30);

    Mtx_StoreIdentity(arg0);
    m = (u8 *)arg0;
    *(f32 *)(m + 0x00) = sp20[0];
    *(f32 *)(m + 0x04) = sp20[1];
    *(f32 *)(m + 0x08) = sp20[2];
    *(s32 *)(m + 0x30) = 0;
    *(f32 *)(m + 0x10) = sp30[0];
    *(f32 *)(m + 0x14) = sp30[1];
    *(f32 *)(m + 0x18) = sp30[2];
    *(f32 *)(m + 0x20) = sp40[0];
    *(f32 *)(m + 0x24) = sp40[1];
    *(f32 *)(m + 0x28) = sp40[2];
    *(s32 *)(m + 0x38) = 0;
    *(s32 *)(m + 0x34) = 0;
}
