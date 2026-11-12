#include "common.h"

extern f32 D_003871B4;
void Rigid_Stub266CC0(u8 *body);
void Mat3_MulVecCols(u8 *out, u8 *a, u8 *b);
void Mat3_MulVecRows(u8 *out, u8 *a, u8 *b);
void Rigid_EulerAccel(u8 *out, u8 *a, u8 *b, u8 *c);
f32 sceVu0InnerProduct(u8 *a, u8 *b);

/* 0x002965D8 Rigid_Integrate(body, dt): semi-implicit integration of one rigid body step. mass at +8, position +0x90,
 * force +0xB0, torque +0xC0, angular velocity +0xD0, inverse inertia rows +0xA0, orientation +0x50. */
void Rigid_Integrate(u8 *body, f32 dt) {
    u8 sp[32];
    u8 *angVel = body + 0xD0;
    u8 *rot = body + 0x50;
    u8 *force = body + 0xB0;
    u8 *torque = body + 0xC0;
    f32 k;
    f32 s;
    f32 *ang;
    f32 *pos;

    Rigid_Stub266CC0(body);
    k = dt / *(f32 *)(body + 8);
    pos = (f32 *)(body + 0x90);
    pos[0] = pos[0] + *(f32 *)(body + 0xB0) * k;
    pos[1] = pos[1] + *(f32 *)(body + 0xB4) * k;
    pos[2] = pos[2] + *(f32 *)(body + 0xB8) * k;
    Mat3_MulVecCols(sp, torque, rot);
    Rigid_EulerAccel(sp + 0x10, angVel, sp, body + 0x10);
    k = D_003871B4;
    ang = (f32 *)angVel;
    ang[0] = ang[0] + (dt * *(f32 *)(sp + 0x10)) * k;
    ang[1] = ang[1] + (dt * *(f32 *)(sp + 0x14)) * k;
    ang[2] = ang[2] + (dt * *(f32 *)(sp + 0x18)) * k;
    Mat3_MulVecRows(body + 0xA0, angVel, rot);
    s = __builtin_sqrtf(sceVu0InnerProduct(force, force));
    *(f32 *)(body + 0x218) = *(f32 *)(body + 0x218) + s;
    *(f32 *)(body + 0xB0) = 0.0f;
    *(f32 *)(body + 0xB4) = 0.0f;
    *(f32 *)(body + 0xB8) = 0.0f;
    *(f32 *)(body + 0xBC) = 1.0f;
    *(f32 *)(body + 0xC0) = 0.0f;
    *(f32 *)(body + 0xCC) = 1.0f;
    *(f32 *)(body + 0xC4) = 0.0f;
    *(f32 *)(body + 0xC8) = 0.0f;
}
