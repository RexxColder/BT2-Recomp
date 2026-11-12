#include "common.h"

extern s32 D_00387930;
extern f32 D_00385978;
extern f32 D_0038597C;
extern f32 D_00385980;
extern f32 D_00385984;
extern f32 D_00385988;
extern f32 D_0038598C;
extern f32 D_00385990;
extern f32 D_00385994;
extern f32 D_00385998;
extern f32 D_0038599C;
extern f32 D_003859A0;
extern f32 D_003859A4;
extern f32 D_003859A8;

s32 func_00211288(s32 a0);
void *BtlChar_GetPos(s32 a0);
s32 BtlObjXf_Update(s32 a0);
void BtlOpp_GetDelta(s32 a0, f32 *a1);
void Vec3_RotateAxis(f32 a, void *b, void *c, f32 *d);
void func_003126C8(void *a0, f32 *a1);
void sceVu0Normalize(f32 *a, f32 *b);
f32 sinf(f32 x);
f32 cosf(f32 x);
f32 func_00212970();

void func_00209D78(u32 arg0, void *arg1) {
    s64 fr[4];
    f32 *v0;
    f32 *v1;
    s32 h;
    s32 r;
    f32 f0;

    v0 = (f32 *)fr;
    v1 = (f32 *)((u8 *)fr + 0x10);

    if (D_00387930 == 0 || arg0 >= 2) {
        return;
    }

    h = func_00211288(arg0);
    v1[0] = sinf(*(f32 *)((u8 *)BtlChar_GetPos(h) + 0x14));
    *(s32 *)&v1[1] = 0;
    v1[2] = cosf(*(f32 *)((u8 *)BtlChar_GetPos(h) + 0x14));
    *(s32 *)&v1[3] = 0;

    v0[0] = v1[2];
    v0[1] = 0.0f;
    v0[2] = -v1[0];
    *(s32 *)&v0[3] = 0;
    func_003126C8(arg1, v1);
    r = BtlObjXf_Update(h);

    switch (r) {
    case 0x110:
        Vec3_RotateAxis(func_00212970() * D_00385980 + D_00385980, arg1, arg1, v0);
        Vec3_RotateAxis(func_00212970() * D_00385984 + 0.5f, arg1, arg1, v1);
        return;
    case 0x10F:
        Vec3_RotateAxis(func_00212970(h) * D_00385978 + D_00385978, arg1, arg1, v0);
        Vec3_RotateAxis(-(func_00212970() * D_0038597C + 0.5f), arg1, arg1, v1);
        return;
    case 0x111:
    case 0x24:
        Vec3_RotateAxis(func_00212970() * 0.5f + 2.5f, arg1, arg1, v0);
        f0 = func_00212970();
        Vec3_RotateAxis(f0 * D_00385988 - D_0038598C, arg1, arg1, v1);
        return;
    case 0x112:
        Vec3_RotateAxis(func_00212970(h) * D_00385990 + D_00385990, arg1, arg1, v0);
        f0 = func_00212970();
        Vec3_RotateAxis(f0 * D_00385994 - D_00385998, arg1, arg1, v1);
        return;
    default:
        BtlOpp_GetDelta(h, v1);
        sceVu0Normalize(v1, v1);
        f0 = -v1[0];
        v0[0] = v1[2];
        v0[1] = 0.0f;
        v0[2] = f0;
        *(s32 *)&v0[3] = 0;
        sceVu0Normalize(v0, v0);
        func_003126C8(arg1, v1);
        Vec3_RotateAxis(func_00212970() * D_0038599C - D_003859A0, arg1, arg1, v0);
        Vec3_RotateAxis(func_00212970() * D_003859A4 - D_003859A8, arg1, arg1, v1);
        return;
    }
}
