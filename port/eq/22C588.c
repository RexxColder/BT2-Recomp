#include "common.h"

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))

extern f32 D_003865CC;
extern f32 D_003865D0;
extern f32 D_003865D4;
extern f32 D_003865D8;
extern f32 D_003865DC;
extern f32 D_003865E0;
extern f32 D_003865E4;
extern f32 D_003865E8;
extern f32 D_003865EC;
extern f32 D_003865F0;
extern f32 D_003865F4;
extern f32 D_003865F8;
extern f32 D_003865FC;
extern f32 D_00386600;
extern f32 D_00386604;

s32 BtlObjXf_Update(void *arg0);
void func_001FA360(f32 farg0, void *arg1);
s32 func_001FA0A0(void *arg0, s32 arg1, s32 arg2);
void BtlAnim_SetBlend(f32 farg0, void *arg1);
s32 func_0023F410(void *arg0);
void func_0020FC38(void *arg0, s32 arg1);
void BtlChar_Vibrate(f32 farg0, f32 farg1, void *arg2);
void func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
void BtlMove_BrakeVertical(void *arg0);
void func_001FA110(void *arg0, s32 arg1);
f32 func_00240D50(void *arg0, s32 arg1);
void func_00216890(f32 farg0, f32 farg1, void *arg2);
void func_00206958(void *arg0, s64 arg1);
void BtlChar_SetVibration(f32 farg0, f32 farg1, void *arg2);
s32 BtlChar_GetPos(void *arg0);
f32 func_0029DFD0(s32 arg0);
s32 BtlPad_Test4C(void *arg0, s32 arg1);
void func_001F9D78(void *arg0, s32 arg1);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
s32 BtlPad_Test48(void *arg0, s32 arg1);
s32 func_00240EA8(void *arg0, s32 arg1);
s32 func_00203888(void *arg0, s32 arg1, s32 arg2);
void func_001F9FB0(void *arg0, s32 arg1);
void func_00215068(f32 farg0, f32 farg1, void *arg2, s32 arg3, s32 arg4);
void func_00215E88(f32 farg0, void *arg1, s32 arg2);
void func_00216208(f32 farg0, f32 farg1, void *arg2);

void func_0022C588(void *arg0) {
    f32 temp_f20;
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = BtlObjXf_Update(arg0);
    switch (temp_v0) {
    case 0x3A:
        if (W(arg0, 0x8DC) & 2) {
            func_001FA360(D_003865CC, arg0);
        }
        if (func_001FA0A0(arg0, 0x3B, 0) != 0) {
            BtlAnim_SetBlend(D_003865D0, arg0);
            if (func_0023F410(arg0) & 0x10) {
                func_0020FC38(arg0, 0x1D);
            } else {
                func_0020FC38(arg0, 0x1C);
            }
            BtlChar_Vibrate(D_003865D4, D_003865D8, arg0);
            func_002113C0(arg0, 0xE, 0x200, 1);
        }
        BtlMove_BrakeVertical(arg0);
        break;
    case 0x3B:
        func_001FA110(arg0, 0);
        func_00216890(-func_00240D50(arg0, 9), D_003865DC, arg0);
        func_00206958(arg0, 8);
        func_00206958(arg0, (s64)0x8000 << 28);
        func_002113C0(arg0, 1, 0x2000, 1);
        BtlChar_SetVibration(D_003865E0, D_003865E4, arg0);
        if (!(func_0029DFD0(BtlChar_GetPos(arg0) + 0x50) < D_003865E8)) {
            W(arg0, 0x8C0) = 0;
        } else {
            temp_v0_2 = W(arg0, 0x8C0) + 1;
            W(arg0, 0x8C0) = temp_v0_2;
            if (temp_v0_2 >= 0x10) {
                func_001F9D78(arg0, 0x3C);
                BtlAnim_SetBlend(D_003865EC, arg0);
            }
        }
        if (BtlPad_Test4C(arg0, 3) != 0) {
            func_001F9D78(arg0, 0x3C);
            BtlAnim_SetBlend(D_003865F0, arg0);
            if ((func_00211310(arg0, 1, 1) == 0) && (BtlPad_Test48(arg0, 7) != 0)) {
                W(arg0, 0x8DC) = W(arg0, 0x8DC) | 1;
            }
        }
        if (func_00211310(arg0, 0, 0x10) != 0) {
            func_001F9D78(arg0, 0x3C);
            BtlAnim_SetBlend(D_003865F4, arg0);
        }
        if (func_00203888(arg0, func_00240EA8(arg0, 2), 0) != 0) {
            func_001F9D78(arg0, 0x3C);
            BtlAnim_SetBlend(D_003865F8, arg0);
        }
        func_002113C0(arg0, 0xD, 8, 1);
        break;
    case 0x3C:
        func_001F9FB0(arg0, 0);
        BtlMove_BrakeVertical(arg0);
        break;
    }
    temp_f20 = D_003865FC;
    func_00215068(D_00386600, temp_f20, arg0, 5, 0xC);
    func_00215E88(temp_f20, arg0, 6);
    func_00216208(0.0f, D_00386604, arg0);
    func_002113C0(arg0, 1, 0x800000, 1);
    func_002113C0(arg0, 8, 4, 1);
}
