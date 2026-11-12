#include "common.h"

void func_003126C8(s32 arg0, s32 arg1, f32 farg0);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
void func_00312FB0(s32 arg0, s32 arg1, f32 farg0);
extern u8 D_00344C40 __attribute__((section(".data")));

void func_002628A8(u8 *arg0, u8 *arg1, s32 arg2, f32 farg0) {
    f32 sp[4];
    f32 m0;
    f32 m1;
    f32 m2;
    f32 m3;
    f32 s0;
    f32 s1;
    f32 s2;
    f32 p;
    f32 q;
    f32 r;
    f32 d3;
    f32 t1;

    func_003126C8((s32)sp, arg2, farg0);
    func_00312638((s32)sp, (s32)sp, (s32)&D_00344C40);
    func_00312FB0((s32)sp, (s32)sp, 0.5f);

    m0 = *(f32 *)(arg1 + 0x0);
    m1 = *(f32 *)(arg1 + 0x4);
    m2 = *(f32 *)(arg1 + 0x8);
    m3 = *(f32 *)(arg1 + 0xC);
    s0 = sp[0];
    s1 = sp[1];
    s2 = sp[2];

    t1 = -(m3 + farg0);
    p = m0 * -s0;
    q = m1 * -s1;
    r = m2 * -s2;
    d3 = p + q;

    *(f32 *)(arg0 + 0x00) = q + r;
    *(f32 *)(arg0 + 0x04) = (-m0) * (-s1);
    *(f32 *)(arg0 + 0x08) = (-m0) * (-s2);
    *(s32 *)(arg0 + 0x0C) = 0;
    *(f32 *)(arg0 + 0x10) = (-m1) * (-s0);
    *(f32 *)(arg0 + 0x14) = p + r;
    *(f32 *)(arg0 + 0x18) = (-m1) * (-s2);
    *(s32 *)(arg0 + 0x1C) = 0;
    *(f32 *)(arg0 + 0x20) = (-m2) * (-s0);
    *(f32 *)(arg0 + 0x24) = (-m2) * (-s1);
    *(f32 *)(arg0 + 0x28) = d3;
    *(s32 *)(arg0 + 0x2C) = 0;
    *(f32 *)(arg0 + 0x30) = t1 * (-s0);
    *(f32 *)(arg0 + 0x34) = t1 * (-s1);
    *(f32 *)(arg0 + 0x38) = t1 * (-s2);
    *(f32 *)(arg0 + 0x3C) = d3 + r;
}
