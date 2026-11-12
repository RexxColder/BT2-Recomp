#include "common.h"

void func_001F9FB0(u8 *arg0, s32 arg1);
void func_00215068(f32 farg0, u8 *arg0, s32 arg1, s32 arg2, f32 farg1);
void func_00215E88(f32 farg0, u8 *arg0, s32 arg1);
void func_00216208(u8 *arg0, f32 farg0, f32 farg1);
void BtlMove_BrakeVertical(u8 *arg0);
s32 func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
void func_00208DE8(s32 arg0, u8 *arg1, s32 arg2);
void func_00209268(s32 arg0, u8 *arg1, u8 *arg2, s32 arg3, f32 farg0, f32 farg1);
u8 *BtlChar_GetPos(u8 *arg0);
f32 sinf(f32 arg0);
f32 cosf(f32 arg0);
extern f32 D_00386280;
extern f32 D_00386284;
extern f32 D_00386288;
extern f32 D_0038628C;
extern f32 D_00386290;

void func_00226898(u8 *arg0) {
    s32 sp[8];
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f0;
    f32 temp_f0_2;

    temp_f20 = D_00386280;
    func_001F9FB0(arg0, 0);
    func_00215068(temp_f20, arg0, 1, 0xC, 0.5f);
    func_00215E88(D_00386284, arg0, 7);
    func_00216208(arg0, 0.0f, D_00386288);
    BtlMove_BrakeVertical(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    func_002113C0(arg0, 0xD, 8, 1);
    if (func_00211310(arg0, 0, 1) != 0) {
        func_00208DE8(*(s32 *)(arg0 + 0x1534), (u8 *)sp, 0x11);
        func_00209268(*(s32 *)(arg0 + 0x1534), arg0 + 0xA00, (u8 *)sp, 0x11, D_0038628C, temp_f20);
        return;
    }
    temp_f20_2 = D_00386290;
    temp_f0 = sinf(*(f32 *)(BtlChar_GetPos(arg0) + 0xB4));
    *(f32 *)(arg0 + 0xA04) = temp_f20_2;
    *(f32 *)(arg0 + 0xA00) = temp_f0 * temp_f20_2;
    temp_f0_2 = cosf(*(f32 *)(BtlChar_GetPos(arg0) + 0xB4));
    *(f32 *)(arg0 + 0xA0C) = 0.0f;
    *(f32 *)(arg0 + 0xA08) = temp_f0_2 * temp_f20_2;
}
