#include "common.h"

void *memset(void *arg0, s32 arg1, s32 arg2);
s32 func_001F3758(s32 arg0, s32 arg1);
f32 func_00209D20(s32 arg0);
void func_00132C68(s32 arg0, s32 arg1);
s32 func_0020B3D0(s32 arg0);
void func_00208798(s32 arg0, s32 arg1);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
void func_00129C28(s32 arg0, s32 arg1);
void func_001A1168(s32 arg0);
void func_001A12D8(s32 arg0, f32 farg0);
void func_0014EAE8(s32 arg0, s32 arg1);
s32 func_001A1280(s32 arg0);
f32 func_001A1348(s32 arg0);
void func_0012D3A0(s32 arg0, s32 arg1, s32 arg2);
void func_001A1298(s32 arg0, s32 arg1);

void func_0015A5D8(u8 *arg0, u8 *arg1) {
    u8 sp[0xC0];
    u8 *s2;
    u8 *v0p;
    u8 *v1p;
    u8 *r;
    s32 s3;
    s32 k;
    s32 cw;
    f32 f0;
    f32 f1;

    r = (u8 *)func_001F3758((s32)arg0, (s32)arg1);
    s2 = *(u8 **)(arg0 + 0x38);
    s3 = *(s32 *)(r + 0x38);
    memset(s2, 0, 0xA80);
    *(s32 *)(s2 + 0x80) = (s32)arg1;
    *(f32 *)(s2 + 0x08) = *(f32 *)(*(u8 **)(arg1 + 0x24) + 0x08);
    *(f32 *)(s2 + 0x0C) = *(f32 *)(*(u8 **)(arg1 + 0x24) + 0x04);

    if (*(s32 *)(*(u8 **)(arg1 + 0x20)) == 0xD2) {
        v1p = s2 + 0x20;
        v0p = s2 + 0x50;
        f0 = func_00209D20(*(s32 *)arg1);
        *(f32 *)(s2 + 0x04) = f0;
        func_00132C68(*(s32 *)arg1, (s32)v0p);
        cw = func_0020B3D0(*(s32 *)arg1);
        func_00208798(cw, (s32)sp);
        Vec3_Sub((s32)v1p, (s32)sp, (s32)v0p);
        *(f32 *)(s2 + 0x2C) = 1.0f;
        Vec3_Normalize((s32)v1p, (s32)v1p);

        *(s32 *)(sp + 0x50) = *(s32 *)arg1;
        memset(sp + 0x60, 0, 0x10);
        memset(sp + 0x70, 0, 0x10);
        *(s32 *)(sp + 0x84) = s3;
        *(s32 *)(sp + 0x80) = (s32)arg1;
        for (k = 0; k < 8; k++) {
            *(s64 *)(sp + 0x10 + 8 * k) = *(s64 *)(sp + 0x50 + 8 * k);
        }
        func_00129C28((s32)(sp + 0x20), (s32)v0p);
        func_00129C28((s32)(sp + 0x30), (s32)v1p);
        func_001A1168((s32)(sp + 0x10));
        func_001A12D8(*(s32 *)arg1, *(f32 *)(s2 + 0x04));
    } else {
        f0 = func_00209D20(*(s32 *)arg1);
        *(f32 *)(s2 + 0x04) = f0;
        cw = func_001A1280(*(s32 *)arg1);
        if (cw != 0) {
            f0 = func_001A1348(*(s32 *)arg1);
        } else {
            f0 = *(f32 *)(s2 + 0x04) * 8.0f;
        }
        *(f32 *)(s2 + 0x10) = f0;
        v0p = s2 + 0x50;
        func_00208798(*(s32 *)arg1, (s32)v0p);
        f1 = *(f32 *)(s2 + 0x10) * 6.0f + 20.0f;
        f0 = *(f32 *)(s2 + 0x54) - f1;
        *(f32 *)(s2 + 0x54) = f0;
        func_0012D3A0((s32)(s2 + 0x20), (s32)v0p, *(s32 *)arg1);
        func_001A1298(*(s32 *)arg1, (s32)v0p);
    }
    func_0014EAE8(s3, (s32)(s2 + 0x84));
}
