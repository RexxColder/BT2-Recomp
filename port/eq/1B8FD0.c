#include "common.h"

extern u8 *D_003876A0;

void func_001B8E80(u8 *arg0, u8 *arg1, f32 farg0);
void func_001B8F00(u8 *arg0, f32 farg0);
void func_001B8F50(u8 *arg0, u8 *arg1, u8 *arg2, f32 farg0);

/* 0x001B8FD0: advances an interpolated particle/sprite state obj (cur t at +0x7C, end at +0x78) toward the keyframe
   block P = *(obj2 + 0x38). While t < end it interpolates size (+0x8C/+0x90), three 24-byte vectors (+0xAC/+0xDC/+0x10C)
   and two scalars (+0x12C/+0x130) between the P start/end values (with an optional ease section when obj+0x60 & 0x10),
   then t += 1; at the end it copies the final values from P. */
void func_001B8FD0(u8 *obj, u8 *obj2) {
    u8 sp[0xC0];
    u8 *P = *(u8 **)(obj2 + 0x38);
    u8 *vS0 = sp + 0x00;
    u8 *vS1 = sp + 0x20;
    u8 *vS2 = sp + 0x40;
    u8 *vD0 = sp + 0x60;
    u8 *vD1 = sp + 0x80;
    u8 *vD2 = sp + 0xA0;
    f32 cur = *(f32 *)(obj + 0x7C);
    f32 end = *(f32 *)(obj + 0x78);
    f32 sizeU;
    f32 sizeV;
    f32 dU;
    f32 dV;
    f32 s0;
    f32 s1;
    f32 d0;
    f32 d1;
    f32 ease;
    f32 inv;
    f32 t;
    f32 lim;
    f32 half;
    s32 v;

    if (cur < end) {
        sizeV = (f32)P[0x10];
        sizeU = (f32)P[0x11];
        __builtin_memcpy(vS0, P + 0x14, 24);
        __builtin_memcpy(vS1, P + 0x2C, 24);
        __builtin_memcpy(vS2, P + 0x44, 24);
        dU = *(f32 *)(obj + 0x84);
        s0 = *(f32 *)(P + 0x144);
        s1 = *(f32 *)(P + 0x148);
        __builtin_memcpy(vD0, obj + 0x94, 24);
        __builtin_memcpy(vD1, obj + 0xC4, 24);
        __builtin_memcpy(vD2, obj + 0xF4, 24);
        dV = *(f32 *)(obj + 0x88);
        d0 = *(f32 *)(obj + 0x124);
        d1 = *(f32 *)(obj + 0x128);
        if ((*(u32 *)(obj + 0x60) & 0x10) != 0) {
            lim = *(f32 *)(obj + 0x80);
            if (cur < lim) {
                t = cur / lim;
                ease = *(f32 *)(P + 0x150);
            } else {
                half = *(f32 *)(P + 0x150);
                ease = 1.0f - half;
                t = (cur - lim) / (end - lim);
                sizeV = sizeV + dU * half;
                sizeU = sizeU + dV * half;
                func_001B8E80(vS0, vD0, half);
                func_001B8E80(vS1, vD1, half);
                func_001B8E80(vS2, vD2, half);
                s0 = s0 + d0 * half;
                s1 = s1 + d1 * half;
            }
            func_001B8F00(vD0, ease);
            func_001B8F00(vD1, ease);
            d1 = d1 * ease;
            func_001B8F00(vD2, ease);
            dU = dU * ease;
            dV = dV * ease;
            d0 = d0 * ease;
        } else {
            t = cur / end;
        }
        *(f32 *)(obj + 0x8C) = sizeV + dU * t;
        *(f32 *)(obj + 0x90) = sizeU + dV * t;
        func_001B8F50(obj + 0xAC, vS0, vD0, t);
        func_001B8F50(obj + 0xDC, vS1, vD1, t);
        func_001B8F50(obj + 0x10C, vS2, vD2, t);
        *(f32 *)(obj + 0x12C) = s0 + d0 * t;
        *(f32 *)(obj + 0x130) = s1 + d1 * t;
        *(f32 *)(obj + 0x7C) = *(f32 *)(obj + 0x7C) + 1.0f;
        return;
    }
    if ((*(u64 *)(D_003876A0 + 0x4D8) & 2) != 0) {
        if (obj[0x64] == 0) {
            half = (f32)(P[9] >> 1);
            *(f32 *)(obj + 0x8C) = half;
            if (half < 1.0f) {
                *(f32 *)(obj + 0x8C) = 1.0f;
            }
            v = P[0xA] >> 1;
        } else {
            *(f32 *)(obj + 0x8C) = (f32)P[9];
            v = P[0xA];
        }
    } else {
        *(f32 *)(obj + 0x8C) = (f32)P[9];
        v = P[0xA];
    }
    *(f32 *)(obj + 0x90) = (f32)v;
    __builtin_memcpy(obj + 0xAC, P + 0x74, 24);
    __builtin_memcpy(obj + 0xDC, P + 0x8C, 24);
    __builtin_memcpy(obj + 0x10C, P + 0xA4, 24);
    *(f32 *)(obj + 0x12C) = *(f32 *)(P + 0xD8);
    *(f32 *)(obj + 0x130) = *(f32 *)(P + 0xDC);
}
