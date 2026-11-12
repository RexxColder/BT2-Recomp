#include "common.h"

extern void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
extern void func_00129BD0(void *arg0, void *arg1, f32 farg0);
extern void Vec3_Add(void *arg0, void *arg1, void *arg2);
extern void Vec3_Sub(void *arg0, void *arg1, void *arg2);
extern void Mtx_Translate(void *arg0, void *arg1, void *arg2);
extern void func_00128C58(f32 farg0, void *arg0, void *arg1);
extern f32 EftMath_WrapAngle(f32 farg0);
extern void Mtx_RotateY(f32 farg0, void *arg0, void *arg1);
extern void Mtx_RotateZ(f32 farg0, void *arg0, void *arg1);
extern void Mtx_RotateX(f32 farg0, void *arg0, void *arg1);
extern f32 atan2f(f32 farg0, f32 farg1);
extern f32 Mathf_Asin(f32 farg0);
extern void func_00129C50(void *arg0, void *arg1, void *arg2);
extern u8 *gBtlCamView;

/* Builds an oriented billboard quad for an effect: places the four corner vectors (obj+0x40..0x70)
   at +-half size, then composes the matrix (translate, scale, yaw from obj angles, aim from obj
   direction, two extra angles) and transforms each corner. Returns 1. */
s32 func_0018A5A0(u8 *obj, u8 *src, u8 *vec, f32 f0, f32 f1, f32 f2, f32 f3, f32 f4) {
    u8 sp[0x90];
    u8 *mtx = sp;
    u8 *off = sp + 0x40;
    u8 *scaled = sp + 0x50;
    u8 *sum = sp + 0x60;
    u8 *shift = sp + 0x70;
    f32 *rel = (f32 *)(sp + 0x80);
    f32 half = *(f32 *)(obj + 0x88) * 0.5f;
    f32 asin_a;
    f32 atan_b;

    __builtin_memcpy(mtx, src, 0x40);
    __builtin_memcpy(off, vec, 0x10);
    Vec4_Set(shift, f3 * half, 0.0f, f4 * half, 1.0f);
    func_00129BD0(scaled, obj, f0);
    Vec3_Add(sum, scaled, off);
    Vec3_Sub(rel, sum, gBtlCamView + 0x1F0);
    Vec4_Set(obj + 0x40, -half, 0.0f, -half, 1.0f);
    Vec4_Set(obj + 0x50, -half, 0.0f, half, 1.0f);
    Vec4_Set(obj + 0x60, half, 0.0f, -half, 1.0f);
    Vec4_Set(obj + 0x70, half, 0.0f, half, 1.0f);
    Mtx_Translate(mtx, mtx, shift);
    func_00128C58(f0, mtx, mtx);
    Mtx_RotateY(EftMath_WrapAngle(*(f32 *)(obj + 0xA4) + *(f32 *)(obj + 0xAC)), mtx, mtx);
    Mtx_RotateZ(EftMath_WrapAngle(atan2f(rel[0], rel[1])), mtx, mtx);
    asin_a = Mathf_Asin(-*(f32 *)(obj + 0x14));
    atan_b = atan2f(*(f32 *)(obj + 0x10), *(f32 *)(obj + 0x18));
    Mtx_RotateX(EftMath_WrapAngle(asin_a), mtx, mtx);
    Mtx_RotateY(EftMath_WrapAngle(atan_b), mtx, mtx);
    Mtx_Translate(mtx, mtx, scaled);
    Mtx_RotateX(EftMath_WrapAngle(f1), mtx, mtx);
    Mtx_RotateY(EftMath_WrapAngle(f2), mtx, mtx);
    Mtx_Translate(mtx, mtx, off);
    func_00129C50(obj + 0x40, mtx, obj + 0x40);
    func_00129C50(obj + 0x50, mtx, obj + 0x50);
    func_00129C50(obj + 0x60, mtx, obj + 0x60);
    func_00129C50(obj + 0x70, mtx, obj + 0x70);
    return 1;
}
