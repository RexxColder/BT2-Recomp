#include "common.h"

extern f32 D_00384C34;
extern f32 D_00384C38;
extern f32 D_00384C3C;
extern f32 D_00384C40;
extern f32 D_00384C44;

void func_00129C28(s32 arg0, s32 arg1);
void func_00129C50(s32 arg0, s32 arg1, s32 arg2);
s32 func_0020B3D0(s32 arg0);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
s32 func_0014EAE8(s32 arg0, s32 arg1);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void Mtx_StoreIdentity(s32 arg0);
void Mtx_RotateX(f32 farg0, s32 arg0, s32 arg1);
void Mtx_RotateY(f32 farg0, s32 arg0, s32 arg1);
void Mtx_RotateZ(f32 farg0, s32 arg0, s32 arg1);
f32 Mathf_Asin(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);
s32 rand(void);

/* Spawns one emitter record: copies the 48-byte template from the record, fills its fields
   from the record's floats, then sets its orientation matrix (kind 84 aims it at the target). */
s32 func_00190F08(u8 *arg0, u8 *arg1) {
    u8 *p;
    u8 *rec = arg1;
    u8 *s4;
    u8 *s0;
    u8 *s2;
    u8 *s5;
    u8 M[0x50];   /* tamano de locales del original (antes 0x40) */
    f32 v30[4];
    s32 flags;
    s32 kind;
    s32 v17;
    f32 r;
    f32 f13;
    f32 f21;
    f32 f20;
    f32 asn;
    f32 at;

    p = *(u8 **)(arg0 + 0x38);
    s4 = *(u8 **)rec;
    __builtin_memset(p, 0, 0x850);
    __builtin_memcpy(p, rec, 48);

    flags = *(s32 *)(p + 0x30);
    *(s32 *)(p + 0x30) = flags | 1;
    if (0.0f < *(f32 *)(rec + 0x24)) {
        *(s32 *)(p + 0x30) = flags | 0x401;
        *(f32 *)(p + 0x34) = *(f32 *)(rec + 0x24) * 30.0f;
    }
    *(s32 *)(p + 0x38) = *(s32 *)(rec + 0x28);

    s0 = p + 0x810;
    s5 = p + 0x820;
    s2 = p + 0x40;
    func_00129C28((s32)s0, *(s32 *)(rec + 0x0C));
    func_00129C28((s32)s5, (s32)s0);
    func_00129C28((s32)s2, *(s32 *)(rec + 0x10));

    kind = *(s32 *)(*(u8 **)(s4 + 0x20));
    if (kind == 84) {
        *(f32 *)(p + 0x3C) = 3.0f;
        v17 = func_0020B3D0(*(s32 *)s4);
        func_00208DE8(v17, (s32)s2, 17);
        Vec3_Sub((s32)s2, (s32)s2, (s32)s5);
        Vec3_Normalize((s32)s2, (s32)s2);

        f21 = ((f32)*(s32 *)(rec + 0x14) / (f32)*(s32 *)(rec + 0x18)) * D_00384C34;
        f21 = f21 + f21;
        r = (f32)rand();
        f13 = (r / D_00384C38) * D_00384C3C + D_00384C40;
        if (D_00384C34 <= f21) {
            f21 = f21 - D_00384C44;
        }


        Vec4_Set(v30, 0.0f, f13, 1.0f - f13, 1.0f);
        Mtx_StoreIdentity((s32)M);
        Mtx_RotateZ(f21, (s32)M, (s32)M);
        func_00129C50((s32)v30, (s32)M, (s32)v30);

        asn = Mathf_Asin(-*(f32 *)(p + 0x44));
        at = atan2f(*(f32 *)(s2 + 0), *(f32 *)(p + 0x48));
        f20 = asn;
        f21 = at;
        Mtx_StoreIdentity((s32)M);
        Mtx_RotateX(f20, (s32)M, (s32)M);
        Mtx_RotateY(f21, (s32)M, (s32)M);
        func_00129C50((s32)s2, (s32)M, (s32)v30);
        Vec3_Normalize((s32)s2, (s32)s2);
        Vec3_Sub((s32)(p + 0x830), (s32)s5, (s32)s2);
        *(f32 *)(p + 0x83C) = 1.0f;
    } else {
        *(f32 *)(p + 0x3C) = 1.0f;
        func_00208DE8(*(s32 *)s4, (s32)(p + 0x830), 17);
    }

    func_00129BD0((s32)(p + 0x840), (s32)s2, *(f32 *)(rec + 0x2C));
    return func_0014EAE8(*(s32 *)(p + 4), (s32)(p + 0x60));
}
