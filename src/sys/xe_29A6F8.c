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


/* "Smallest three" compression: drops the largest component (index in bits 60..63, made positive)
   and stores the other three as 20-bit fields. */
u64 Quat_Pack(Quat *q) {
    float v[4];
    s32 largest;
    s32 i;
    float best;
    u64 packed;

    Vec4_Copy(v, q);
    largest = 0;
    best = fabsf(v[0]);
    for (i = 1; i < 4; i++) {
        if (best < fabsf(v[i])) {
            best = fabsf(v[i]);
            largest = i;
        }
    }
    if (v[largest] < 0.0f) {
        v[0] = -v[0];
        v[1] = -v[1];
        v[2] = -v[2];
        v[3] = -v[3];
    }
    for (i = largest; i < 3; i++) {
        v[i] = v[i + 1];
    }
    packed = 0;
    for (i = 0; i < 3; i++) {
        s32 n = (v[i] * 0.70710677f + 0.5f) * 1048575.0f;

        if (n < 0) {
            n = 0;
        }
        if (n > 0xFFFFF) {
            n = 0xFFFFF;
        }
        packed |= (u64)n << (i * 20);
    }
    return packed | ((u64)largest << 60);
}

/* Inverse of Quat_Pack: the dropped component is rebuilt as sqrt(1 - sum of squares). */
void Quat_Unpack(Quat *out, u64 packed) {
    float v[4];
    s32 largest;
    s32 i;
    float sum;
    float w;

    largest = packed >> 60;
    for (i = 0; i < 3; i++) {
        sum = (u32)(packed >> (i * 20)) & 0xFFFFF;
        v[i] = (sum * (1.0f / 1048575.0f) - 0.5f) * 1.41421356f;
    }
    sum = 0.0f;
    for (i = 0; i < 3; i++) {
        sum += v[i] * v[i];
    }
    w = sqrtf(1.0f - sum);
    for (i = 3; i > largest; i--) {
        v[i] = v[i - 1];
    }
    v[largest] = w;
    Vec4_Copy(out, v);
}
