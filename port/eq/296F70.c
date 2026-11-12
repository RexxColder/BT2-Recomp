#include "common.h"
#include "sys/rigid.h"

void func_003126C8(void *dst, void *src); /* Vec4 copy */
void func_003126D8(void *dst, void *src); /* Mat3 copy */

#define RABS(x) __builtin_fabsf(x)

/* 0x00296F70 Rigid_CheckRest: the same routine as BT3's (Tenkaichi3Decomp src/sys/rigid.c), with BT2's inline
   distance (VU0: z*z + (x*x + y*y), vsqrt of the absolute value) and constants 0.1 / 0.2, 0.15 / 0.7, 0.25 / 0.7,
   0.015, 0.2 (gp -0x4C28.. and lui 0x3E80). Damps small spins and says whether the body has come to rest; it ran on
   the PS2Recomp fallback until now. */
s32 func_00296F70(RigidBody *body) {
    f32 *p = (f32 *)&body->pos, *q = (f32 *)&body->prevPos;
    f32 dx = q[0] - p[0], dy = q[1] - p[1], dz = q[2] - p[2];
    f32 sum;

    body->moved = __builtin_sqrtf(RABS(dz * dz + (dx * dx + dy * dy)));
    sum = RABS(body->angVel.x);
    sum += RABS(body->angVel.y);
    sum += RABS(body->angVel.z);
    if (RABS(body->angVel.x) < 0.1f) { body->angVel.x *= 0.2f; }
    if (RABS(body->angVel.y) < 0.1f) { body->angVel.y *= 0.2f; }
    if (RABS(body->angVel.z) < 0.1f) { body->angVel.z *= 0.2f; }
    if (RABS(body->angVelBody.x) < 0.1f) { body->angVelBody.x *= 0.2f; }
    if (RABS(body->angVelBody.y) < 0.1f) { body->angVelBody.y *= 0.2f; }
    if (RABS(body->angVelBody.z) < 0.1f) { body->angVelBody.z *= 0.2f; }
    if (RABS(body->angVel.x) < 0.15f) { body->angVel.x *= 0.7f; }
    if (RABS(body->angVel.y) < 0.15f) { body->angVel.y *= 0.7f; }
    if (RABS(body->angVel.z) < 0.15f) { body->angVel.z *= 0.7f; }
    if (RABS(body->angVelBody.x) < 0.25f) { body->angVelBody.x *= 0.7f; }
    if (RABS(body->angVelBody.y) < 0.25f) { body->angVelBody.y *= 0.7f; }
    if (RABS(body->angVelBody.z) < 0.25f) { body->angVelBody.z *= 0.7f; }
    if (body->moved <= 0.015f && sum < 0.2f) {
        func_003126C8(&body->pos, &body->prevPos);
        func_003126D8(&body->rot, &body->prevRot);
        return 1;
    }
    return 0;
}
