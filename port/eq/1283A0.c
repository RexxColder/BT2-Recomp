#include "common.h"

#define PTR(p, off) (*(u8 **)((u8 *)(p) + (off)))
#define W32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define F32(p, off) (*(f32 *)((u8 *)(p) + (off)))

s32 EftHit_GetHitCount();
s32 func_00127A58();
s32 func_0020B3D0();
s32 func_00208DE8();
void func_0019F3B0();
void func_0019F600();
s32 EftWater_GetSurfaceY();
void Vec3_Sub();
s32 Vec3_Normalize();
s32 func_00276908();
void func_001D1C78(u8 *a0, u8 *a1, s32 a2, s32 a3, f32 farg0);

void func_001283A0(u8 *obj, s32 a1, s32 pa2) {
    u8 sp[0x30];
    u8 *a;
    u8 *s1;
    u8 *v1;

    F32(PTR(obj, 0x60), 0x1C) = 1.0f;
    s1 = PTR(obj, 0x64);
    v1 = PTR(s1, 0x20);
    if (W32(v1, 0x4) != 0) {
        a = PTR(obj, 0x60);
        if (W32(a, 0x4) & 0x4000) {
            if (func_00127A58(obj) != 0) {
                func_00208DE8(func_0020B3D0(W32(obj, 0x0)), sp, 0x11);
                func_0019F3B0(sp, W32(obj, 0x4));
            } else if (EftHit_GetHitCount(obj) == 1 && !(W32(PTR(s1, 0x20), 0x2C) & 1)) {
                func_0019F600(PTR(obj, 0x60) + 0x10, W32(obj, 0x4));
            } else {
                func_0019F3B0(PTR(obj, 0x60) + 0x10, W32(obj, 0x4), pa2);
            }
        } else {
            if (!(W32(v1, 0x2C) & 1)) {
                func_0019F600(a + 0x10, W32(obj, 0x4));
            } else {
                func_0019F3B0(a + 0x10, W32(obj, 0x4), a);
            }
        }
    } else if (W32(v1, 0x2C) & 1) {
        func_0019F3B0(PTR(obj, 0x60) + 0x10, W32(obj, 0x4), pa2);
    }

    if (W32(PTR(obj, 0x60), 0x4) & 0x4) {
        EftWater_GetSurfaceY(sp + 0x20);
        Vec3_Sub(sp + 0x10, obj + 0x30, obj + 0x20);
        Vec3_Normalize(sp + 0x10, sp + 0x10);
        if (func_00276908(7) != 0) {
            if (F32(PTR(obj, 0x60), 0x14) < F32(sp, 0x20)) {
                func_001D1C78(PTR(obj, 0x60) + 0x10, sp + 0x10, W32(obj, 0x0), 0, 1.0f);
            }
        } else {
            func_001D1C78(PTR(obj, 0x60) + 0x10, sp + 0x10, W32(obj, 0x0), 0, 1.0f);
        }
    }
}
