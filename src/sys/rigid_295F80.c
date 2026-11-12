#define Vec3_Cross func_00312490  /* fix_targets */ /* the original uses 0x312490 here */
#define Vec3_Normalize sceVu0Normalize  /* fix_targets */ /* the original uses 0x3124d8 here */
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

/* out = v * -scale (xyz). */
void Vec3_ScaleNeg(Vec4 *out, Vec4 *v, f32 scale) {
    scale = -scale;
    out->x = scale * v->x;
    out->y = scale * v->y;
    out->z = scale * v->z;
}

/* Euler's equations for a diagonal inertia tensor: out = (torque + (I x-permuted) w w) / I, body space. */
void Rigid_EulerAccel(Vec4 *out, Vec4 *angVel, Vec4 *torque, Vec4 *inertia) {
    out->x = (torque->x + (inertia->y - inertia->z) * angVel->y * angVel->z) / inertia->x;
    out->y = (torque->y + (inertia->z - inertia->x) * angVel->z * angVel->x) / inertia->y;
    out->z = (torque->z + (inertia->x - inertia->y) * angVel->x * angVel->y) / inertia->z;
}

/* out = the skew-symmetric (cross-product) matrix of v. */
void Mat3_SetSkew(Mat3 *out, Vec4 *v) {
    out->m[0][0] = 0.0f;
    out->m[0][1] = v->z;
    out->m[0][2] = -v->y;
    out->m[1][0] = -v->z;
    out->m[1][1] = 0.0f;
    out->m[1][2] = v->x;
    out->m[2][0] = v->y;
    out->m[2][1] = -v->x;
    out->m[2][2] = 0.0f;
}

/* out = a * b (3x3). out must not alias a or b. */
void Mat3_Mul(Mat3 *out, Mat3 *a, Mat3 *b) {
    out->m[0][0] = a->m[0][0] * b->m[0][0] + a->m[0][1] * b->m[1][0] + a->m[0][2] * b->m[2][0];
    out->m[0][1] = a->m[0][0] * b->m[0][1] + a->m[0][1] * b->m[1][1] + a->m[0][2] * b->m[2][1];
    out->m[0][2] = a->m[0][0] * b->m[0][2] + a->m[0][1] * b->m[1][2] + a->m[0][2] * b->m[2][2];
    out->m[1][0] = a->m[1][0] * b->m[0][0] + a->m[1][1] * b->m[1][0] + a->m[1][2] * b->m[2][0];
    out->m[1][1] = a->m[1][0] * b->m[0][1] + a->m[1][1] * b->m[1][1] + a->m[1][2] * b->m[2][1];
    out->m[1][2] = a->m[1][0] * b->m[0][2] + a->m[1][1] * b->m[1][2] + a->m[1][2] * b->m[2][2];
    out->m[2][0] = a->m[2][0] * b->m[0][0] + a->m[2][1] * b->m[1][0] + a->m[2][2] * b->m[2][0];
    out->m[2][1] = a->m[2][0] * b->m[0][1] + a->m[2][1] * b->m[1][1] + a->m[2][2] * b->m[2][1];
    out->m[2][2] = a->m[2][0] * b->m[0][2] + a->m[2][1] * b->m[1][2] + a->m[2][2] * b->m[2][2];
}

/* out = a + b (3x3). */
void Mat3_Add(Mat3 *out, Mat3 *a, Mat3 *b) {
    out->m[0][0] = a->m[0][0] + b->m[0][0];
    out->m[0][1] = a->m[0][1] + b->m[0][1];
    out->m[0][2] = a->m[0][2] + b->m[0][2];
    out->m[1][0] = a->m[1][0] + b->m[1][0];
    out->m[1][1] = a->m[1][1] + b->m[1][1];
    out->m[1][2] = a->m[1][2] + b->m[1][2];
    out->m[2][0] = a->m[2][0] + b->m[2][0];
    out->m[2][1] = a->m[2][1] + b->m[2][1];
    out->m[2][2] = a->m[2][2] + b->m[2][2];
}

/* out = m * v with v as a column: out[i] = row i of m . v. With a rotation: world -> body. */
void Mat3_MulVecCols(Vec4 *out, Vec4 *v, Mat3 *m) {
    out->x = v->x * m->m[0][0] + v->y * m->m[0][1] + v->z * m->m[0][2];
    out->y = v->x * m->m[1][0] + v->y * m->m[1][1] + v->z * m->m[1][2];
    out->z = v->x * m->m[2][0] + v->y * m->m[2][1] + v->z * m->m[2][2];
}

/* out = v * m with v as a row: out[j] = v . column j of m. With a rotation: body -> world. */
void Mat3_MulVecRows(Vec4 *out, Vec4 *v, Mat3 *m) {
    out->x = v->x * m->m[0][0] + v->y * m->m[1][0] + v->z * m->m[2][0];
    out->y = v->x * m->m[0][1] + v->y * m->m[1][1] + v->z * m->m[2][1];
    out->z = v->x * m->m[0][2] + v->y * m->m[1][2] + v->z * m->m[2][2];
}

/* Makes the three rows orthonormal again: row 2 is kept (normalised), row 0 = row1 x row2, row 1 = row2 x row0. */
void Mat3_Orthonormalize(Mat3 *m) {
    Vec4 z;
    Vec4 y;
    Vec4 x;

    z.x = m->m[2][0];
    z.y = m->m[2][1];
    z.z = m->m[2][2];
    Vec3_Normalize(&z, &z);
    m->m[2][0] = z.x;
    m->m[2][1] = z.y;
    m->m[2][2] = z.z;
    y.x = m->m[1][0];
    y.y = m->m[1][1];
    y.z = m->m[1][2];
    Vec3_Cross(&x, &y, &z);
    Vec3_Normalize(&x, &x);
    m->m[0][0] = x.x;
    m->m[0][1] = x.y;
    m->m[0][2] = x.z;
    Vec3_Cross(&y, &z, &x);
    m->m[1][0] = y.x;
    m->m[1][1] = y.y;
    m->m[1][2] = y.z;
}

/* Empty; called at the start of Rigid_Integrate. */
void Rigid_Stub266CC0(void);

/* Accumulates a world-space force applied at a world-space point: force += f, torque += (point - center) x f. */
void Rigid_AddForceAt(RigidBody *body, Vec4 *point, Vec4 *force);

/* Turns the accumulated force and torque into velocity changes over dt, then clears them. */
void Rigid_Integrate(RigidBody *body, f32 dt);

/* Builds the body's 4x4 world matrix: rotation rows, position in row 3. */
void Rigid_GetMatrix(Mtx44 *out, RigidBody *body);

/* Adds the weight (0, 9.8 * mass, 0) at the centre of mass; +Y is down. */
void Rigid_AddGravity(RigidBody *body);

/* Drag: removes the fraction k of the linear velocity and of the body-space angular velocity. */
void Rigid_Damp(RigidBody *body, f32 k);

/* Recomputes the world-space centre of mass: localCenter * rot + pos. */
void Rigid_UpdateCenter(RigidBody *body);

/* Contact with a plane at `point` with unit `normal`, penetrating by `depth`: a penalty spring
   (147 * mass * depth) minus a damper on the approach speed, plus sliding friction when friction > 0. */
void Rigid_AddContact(RigidBody *body, Vec4 *point, Vec4 *normal, f32 restitution, f32 friction, f32 depth);

/* Empty; no caller. */
void Rigid_Stub267390(void);

/* One simulation step of dt seconds: integrates the velocities, then moves and rotates the body. */
void Rigid_Step(RigidBody *body, f32 dt);

/* Places the body and stops it: velocities, force and torque are cleared, previous transform = current. */
void Rigid_SetTransform(RigidBody *body, Vec4 *pos, Mtx44 *rot);

/* Same as Rigid_SetTransform (plain forwarder); no caller. */
void Rigid_SetTransform2(RigidBody *body, Vec4 *pos, Mtx44 *rot);

/* Start of a frame: remembers the flags and the transform, keeps only the low byte of the flags. */
void Rigid_BeginFrame(RigidBody *body);

/* Sets the linear velocity and replaces the body-space angular velocity with that of angVel's Y part only. */
void Rigid_SetVelocity(RigidBody *body, Vec4 *vel, Vec4 *angVel);

/* Damps slow rotation and returns 1 (restoring the previous transform) when the body is at rest. */
s32 Rigid_CheckRest(RigidBody *body);

/* Moves the centres of both collision spheres to the body position. */
void Rigid_SyncSpheres(RigidBody *body);

/*
 * Clears the body and sets it up as a sphere of the given radius and density:
 *   mass = radius^3 * 2.3561945 (3 pi / 4) * density;  inertia = (2 / 5) mass radius^2 * 20 on all three axes;
 *   sphere = prevSphere = { centre (0, 0, 0), radius };  flags = 1;  user = second argument.
 *
 * The float constant 2.35619449f (0x4016CBE3) of this function is D_002FE818, the last entry of this file's
 * .lit4 pool.
 */
/* FAKE MATCH (permuter): `body++; body--;` in front of the clear. The two statements combine to a self-move
   (`body = body`) that survives until after the first scheduling pass and vanishes later. All it does is add ONE
   instruction to the instructions issued before the first memset call (the clear of `zero`); the scheduler
   issues two per cycle, so the call becomes the second instruction of its cycle instead of the first, the three
   argument loads of the second memset are then sorted together and come out as size, body, zero like the
   original (without it `a0 = body` is issued in the call's own cycle: `move a0,s0` in front of `li a2,0x220`).
   It stands for whatever gave the original an odd number of instructions there; no natural form was found
   (a local copy of `body`, inline identity / clear helpers, a cast through u32, `&body[0]`, an explicit memset
   of `zero`, a compound literal and a local for 1.0f all leave the pair as it was). */
void Rigid_Init(RigidBody *body, s32 user, f32 radius, f32 density);
