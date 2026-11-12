#include "common.h"

s32 func_00177540(void);
void func_00129C28(s32 arg0, s32 arg1);
f32 BtlCharApi_GetHeight(s32 arg0);
s32 rand(void);
extern f32 D_0038497C;
extern f32 D_00384980;
extern f32 D_00384984;
extern u8 *D_00387E94;

void func_001775A0(s32 arg0, void *arg1, void *arg2) {
    s64 vA[2];
    s64 vB[2];
    s32 s1;
    s32 r;
    f32 f0;
    u8 *d;

    vA[0] = *(s64 *)arg1;
    vA[1] = *(s64 *)((u8 *)arg1 + 8);
    vB[0] = *(s64 *)arg2;
    vB[1] = *(s64 *)((u8 *)arg2 + 8);
    s1 = func_00177540();
    if (s1 == 0) {
        return;
    }
    d = D_00387E94;
    if (*(s32 *)(d + 0x3F54) != 0) {
        *(s32 *)(s1 + 0x4C) = 0;
        *(s32 *)(s1 + 0x48) = *(s32 *)(d + 0x3F58);
    } else {
        *(s32 *)(d + 0x3F54) = s1;
        *(s32 *)(s1 + 0x48) = 0;
        *(s32 *)(s1 + 0x4C) = 0;
    }
    if (*(s32 *)(d + 0x3F58) != 0) {
        *(s32 *)(*(s32 *)(d + 0x3F58) + 0x4C) = s1;
    }
    *(s32 *)(d + 0x3F58) = s1;
    *(s32 *)(s1 + 0x30) = arg0;
    func_00129C28(s1, (s32)vA);
    func_00129C28(s1 + 0x10, (s32)vA);
    func_00129C28(s1 + 0x20, (s32)vB);
    r = rand();
    f0 = BtlCharApi_GetHeight(arg0) * D_00384984;
    *(f32 *)(s1 + 0x38) = 64.0f;
    *(f32 *)(s1 + 0x3C) = 2.0f;
    *(s32 *)(s1 + 0x40) = 1;
    *(u8 *)(s1 + 0x45) = 0;
    *(u8 *)(s1 + 0x44) = 0;
    *(f32 *)(s1 + 0x34) = ((((f32)r / D_0038497C) * D_00384980) + D_00384984) * f0;
    *(s32 *)(d + 0x3D40) = *(s32 *)(d + 0x3D40) + 1;
}
