#include "common.h"

void func_001E99B8(s32 arg0, s32 arg1);
void func_001E9AE8(s32 arg0, s32 arg1);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
void Mtx_StoreIdentity(s32 arg0);
f32 Mathf_Asin(f32 farg0);
f32 EftMath_WrapAngle(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);
void Mtx_RotateX(f32 farg0, s32 arg0, s32 arg1);
void Mtx_RotateY(f32 farg0, s32 arg0, s32 arg1);
void Mtx_Translate(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
void func_00129D68(s32 arg0, s32 arg1, f32 arg2, f32 arg3);
void func_00129C28(s32 arg0, s32 arg1);
f32 func_00129CD8(s32 arg0, s32 arg1);

/* One effect-object update step: pose from the object's angles, flag-driven sub-updates,
   timing and fade (fields at +0x108/+0x10C), and the distance pass over the particle list at +0x180. */
void func_001E96B8(u8 *arg0) {
    u8 *e = arg0;
    u8 *d;
    f32 v24[4];
    f32 v25[4];
    f32 v26[4];
    f32 t;
    f32 f21;
    f32 dot;
    s32 s3 = 0;
    s32 flags;
    u8 *p;
    f32 f0;

    d = *(u8 **)e;
    __builtin_memset(v24, 0, 16);
    __builtin_memset(v25, 0, 16);
    __builtin_memset(v26, 0, 16);

    t = *(f32 *)(e + 0x108) / *(f32 *)(e + 0x10C);
    if (*(f32 *)(d + 0x18) <= t) {
        s3 = (t < 1.0f) ? 1 : 0;
    }

    flags = *(s32 *)(d + 0x98);
    if ((flags & 1) != 0) {
        func_001E99B8((s32)e, s3);
        flags = *(s32 *)(d + 0x98);
    }
    if ((flags & 2) != 0) {
        func_001E9AE8((s32)e, s3);
    }

    func_00129BD0((s32)v25, (s32)(e + 0x70), *(f32 *)(e + 0xC4));
    Mtx_StoreIdentity((s32)(e + 0x10));

    f0 = EftMath_WrapAngle(Mathf_Asin(-*(f32 *)(e + 0x94)));
    f21 = f0;
    f0 = atan2f(*(f32 *)(e + 0x90), *(f32 *)(e + 0x98));
    f0 = EftMath_WrapAngle(f0);
    Mtx_RotateX(f21, (s32)(e + 0x10), (s32)(e + 0x10));
    Mtx_RotateY(f0, (s32)(e + 0x10), (s32)(e + 0x10));
    Mtx_Translate((s32)(e + 0x10), (s32)(e + 0x10), (s32)(e + 0x80));

    flags = *(u16 *)(e + 0x124);
    if ((flags & 0x40) == 0) {
        Vec3_Add((s32)(e + 0x50), (s32)(e + 0x50), (s32)(e + 0x60));
        flags = *(u16 *)(e + 0x124);
    }

    if (t < *(f32 *)(d + 0x10)) {
        *(f32 *)(e + 0x5C) = *(f32 *)(e + 0x5C) + *(f32 *)(e + 0xD4);
    }

    if ((flags & 0x8) != 0) {
        f0 = *(f32 *)(e + 0x5C) + *(f32 *)(e + 0xD8);
        *(f32 *)(e + 0x5C) = f0;
        if (f0 <= 0.0f) {
            *(f32 *)(e + 0x5C) = 0.0f;
            *(u16 *)(e + 0x124) = (u16)(flags | 4);
        }
    } else {
        if (*(f32 *)(d + 0x14) <= t && t < 1.0f) {
            *(f32 *)(e + 0x5C) = *(f32 *)(e + 0x5C) + *(f32 *)(e + 0xD8);
        }
    }
    func_00129D68((s32)(e + 0x50), (s32)(e + 0x50), 0.0f, 255.0f);

    p = *(u8 **)(e + 0x180);
    while (p != 0) {
        func_00129C28((s32)v24, (s32)p);
        func_00129C28((s32)p, (s32)v25);
        func_00129C28((s32)v25, (s32)v24);
        Vec3_Sub((s32)v26, (s32)p, (s32)v24);
        dot = func_00129CD8((s32)v26, (s32)v26);
        *(f32 *)(p + 0x10) = __builtin_sqrtf(__builtin_fabsf(dot));
        p = *(u8 **)(p + 0x18);
    }

    *(f32 *)(e + 0x108) = *(f32 *)(e + 0x108) + 1.0f;
    if (*(f32 *)(e + 0x10C) <= *(f32 *)(e + 0x108)) {
        *(u16 *)(e + 0x124) = (u16)(*(u16 *)(e + 0x124) | 4);
    }
}
