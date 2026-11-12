#include "common.h"

s32 BtlObjXf_Update(u8 *arg0);
s32 BtlObjAnim_QueryEvent(s32 a0, s32 a1, s32 a2, s32 a3);
void BtlChar_SetVibration(void *a0, f32 farg0, f32 farg1);
s32 BtlPad_Test48(void *a0, s32 a1);
s32 BtlPad_Test4C(void *a0, s32 a1);
void func_001F9D78(void *a0, s32 a1);
void func_001F9FB0(void *a0, s32 a1);
s32 func_001FA0A0(void *a0, s32 a1, s32 a2);
s32 func_001FA2E0(void *a0);
f32 func_001FA308(void *a0);
f32 func_001FA318(void *a0);
void func_00206958(void *a0, s64 a1);
void func_0020FC38(void *a0, s32 a1);
s32 func_00211310(void *a0, s32 a1, s32 a2);
s32 func_002113C0(void *a0, s32 a1, s32 a2, s32 a3);
void func_00212DD8(void *a0, s32 a1);
void func_00215068(s32 a0, s32 a1, s32 a2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 a1, s32 a2);
void func_00216208(s32 a0, f32 farg0, f32 farg1);
void func_00216678(void *a0);
void func_002182A8(void *a0);
void func_002188C8(void *a0);
s32 func_0023F2D8(void *a0);
extern f32 D_00385DC4;
extern f32 D_00385DC8;
extern f32 D_00385DCC;
extern f32 D_00385DD0;
extern f32 D_00385DD4;

void func_0021D3A8(u8 *arg0) {
    f32 temp_f20;
    f32 var_f21;
    s32 temp_v0;

    temp_v0 = BtlObjXf_Update(arg0);
    var_f21 = D_00385DC4;
    if (temp_v0 == 0x53) {
        func_002188C8(arg0);
        func_001FA0A0(arg0, 0x54, 0);
    } else if (temp_v0 == 0x54) {
        func_002188C8(arg0);
        if (func_001FA0A0(arg0, 0x55, 0) == 0) {
            if (BtlPad_Test48(arg0, 1) == 0) {
                func_001F9D78(arg0, 0x55);
            }
            if ((BtlPad_Test4C(arg0, 3) != 0) || (BtlPad_Test4C(arg0, 2) != 0) || (BtlPad_Test4C(arg0, 0) != 0)) {
                func_001F9D78(arg0, 0x39);
                func_002182A8(arg0);
                func_0020FC38(arg0, 0x1F);
                *(s32 *)(arg0 + 0x14A0) = *(s32 *)(arg0 + 0x14A0) + 1;
            }
        } else {
            BtlChar_SetVibration(arg0, 1.0f, D_00385DC8);
        }
        *(f32 *)(arg0 + 0x9B0) = func_001FA318(arg0);
        func_00206958(arg0, 0x40000);
    } else if (temp_v0 == 0x55) {
        func_001F9FB0(arg0, 0);
        if (func_001FA2E0(arg0) != 0) {
            func_00212DD8(arg0, func_0023F2D8(arg0));
        }
        var_f21 = 0.0f;
        temp_f20 = func_001FA308(arg0) - 15.0f;
        if (temp_f20 < (f32)BtlObjAnim_QueryEvent(*(s32 *)(arg0 + 0x1530), 2, 0, 1)) {
            func_00206958(arg0, 0x40000);
        }
    } else if (temp_v0 == 0x39) {
        func_001F9FB0(arg0, 0);
        var_f21 = 0.0f;
        func_002113C0(arg0, 5, 0x800, 1);
    }
    if (func_00211310(arg0, 5, 4) == 0) {
        var_f21 = 0.0f;
    }
    func_00215068((s32)arg0, 5, 0xC, D_00385DCC, 0.5f);
    func_00215E88(D_00385DD0, (s32)arg0, 2);
    func_00216208((s32)arg0, var_f21, D_00385DD4);
    func_00216678(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    func_002113C0(arg0, 0xF, 0x40, 1);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
}
