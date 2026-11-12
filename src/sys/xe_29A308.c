#include "common.h"
#include "sys/math3d.h"

extern float sqrtf(float x);
extern float fabsf(float x);
extern float sinf(float x);
extern float cosf(float x);
extern float atan2f(float y, float x);
extern float Mathf_Acos(float x); /* acosf with the argument clamped to [-1, 1] */
extern float Mathf_Asin(float x); /* asinf with the argument clamped to [-1, 1] */

extern void Vec4_Copy(void *dst, void *src);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern void Vec3_Cross(Vec4 *dst, Vec4 *a, Vec4 *b);
extern float Vec3_Dot(Vec4 *a, Vec4 *b);
extern void Mtx_StoreIdentity(Mtx44 *m);


/* Copies q, but rebuilds it with rotation angle maxAngle when it turns further than that. */
void Quat_LimitAngle(Quat *out, Quat *q, float maxAngle) {
    if (fabsf(maxAngle) >= 3.14159265f) {
        Vec4_Copy(out, q);
        return;
    }
    if (fabsf(q->w) > 0.999999f) {
        Vec4_Copy(out, q);
        return;
    }
    if (cosf(maxAngle * 0.5f) < q->w) {
        Vec4_Copy(out, q);
        return;
    }
    Quat_FromAxisAngle(out, q->x, q->y, q->z, maxAngle);
}
