#include "common.h"

f32 Mathf_Asin(f32 x);
f32 atan2f(f32 y, f32 x);
s32 Vec3_Normalize(s32 arg0, s32 arg1);
void Mtx_StoreIdentity(s32 arg0);
void Mtx_RotateX(f32 f0, s32 arg0, s32 arg1);
void Mtx_RotateY(f32 f0, s32 arg0, s32 arg1);
void func_001A2308(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

s32 func_001A3E90(u8 *arg0, u8 *arg1) {
    u8 *p20;
    u8 *m0;
    s32 i;
    s32 n;

    p20 = arg1 + 0x20;
    m0 = *(u8 **)(arg1 + 0x38);
    *(s32 *)(arg0 + 0x50) = *(s32 *)(arg0 + 0x50) | 1;
    Vec3_Normalize((s32)p20, (s32)p20);
    Mtx_StoreIdentity((s32)(arg0 + 0x80));
    Mtx_RotateX(Mathf_Asin(*(f32 *)(arg1 + 0x24)), (s32)(arg0 + 0xC0), (s32)(arg0 + 0x80));
    Mtx_RotateY(atan2f(-*(f32 *)(arg1 + 0x20), -*(f32 *)(arg1 + 0x28)), (s32)(arg0 + 0xC0), (s32)(arg0 + 0xC0));
    *(s32 *)(arg0 + 0x6C) = 0;
    *(s32 *)(arg0 + 0x70) = 0;
    n = (m0[1] != 0) ? 2 : 1;
    *(s32 *)(arg0 + 0x100) = n;
    for (i = 0; i < *(s32 *)(arg0 + 0x100); i++) {
        func_001A2308((s32)arg0, i, *(s32 *)(arg1 + 0x34), *(s32 *)(arg1 + 0x30) + i, *(s32 *)(arg1 + 0x30) + i);
    }
    return 1;
}
