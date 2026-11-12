#include "common.h"

#define AT(T, p, off) (*(T *)((u8 *)(p) + (off)))

void Mtx_StoreIdentity(u8 *arg0);
void Vec3_Cross(f32 *arg0, f32 *arg1, f32 *arg2);
void Vec3_Normalize(f32 *arg0, f32 *arg1);
void func_00129B58(f32 *arg0, u8 *arg1, f32 *arg2);
void func_00129BB8(f32 farg0, f32 *arg1, f32 *arg2);
f32 func_00129CD8(u8 *arg0, u8 *arg1, u8 *arg2);

extern u8 *gBtlCamView;

void func_001DA3E8(u8 *arg0, u8 *arg1, u8 *arg2) {
    u8 fr[0xC0];
    u8 *cam;
    s32 i;
    f32 res;
    f32 f20;

    cam = gBtlCamView;
    for (i = 0; i < 16; i++) {
        fr[i] = arg1[i];
    }
    for (i = 0; i < 16; i++) {
        fr[0x10 + i] = arg2[i];
    }

    AT(f32, fr, 0x60) = AT(f32, cam, 8);
    AT(f32, fr, 0x64) = AT(f32, cam, 0x18);
    AT(f32, fr, 0x6C) = 1.0f;
    AT(f32, fr, 0x68) = AT(f32, cam, 0x28);
    res = func_00129CD8(fr + 0x60, fr, cam);

    if (res < 0.0f) {
        AT(f32, fr, 0x2C) = 1.0f;
        f20 = (-res) * 0.5f;
        AT(f32, fr, 0x20) = -AT(f32, fr, 0x60);
        AT(f32, fr, 0x24) = -AT(f32, fr, 0x64);
        AT(f32, fr, 0x28) = -AT(f32, fr, 0x68);
    } else {
        f20 = res * 0.5f;
        AT(f32, fr, 0x20) = AT(f32, fr, 0x60);
        AT(f32, fr, 0x24) = AT(f32, fr, 0x64);
        AT(f32, fr, 0x28) = AT(f32, fr, 0x68);
        AT(f32, fr, 0x2C) = 1.0f;
    }
    func_00129B58((f32 *)(fr + 0x20), fr, (f32 *)(fr + 0x20));
    Vec3_Normalize((f32 *)(fr + 0x20), (f32 *)(fr + 0x20));
    func_00129BB8(f20, (f32 *)(fr + 0x20), (f32 *)(fr + 0x20));

    AT(f32, fr, 0x50) = AT(f32, fr, 0) + AT(f32, fr, 0x20);
    AT(f32, fr, 0x54) = AT(f32, fr, 4) + AT(f32, fr, 0x24);
    AT(f32, fr, 0x5C) = 1.0f;
    AT(f32, fr, 0x58) = AT(f32, fr, 8) + AT(f32, fr, 0x28);
    Vec3_Normalize((f32 *)(fr + 0x50), (f32 *)(fr + 0x50));
    Vec3_Cross((f32 *)(fr + 0x30), (f32 *)(fr + 0x60), (f32 *)(fr + 0x50));
    Vec3_Normalize((f32 *)(fr + 0x30), (f32 *)(fr + 0x30));
    Vec3_Cross((f32 *)(fr + 0x40), (f32 *)(fr + 0x30), (f32 *)(fr + 0x50));
    Vec3_Normalize((f32 *)(fr + 0x40), (f32 *)(fr + 0x40));

    Mtx_StoreIdentity(arg0);
    AT(f32, arg0, 0x00) = AT(f32, fr, 0x30);
    AT(f32, arg0, 0x10) = AT(f32, fr, 0x40);
    AT(f32, arg0, 0x20) = AT(f32, fr, 0x50);
    AT(f32, arg0, 0x04) = AT(f32, fr, 0x34);
    AT(f32, arg0, 0x14) = AT(f32, fr, 0x44);
    AT(f32, arg0, 0x24) = AT(f32, fr, 0x54);
    AT(f32, arg0, 0x08) = AT(f32, fr, 0x38);
    AT(f32, arg0, 0x18) = AT(f32, fr, 0x48);
    AT(f32, arg0, 0x28) = AT(f32, fr, 0x58);
    AT(f32, arg0, 0x30) = AT(f32, fr, 0x10);
    AT(f32, arg0, 0x34) = AT(f32, fr, 0x14);
    AT(f32, arg0, 0x38) = AT(f32, fr, 0x18);
}
