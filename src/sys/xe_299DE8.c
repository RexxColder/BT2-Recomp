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


/* Slerp from the identity to q: the same axis with the angle scaled by t. */
void Quat_SlerpIdentity(Quat *out, Quat *q, float t) {
    float w;
    float angle;
    float s;

    w = fabsf(q->w);
    if (w > 1.0f) {
        w = 1.0f;
    }
    angle = Mathf_Acos(w);
    s = sinf(angle);
    if (s < 0.000001f) {
        out->x = 0.0f;
        out->y = 0.0f;
        out->z = 0.0f;
        out->w = 1.0f;
    } else {
        float inv = 1.0f / s;
        float ka = sinf(angle * (1.0f - t)) * inv;
        float kb = sinf(angle * t) * inv;

        out->x = q->x * kb;
        out->y = q->y * kb;
        out->z = q->z * kb;
        out->w = ka + q->w * kb;
    }
}

/* Rotation angle of q in radians, 2 * acos(w). */
float Quat_GetAngle(Quat *q) {
    float w = q->w;

    if (w < -1.0f) {
        w = -1.0f;
    }
    if (w > 1.0f) {
        w = 1.0f;
    }
    return Mathf_Acos(w) * 2.0f;
}

/* Conjugate: negated vector part. */
void Quat_Conjugate(Quat *out, Quat *q) {
    out->x = -q->x;
    out->y = -q->y;
    out->z = -q->z;
    out->w = q->w;
}

/* Inverse: conjugate divided by the squared norm. */
void Quat_Inverse(Quat *out, Quat *q) {
    float inv = 1.0f / Quat_LengthSq(q);

    out->x = -q->x * inv;
    out->y = -q->y * inv;
    out->z = -q->z * inv;
    out->w = q->w * inv;
}

/* Hamilton product out = a * b; out may alias either operand. */
void Quat_Mul(Quat *out, Quat *a, Quat *b) {
    Quat unused; /* never referenced, but it is what gives the function its 0x10 frame */
    float x, y, z, w;

    w = a->w * b->w - a->x * b->x - a->y * b->y - a->z * b->z;
    x = a->w * b->x + a->x * b->w + a->y * b->z - a->z * b->y;
    y = a->w * b->y - a->x * b->z + a->y * b->w + a->z * b->x;
    z = a->w * b->z + a->x * b->y - a->y * b->x + a->z * b->w;
    out->x = x;
    out->y = y;
    out->z = z;
    out->w = w;
}
