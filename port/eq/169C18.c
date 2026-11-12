#include "common.h"

f32 BtlCharApi_GetHeight(s32 arg0);
void func_0014EAE8(s32 arg0, void *arg1);
void func_00168EE8(void *arg0);
void *func_001F3758(void *arg0);
s32 func_0020B3D0(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern f32 D_0038483C;
extern f32 D_00384840;

void func_00169C18(u8 *arg0, u8 *arg1) {
    u8 *s3;
    u8 *s1;
    s32 s2;
    s32 v;
    f32 f0;

    s3 = *(u8 **)(arg0 + 0x38);
    s2 = *(s32 *)((u8 *)func_001F3758(arg0) + 0x38);
    memset(s3, 0, 0x1140);
    *(u8 **)(s3 + 0xB0) = arg1;
    s1 = *(u8 **)(arg1 + 0x24);
    v = func_0020B3D0(*(s32 *)arg1);
    *(s32 *)(s3 + 8) = v;
    *(f32 *)(s3 + 0x18) = *(f32 *)(s1 + 8);
    *(f32 *)(s3 + 0x1C) = *(f32 *)(s1 + 4);
    f0 = BtlCharApi_GetHeight(v) / D_0038483C;
    *(f32 *)(s3 + 0x20) = f0;
    if (f0 < D_00384840) {
        *(f32 *)(s3 + 0x20) = D_00384840;
    }
    func_0014EAE8(s2, s3 + 0xB4);
    func_00168EE8(arg0);
}
