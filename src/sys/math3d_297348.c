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

/* Cubic Hermite spline on xyz: p0/p1 are the end points, t0/t1 the tangents, t in [0, 1]. */
void Vec3_Hermite(Vec4 *out, Vec4 *p0, Vec4 *p1, Vec4 *t0, Vec4 *t1, float t) {
    float h0 = (t - 1.0f) * (t - 1.0f) * (2.0f * t + 1.0f);
    float h1 = t * t * (3.0f - 2.0f * t);
    float h2 = (1.0f - t) * (1.0f - t) * t;
    float h3 = (t - 1.0f) * t * t;

    out->x = h0 * p0->x + h1 * p1->x + h2 * t0->x + h3 * t1->x;
    out->y = h0 * p0->y + h1 * p1->y + h2 * t0->y + h3 * t1->y;
    out->z = h0 * p0->z + h1 * p1->z + h2 * t0->z + h3 * t1->z;
}

/* Sets q to (0, 0, 0, 1). */
void Quat_SetIdentity(Quat *q);

/* Rotation of `angle` radians about the axis (x, y, z), which need not be normalised; identity for a null axis. */
void Quat_FromAxisAngle(Quat *out, float x, float y, float z, float angle);

/* Shortest rotation taking direction `from` to direction `to`, scaled by t (1 = the full rotation). */
void Quat_FromVectors(Quat *out, Vec4 *from, Vec4 *to, float t);

/* Squared norm of the four components. */
float Quat_LengthSq(Quat *q);

/* Norm of the four components. */
float Quat_Length(Quat *q);

/* Slerp from the identity to q: the same axis with the angle scaled by t. */
void Quat_SlerpIdentity(Quat *out, Quat *q, float t);

/* Rotation angle of q in radians, 2 * acos(w). */
float Quat_GetAngle(Quat *q);

/* Conjugate: negated vector part. */
void Quat_Conjugate(Quat *out, Quat *q);

/* Inverse: conjugate divided by the squared norm. */
void Quat_Inverse(Quat *out, Quat *q);

/* Hamilton product out = a * b; out may alias either operand. */
void Quat_Mul(Quat *out, Quat *a, Quat *b);

/* Four-component dot product. */
static inline float Quat_Dot(Quat *a, Quat *b);

/* Spherical interpolation from a (t = 0) to b (t = 1) along the shorter arc. */
void Quat_Slerp(Quat *out, Quat *a, Quat *b, float t);

/* out = r * q * r^-1: q expressed in the frame rotated by r. */
void Quat_ConjugateBy(Quat *out, Quat *q, Quat *r);

/* Copies q, but rebuilds it with rotation angle maxAngle when it turns further than that. */
void Quat_LimitAngle(Quat *out, Quat *q, float maxAngle);

/* out = q scaled by 1 / |out| (sic: the length is taken from out, so this is only right in place). */
void Quat_Normalize(Quat *out, Quat *q);

/* "Smallest three" compression: drops the largest component (index in bits 60..63, made positive)
   and stores the other three as 20-bit fields. */
u64 Quat_Pack(Quat *q);

/* Inverse of Quat_Pack: the dropped component is rebuilt as sqrt(1 - sum of squares). */
void Quat_Unpack(Quat *out, u64 packed);

/* Rotation matrix of a unit quaternion (identity elsewhere). */
void Quat_ToMtx(Mtx44 *out, Quat *q);

/* Quaternion from Euler angles (radians about x, y, z): qy * (qx * qz). */
void Quat_FromEuler(Quat *out, Vec4 *angles);

/* Euler angles of a rotation matrix (the inverse of Quat_FromEuler + Quat_ToMtx), with the two gimbal-lock cases. */
void Mtx_ToEuler(Vec4 *out, Mtx44 *m);

/* Euler angles of a quaternion, through the matrix. */
void Quat_ToEuler(Vec4 *out, Quat *q);

/* Quaternion of a rotation matrix (trace method, falling back to the largest diagonal element). */
void Quat_FromMtx(Quat *out, Mtx44 *m);
