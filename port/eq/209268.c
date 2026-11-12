#include "common.h"

extern s32 D_00387930;
extern f32 D_00385964;
extern f32 D_00385968;
extern f32 D_0038596C;
extern u8 D_002C3630[];

s32 func_00211288(s32 arg0);
void func_00210F30(void *arg0, void *arg1, s32 arg2);
void func_003126C8(void *arg0, void *arg1);
void func_00312650(void *arg0, void *arg1, void *arg2);
f32 func_0029DFD0(void *arg0);
void func_00312680(void *arg0, void *arg1, f32 farg0);
s32 BtlChar_GetPos(s32 arg0);
f32 sinf(f32 farg0);
f32 cosf(f32 farg0);
void BtlOpp_GetDelta(s32 arg0, void *arg1);
s32 BtlCharApi_IsInTechnique(s32 arg0);
void sceVu0Normalize(void *arg0, void *arg1);
void Vec3_RotateAxis(void *arg0, void *arg1, void *arg2, f32 farg0);
void Vec3_RotateY(void *arg0, void *arg1, f32 farg0);

#define FP(p, o) (*(f32 *)((p) + (o)))

/* Unit direction vector out (xyz) for character idx, clamped so its y component lies in [sin(a), sin(b)]. */
void func_00209268(s32 idx, f32 *out, void *p2, s32 p3, f32 a, f32 b) {
    f32 delta[4];
    f32 axis[4];
    f32 lo, hi, f3, ox, oz, r, k, dist;
    f32 limit;
    s32 obj;
    u8 *pos;

    if (D_00387930 == 0 || idx < 0 || idx >= 2) {
        func_003126C8(out, D_002C3630);
        return;
    }
    obj = func_00211288(idx);
    limit = D_00385964;
    func_00210F30((void *)obj, delta, p3);
    func_00312650(out, delta, p2);
    dist = func_0029DFD0(out);
    if (dist < limit) {
        pos = (u8 *)BtlChar_GetPos(obj);
        out[1] = 0.0f;
        out[0] = sinf(FP(pos, 0x14));
        pos = (u8 *)BtlChar_GetPos(obj);
        out[3] = 0.0f;
        out[2] = cosf(FP(pos, 0x14));
        return;
    }
    func_00312680(out, out, 1.0f / dist);
    BtlOpp_GetDelta(obj, delta);
    if (BtlCharApi_IsInTechnique(idx)) {
        ox = out[0];
        oz = out[2];
        if (limit < __builtin_fabsf(ox) || limit < __builtin_fabsf(oz)) {
            axis[0] = oz;
            axis[1] = 0.0f;
            axis[2] = -ox;
            axis[3] = 0.0f;
            sceVu0Normalize(axis, axis);
            Vec3_RotateAxis(out, out, axis, FP((u8 *)obj, 0xA44));
            Vec3_RotateY(out, out, FP((u8 *)obj, 0xA48));
        }
    }
    ox = out[0];
    oz = out[2];
    if (ox * delta[0] + oz * delta[2] < 0.0f) {
        out[0] = -ox;
        out[2] = -oz;
    }
    lo = sinf(a);
    hi = sinf(b);
    f3 = out[1];
    if (f3 < lo) {
        if (__builtin_fabsf(f3) < D_00385968) {
            k = __builtin_sqrtf(__builtin_fabsf(1.0f - lo * lo)) / __builtin_sqrtf(__builtin_fabsf(1.0f - f3 * f3));
            oz = out[2];
            ox = out[0];
            out[1] = lo;
            out[2] = oz * k;
            out[0] = ox * k;
            f3 = lo;
        } else {
            r = __builtin_sqrtf(__builtin_fabsf(1.0f - lo * lo));
            pos = (u8 *)BtlChar_GetPos(obj);
            out[1] = lo;
            out[0] = r * sinf(FP(pos, 0x14));
            pos = (u8 *)BtlChar_GetPos(obj);
            out[2] = r * cosf(FP(pos, 0x14));
            f3 = out[1];
        }
    }
    if (hi < f3) {
        if (__builtin_fabsf(f3) < D_0038596C) {
            k = __builtin_sqrtf(__builtin_fabsf(1.0f - hi * hi)) / __builtin_sqrtf(__builtin_fabsf(1.0f - f3 * f3));
            oz = out[2];
            ox = out[0];
            out[1] = hi;
            out[2] = oz * k;
            out[0] = ox * k;
        } else {
            r = __builtin_sqrtf(__builtin_fabsf(1.0f - hi * hi));
            pos = (u8 *)BtlChar_GetPos(obj);
            out[1] = hi;
            out[0] = r * sinf(FP(pos, 0x14));
            pos = (u8 *)BtlChar_GetPos(obj);
            out[2] = r * cosf(FP(pos, 0x14));
        }
    }
    out[3] = 0.0f;
}
