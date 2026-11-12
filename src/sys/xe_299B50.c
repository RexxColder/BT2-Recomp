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


/* Rotation of `angle` radians about the axis (x, y, z), which need not be normalised; identity for a null axis. */
void Quat_FromAxisAngle(Quat *out, float x, float y, float z, float angle) {
    float len = sqrtf(x * x + y * y + z * z);

    if (len > 0.000001f) {
        float half = angle * 0.5f;
        float s = sinf(half);
        float inv = 1.0f / len;

        out->x = x * inv * s;
        out->y = y * inv * s;
        out->z = z * inv * s;
        out->w = cosf(half);
    } else {
        out->x = 0.0f;
        out->y = 0.0f;
        out->z = 0.0f;
        out->w = 1.0f;
    }
}

/* Shortest rotation taking direction `from` to direction `to`, scaled by t (1 = the full rotation). */
void Quat_FromVectors(Quat *out, Vec4 *from, Vec4 *to, float t) {
    Vec4 a;
    Vec4 b;
    Vec4 axis;
    float s;
    float inv;

    Vec3_Normalize(&a, from);
    Vec3_Normalize(&b, to);
    Vec3_Cross(&axis, &a, &b);
    s = sqrtf((Vec3_Dot(&a, &b) + 1.0f) * 2.0f);
    inv = 1.0f / s;
    out->x = axis.x * inv;
    out->y = axis.y * inv;
    out->z = axis.z * inv;
    out->w = s * 0.5f;
    if (t != 1.0f) {
        Quat_SlerpIdentity(out, out, t);
    }
}

/* Squared norm of the four components. */
float Quat_LengthSq(Quat *q) {
    return q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w;
}
