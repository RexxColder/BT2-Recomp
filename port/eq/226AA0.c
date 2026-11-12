#include "common.h"

s32 BtlObjXf_Update(u8 *arg0);
void BtlMove_BrakeVertical(u8 *arg0);
u8 *BtlChar_GetPos(u8 *arg0);
s32 BtlPad_Test48(u8 *arg0, s32 arg1);
void func_001F9FB0(u8 *arg0, s32 arg1);
void func_001F9D78(u8 *arg0, s32 arg1);
s32 func_001FA2E0(u8 *arg0);
s32 func_00240398(u8 *arg0);
void func_00203888(u8 *arg0, s32 arg1, s32 arg2);
void func_001FA0A0(u8 *arg0, s32 arg1, s32 arg2);
f32 func_001FA318(u8 *arg0);
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
void func_00215068(f32 farg0, u8 *arg0, s32 arg1, s32 arg2, f32 farg1);
void func_00215E88(f32 farg0, u8 *arg0, s32 arg1);
void func_00216208(f32 farg0, u8 *arg0, f32 farg1);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void func_00209268(f32 farg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg1);
f32 sinf(f32);
f32 cosf(f32);
extern f32 D_00386298;
extern f32 D_0038629C;
extern f32 D_003862A0;
extern f32 D_003862A4;
extern f32 D_003862A8;

void func_00226AA0(u8 *arg0) {
    s32 sp[4];
    s32 v;
    f32 f20;
    f32 f21;
    f32 temp_f0;
    f32 temp_f0_2;

    v = BtlObjXf_Update(arg0);
    switch (v) {
        case 0x9B:
            func_001F9FB0(arg0, 0);
            if (func_001FA2E0(arg0) != 0) {
                func_00203888(arg0, func_00240398(arg0), 0);
            }
            break;
        case 0x99:
            func_001FA0A0(arg0, 0x9A, 0);
            func_002113C0(arg0, 5, 0x400, 1);
            break;
        case 0x9A:
            func_001FA0A0(arg0, 0x9B, 0);
            *(f32 *)(arg0 + 0xA1C) = func_001FA318(arg0);
            func_002113C0(arg0, 5, 0x400, 1);
            if (BtlPad_Test48(arg0, 1) == 0) {
                func_001F9D78(arg0, 0x9B);
            }
            break;
    }
    f20 = D_00386298;
    func_00215068(f20, arg0, 1, 0xC, 0.5f);
    f21 = 0.0f;
    func_00215E88(D_0038629C, arg0, 7);
    func_00216208(0.0f, arg0, D_003862A0);
    BtlMove_BrakeVertical(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    func_002113C0(arg0, 0xD, 8, 1);
    func_002113C0(arg0, 0xF, 0x40, 1);
    if (func_00211310(arg0, 0, 1) != 0) {
        func_00208DE8(*(s32 *)(arg0 + 0x1534), (s32)sp, 0x11);
        func_00209268(D_003862A4, *(s32 *)(arg0 + 0x1534), (s32)(arg0 + 0xA00), (s32)sp, 0x11, f20);
        return;
    }
    f20 = D_003862A8;
    temp_f0 = sinf(*(f32 *)(BtlChar_GetPos(arg0) + 0xB4));
    *(f32 *)(arg0 + 0xA04) = f20;
    *(f32 *)(arg0 + 0xA00) = temp_f0 * f20;
    temp_f0_2 = cosf(*(f32 *)(BtlChar_GetPos(arg0) + 0xB4));
    *(f32 *)(arg0 + 0xA0C) = f21;
    *(f32 *)(arg0 + 0xA08) = temp_f0_2 * f20;
}
