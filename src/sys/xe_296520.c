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


/* Accumulates a world-space force applied at a world-space point: force += f, torque += (point - center) x f. */
void Rigid_AddForceAt(RigidBody *body, Vec4 *point, Vec4 *force) {
    Vec4 torque;
    Vec4 arm;

    Vec4_Sub(&arm, point, &body->center);
    Vec3_Cross(&torque, &arm, force);
    body->force.x += force->x;
    body->force.y += force->y;
    body->force.z += force->z;
    body->torque.x += torque.x;
    body->torque.y += torque.y;
    body->torque.z += torque.z;
}

/* Turns the accumulated force and torque into velocity changes over dt, then clears them. */
void Rigid_Integrate(RigidBody *body, f32 dt) {
    Vec4 torque;
    Vec4 accel;
    f32 k;

    Rigid_Stub266CC0();
    k = dt / body->mass;
    body->vel.x += body->force.x * k;
    body->vel.y += body->force.y * k;
    body->vel.z += body->force.z * k;
    Mat3_MulVecCols(&torque, &body->torque, &body->rot);
    Rigid_EulerAccel(&accel, &body->angVelBody, &torque, &body->inertia);
    body->angVelBody.x += dt * accel.x * 0.999f;
    body->angVelBody.y += dt * accel.y * 0.999f;
    body->angVelBody.z += dt * accel.z * 0.999f;
    Mat3_MulVecRows(&body->angVel, &body->angVelBody, &body->rot);
    body->forceSum += sqrtf(Vec3_Dot(&body->force, &body->force));
    body->force.x = 0.0f;
    body->force.y = 0.0f;
    body->force.z = 0.0f;
    body->force.w = 1.0f;
    body->torque.x = 0.0f;
    body->torque.y = 0.0f;
    body->torque.z = 0.0f;
    body->torque.w = 1.0f;
}

/* Builds the body's 4x4 world matrix: rotation rows, position in row 3. */
void Rigid_GetMatrix(Mtx44 *out, RigidBody *body) {
    Mtx_StoreIdentity(out);
    out->m[0][0] = body->rot.m[0][0];
    out->m[0][1] = body->rot.m[0][1];
    out->m[0][2] = body->rot.m[0][2];
    out->m[1][0] = body->rot.m[1][0];
    out->m[1][1] = body->rot.m[1][1];
    out->m[1][2] = body->rot.m[1][2];
    out->m[2][0] = body->rot.m[2][0];
    out->m[2][1] = body->rot.m[2][1];
    out->m[2][2] = body->rot.m[2][2];
    out->m[3][0] = body->pos.x;
    out->m[3][1] = body->pos.y;
    out->m[3][2] = body->pos.z;
}

/* Adds the weight (0, 9.8 * mass, 0) at the centre of mass; +Y is down. */
void Rigid_AddGravity(RigidBody *body) {
    Vec4 force;

    force.x = 0.0f;
    force.y = body->mass * 9.8f;
    force.z = 0.0f;
    Rigid_AddForceAt(body, &body->center, &force);
}

/* Drag: removes the fraction k of the linear velocity and of the body-space angular velocity. */
void Rigid_Damp(RigidBody *body, f32 k) {
    body->vel.x -= body->vel.x * k;
    body->vel.y -= body->vel.y * k;
    body->vel.z -= body->vel.z * k;
    body->angVelBody.x -= body->angVelBody.x * k;
    body->angVelBody.y -= body->angVelBody.y * k;
    body->angVelBody.z -= body->angVelBody.z * k;
}

/* Recomputes the world-space centre of mass: localCenter * rot + pos. */
void Rigid_UpdateCenter(RigidBody *body) {
    Mat3_MulVecRows(&body->center, &body->localCenter, &body->rot);
    body->center.x += body->pos.x;
    body->center.y += body->pos.y;
    body->center.z += body->pos.z;
}
