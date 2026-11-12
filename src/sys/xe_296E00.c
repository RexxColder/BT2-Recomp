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


/* Start of a frame: remembers the flags and the transform, keeps only the low byte of the flags. */
void Rigid_BeginFrame(RigidBody *body) {
    body->prevFlags = body->flags;
    Vec4_Copy(&body->prevPos, &body->pos);
    Mtx_Copy(&body->prevRot, &body->rot);
    body->flags &= 0xFF;
    body->unk210 = 0;
}

/* Sets the linear velocity and replaces the body-space angular velocity with that of angVel's Y part only. */
void Rigid_SetVelocity(RigidBody *body, Vec4 *vel, Vec4 *angVel) {
    Vec4 a;
    Vec4 b;
    Vec4 w;

    Vec4_Copy(&w, angVel);
    Mat3_MulVecRows(&a, &w, &body->rot);
    Mat3_MulVecCols(&b, &a, &body->rot);
    body->angVelBody.x -= b.x;
    body->angVelBody.y -= b.y;
    body->angVelBody.z -= b.z;
    w.x = 0.0f;
    w.z = 0.0f;
    w.y = angVel->y;
    Mat3_MulVecCols(&b, &w, &body->rot);
    body->angVelBody.x += b.x;
    body->angVelBody.y += b.y;
    body->angVelBody.z += b.z;
    body->vel.x = vel->x;
    body->vel.y = vel->y;
    body->vel.z = vel->z;
}
