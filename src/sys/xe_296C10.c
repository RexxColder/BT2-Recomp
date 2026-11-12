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


/* One simulation step of dt seconds: integrates the velocities, then moves and rotates the body. */
void Rigid_Step(RigidBody *body, f32 dt) {
    Vec4 pos;
    Vec4 angle;
    Mat3 rot;
    Mat3 skew;
    Mat3 delta;

    Rigid_Integrate(body, dt);
    pos.x = body->pos.x + dt * body->vel.x;
    pos.y = body->pos.y + dt * body->vel.y;
    pos.z = body->pos.z + dt * body->vel.z;
    angle.x = dt * body->angVel.x;
    angle.y = dt * body->angVel.y;
    angle.z = dt * body->angVel.z;
    Mat3_SetSkew(&skew, &angle);
    Mat3_Mul(&delta, &body->rot, &skew);
    Mat3_Add(&rot, &body->rot, &delta);
    Mat3_Orthonormalize(&rot);
    Vec4_Copy(&body->pos, &pos);
    Mtx_Copy(&body->rot, &rot);
}

/* Places the body and stops it: velocities, force and torque are cleared, previous transform = current. */
void Rigid_SetTransform(RigidBody *body, Vec4 *pos, Mtx44 *rot) {
    Vec4_Copy(&body->pos, pos);
    Mtx_Copy(&body->rot, rot);
    Vec4_Copy(&body->prevPos, &body->pos);
    Mtx_Copy(&body->prevRot, &body->rot);
    body->vel.x = 0.0f;
    body->vel.y = 0.0f;
    body->vel.z = 0.0f;
    body->vel.w = 1.0f;
    body->force.x = 0.0f;
    body->force.y = 0.0f;
    body->force.z = 0.0f;
    body->force.w = 1.0f;
    body->torque.x = 0.0f;
    body->torque.y = 0.0f;
    body->torque.z = 0.0f;
    body->torque.w = 1.0f;
    body->angVel.x = 0.0f;
    body->angVel.y = 0.0f;
    body->angVel.z = 0.0f;
    body->angVel.w = 1.0f;
    body->angVelBody.x = 0.0f;
    body->angVelBody.y = 0.0f;
    body->angVelBody.z = 0.0f;
    body->angVelBody.w = 1.0f;
    body->moved = 0.0f;
}
