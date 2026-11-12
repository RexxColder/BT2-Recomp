#include "common.h"

void *memcpy(void *, const void *, unsigned int);
void Vec3_Normalize(f32 *arg0, f32 *arg1);
void Vec3_Cross(f32 *arg0, f32 *arg1, f32 *arg2);
f32 func_00129CD8(f32 *arg0, f32 *arg1);
void Vec4_Set(f32 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
f32 sqrtf(f32 arg0);

/* 0x001DA670: copies the two vec4 inputs arg1 and arg2 to locals; an = normalize(arg1 copy), bn = normalize(arg2
 * copy), cr = cross(an, arg2 copy); d = dot(an, bn); s = sqrt(2 * (d + 1)); arg0 = (cr.x, cr.y, cr.z) / s and
 * w = s * 0.5. */
void func_001DA670(f32 *arg0, f32 *arg1, f32 *arg2) {
    f32 ac[4];
    f32 bc[4];
    f32 an[4];
    f32 bn[4];
    f32 cr[4];
    f32 d;
    f32 s;
    f32 inv;

    memcpy(ac, arg1, 16);
    memcpy(bc, arg2, 16);
    Vec3_Normalize(an, ac);
    Vec3_Normalize(bn, bc);
    Vec3_Cross(cr, an, bc);
    d = func_00129CD8(an, bn);
    s = sqrtf((d + 1.0f) + (d + 1.0f));
    inv = 1.0f / s;
    Vec4_Set(arg0, cr[0] * inv, cr[1] * inv, cr[2] * inv, s * 0.5f);
}
