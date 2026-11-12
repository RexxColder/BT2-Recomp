#include "common.h"

f32 EftMath_WrapAngle(f32 farg0);
void Mtx_Mul(s32 arg0, s32 arg1, s32 arg2);
void Mtx_RotateX(f32 farg0, s32 arg0, s32 arg1);
void Mtx_StoreIdentity(s32 arg0);
void Vec4_Set(f32 farg0, f32 farg1, f32 farg2, f32 farg3, s32 arg0);
void func_00128810(s32 arg0, s32 arg1);
void func_001AD730(s32 arg0);
void func_001EDBD8(s32 arg0, s32 arg1);
void func_001EDD40(s32 arg0, s32 arg1);

void func_001AD418(s32 arg0) {
    f32 buf[36];
    u8 *e;
    s32 a0;

    e = *(u8 **)(arg0 + 0x38);
    a0 = *(s32 *)(e + 0x11C);
    if (a0 == -1) {
        return;
    }
    if (*(s32 *)(e + 0xC0) & 0x40) {
        func_001EDBD8(a0, 1);
    } else {
        func_001EDBD8(a0, 0);
    }
    Mtx_StoreIdentity((s32)buf);
    Mtx_StoreIdentity((s32)(buf + 16));
    buf[16] = *(f32 *)(e + 0xD0);
    buf[21] = *(f32 *)(e + 0xD0);
    buf[26] = *(f32 *)(e + 0xD0);
    Mtx_Mul((s32)buf, (s32)buf, (s32)(buf + 16));
    Mtx_RotateX(EftMath_WrapAngle(-*(f32 *)(e + 0xD8)), (s32)buf, (s32)buf);
    Vec4_Set(*(f32 *)(e + 0x50), *(f32 *)(e + 0x54), *(f32 *)(e + 0x58), 1.0f, (s32)(buf + 32));
    func_00128810((s32)buf, (s32)(buf + 32));
    func_001EDD40(*(s32 *)(e + 0x11C), (s32)buf);
    func_001AD730(arg0);
}
