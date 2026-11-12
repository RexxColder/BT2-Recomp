#include "common.h"

extern void *gBtlCamView;

void *memset(void *arg0, s32 arg1, s32 arg2);
void ColBox_GetCenter(s32 arg0, s32 arg1);
void ColBox_GetHalf(s32 arg0, s32 arg1);
void Vu0Screen_StoreMtx(s32 arg0);
void func_0029E2E0(s32 arg0, s32 arg1, s32 arg2);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);

s32 func_00264020(u8 *arg0) {
    u8 sp[0x120];
    u8 *obj;
    u8 *rp;
    u8 *cam;
    f32 x;
    f32 y;
    f32 z;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 one;
    f32 fx;
    f32 fy;
    f32 fz;
    f32 t;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 v1;

    s1 = 0;
    s2 = 0;
    s3 = 7;
    obj = arg0 + 0xF90;
    memset(sp + 0x100, 0, 0x14);
    ColBox_GetCenter((s32)obj, (s32)(sp + 0xA0));
    ColBox_GetHalf((s32)obj, (s32)(sp + 0xB0));

    x = *(f32 *)(sp + 0xB0);
    y = *(f32 *)(sp + 0xB4);
    z = *(f32 *)(sp + 0xB8);
    nx = -x;
    ny = -y;
    nz = -z;
    one = 1.0f;
    *(f32 *)(sp + 0x54) = y;
    *(f32 *)(sp + 0x60) = x;
    *(f32 *)(sp + 0x00) = x;
    *(f32 *)(sp + 0x70) = nx;
    *(f32 *)(sp + 0x74) = ny;
    *(f32 *)(sp + 0x04) = y;
    *(f32 *)(sp + 0x08) = z;
    *(f32 *)(sp + 0x0C) = one;
    *(f32 *)(sp + 0x10) = nx;
    *(f32 *)(sp + 0x14) = y;
    *(f32 *)(sp + 0x18) = z;
    *(f32 *)(sp + 0x1C) = one;
    *(f32 *)(sp + 0x20) = x;
    *(f32 *)(sp + 0x24) = ny;
    *(f32 *)(sp + 0x28) = z;
    *(f32 *)(sp + 0x2C) = one;
    *(f32 *)(sp + 0x30) = nx;
    *(f32 *)(sp + 0x34) = ny;
    *(f32 *)(sp + 0x38) = z;
    *(f32 *)(sp + 0x3C) = one;
    *(f32 *)(sp + 0x40) = x;
    *(f32 *)(sp + 0x44) = y;
    *(f32 *)(sp + 0x48) = nz;
    *(f32 *)(sp + 0x4C) = one;
    *(f32 *)(sp + 0x50) = nx;
    *(f32 *)(sp + 0x58) = nz;
    *(f32 *)(sp + 0x5C) = one;
    *(f32 *)(sp + 0x64) = ny;
    *(f32 *)(sp + 0x68) = nz;
    *(f32 *)(sp + 0x6C) = one;
    *(f32 *)(sp + 0x78) = nz;
    *(f32 *)(sp + 0x7C) = one;
    Vu0Screen_StoreMtx((s32)(sp + 0xC0));

    rp = sp;
    do {
        func_00312638((s32)rp, (s32)rp, (s32)(sp + 0xA0));
        func_0029E2E0((s32)(sp + 0x80), (s32)(sp + 0xC0), (s32)rp);
        v1 = s1;
        fx = *(f32 *)(sp + 0x80) - 1792.0f;
        fy = *(f32 *)(sp + 0x84) - 1824.0f;
        fz = *(f32 *)(sp + 0x88);
        *(f32 *)(sp + 0x90) = fx;
        *(f32 *)(sp + 0x94) = fy;
        *(f32 *)(sp + 0x98) = fz;
        if (fz < 0.0f) {
            s1 += 1;
            *(s32 *)(sp + 0x110) = *(s32 *)(sp + 0x110) + 1;
        }

        cam = (u8 *)gBtlCamView;
        t = (f32)*(s32 *)(cam + 0x200);
        if (fx < t) {
            *(s32 *)(sp + 0x100) = *(s32 *)(sp + 0x100) + 1;
            s1 += 1;
        }
        t = (f32)(*(s32 *)(cam + 0x204) + 1);
        if (t < fx) {
            *(s32 *)(sp + 0x104) = *(s32 *)(sp + 0x104) + 1;
            s1 += 1;
        }
        t = (f32)*(s32 *)(cam + 0x208);
        if (fy < t) {
            *(s32 *)(sp + 0x108) = *(s32 *)(sp + 0x108) + 1;
            s1 += 1;
        }
        t = (f32)(*(s32 *)(cam + 0x20C) + 1);
        if (t < fy) {
            *(s32 *)(sp + 0x10C) = *(s32 *)(sp + 0x10C) + 1;
            s1 += 1;
        }
        v1 = v1 ^ s1;
        if (v1 != 0) {
            s2 += 1;
        }

        s3 -= 1;
        rp += 0x10;
    } while (s3 >= 0);

    if (s2 != 8) {
        return 0;
    }
    if (*(s32 *)(sp + 0x100) == s2 || *(s32 *)(sp + 0x104) == s2 || *(s32 *)(sp + 0x108) == s2 ||
        *(s32 *)(sp + 0x10C) == s2 || *(s32 *)(sp + 0x110) == s2) {
        return 1;
    }
    return 0;
}
