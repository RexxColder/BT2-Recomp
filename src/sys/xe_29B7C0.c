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


/* Euler angles of a quaternion, through the matrix. */
void Quat_ToEuler(Vec4 *out, Quat *q) {
    Mtx44 m;

    Quat_ToMtx(&m, q);
    Mtx_ToEuler(out, &m);
}

/* Quaternion of a rotation matrix (trace method, falling back to the largest diagonal element). */
void Quat_FromMtx(Quat *out, Mtx44 *m) {
    float tr = m->m[0][0] + 1.0f + m->m[1][1] + m->m[2][2];
    float s;

    if (tr > 0.0001f) {
        s = 0.5f / sqrtf(tr);
        out->w = 0.25f / s;
        out->x = (m->m[1][2] - m->m[2][1]) * s;
        out->y = (m->m[2][0] - m->m[0][2]) * s;
        out->z = (m->m[0][1] - m->m[1][0]) * s;
    } else if (m->m[0][0] > m->m[1][1] && m->m[0][0] > m->m[2][2]) {
        s = sqrtf(m->m[0][0] + 1.0f - m->m[1][1] - m->m[2][2]) * 2.0f;
        out->x = s * 0.25f;
        out->y = (m->m[1][0] + m->m[0][1]) / s;
        out->z = (m->m[2][0] + m->m[0][2]) / s;
        out->w = (m->m[1][2] - m->m[2][1]) / s;
    } else if (m->m[1][1] > m->m[2][2]) {
        s = sqrtf(m->m[1][1] + 1.0f - m->m[0][0] - m->m[2][2]) * 2.0f;
        out->x = (m->m[1][0] + m->m[0][1]) / s;
        out->y = s * 0.25f;
        out->z = (m->m[2][1] + m->m[1][2]) / s;
        out->w = (m->m[2][0] - m->m[0][2]) / s;
    } else {
        s = sqrtf(m->m[2][2] + 1.0f - m->m[0][0] - m->m[1][1]) * 2.0f;
        out->x = (m->m[2][0] + m->m[0][2]) / s;
        out->y = (m->m[2][1] + m->m[1][2]) / s;
        out->z = s * 0.25f;
        out->w = (m->m[0][1] - m->m[1][0]) / s;
    }
}
