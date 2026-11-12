#include "common.h"
#include "sys/rigid.h"

#define RIGID_ABS(a) ((a) < 0.0f ? -(a) : (a))

extern void *memset(void *dst, s32 value, u32 size);
extern f32 sqrtf(f32 x);

extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern void Vec3_Cross(Vec4 *dst, Vec4 *a, Vec4 *b);
extern f32 Vec3_Dot(Vec4 *a, Vec4 *b);
extern void Mtx_StoreIdentity(Mtx44 *dst);
extern void Mtx_Copy(Mtx44 *dst, Mtx44 *src);              /* 4x4 matrix copy */
extern f32 Vec3_Dist(Vec4 *a, Vec4 *b);                     /* distance between two points */
extern f32 Mathf_Sqrt(f32 x);
extern void ColSphere_Set(RigidSphere *out, Vec4 *center, f32 radius); /* fills a sphere */


/* Moves the centres of both collision spheres to the body position. */
void Rigid_SyncSpheres(RigidBody *body) {
    Vec4_Copy(&body->prevSphere.center, &body->pos);
    Vec4_Copy(&body->sphere.center, &body->pos);
}
