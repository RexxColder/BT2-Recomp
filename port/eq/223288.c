#include "common.h"

f32 BtlMember_GetHealthRatio(u8 *arg0);
s32 BtlMember_HasKi(u8 *arg0, s32 arg1);
s32 BtlPad_Test48(u8 *arg0, s32 arg1);
void func_001FA110(u8 *arg0, s32 arg1);
void func_00206958(u8 *arg0, s64 arg1);
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212820(u8 *arg0);
s32 func_00212878(void);
void func_00215068(u8 *arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, u8 *arg0, s32 arg1);
void func_00216208(u8 *arg0, f32 farg0, f32 farg1);
void func_00216678(u8 *arg0);
s32 func_00218838(u8 *arg0, s32 arg1);
s32 func_0023FB58(u8 *arg0);
extern f32 D_0038609C;
extern f32 D_003860A0;
extern f32 D_003860A4;
extern f32 D_003860A8;
extern f32 D_003860AC;

void func_00223288(u8 *arg0) {
    f32 temp_f20;
    f32 var_f21;

    var_f21 = D_0038609C;
    if (func_00212878() != 0) {
        var_f21 = (1.0f - BtlMember_GetHealthRatio(arg0)) * var_f21;
    }
    temp_f20 = D_003860A0;
    func_001FA110(arg0, 0);
    func_00215068(arg0, 5, 0xD, D_003860A4, temp_f20);
    if (func_00218838(arg0, 0) != 0) {
        func_00215E88(temp_f20, arg0, 3);
    } else {
        func_00215E88(temp_f20, arg0, 5);
    }
    func_00216208(arg0, var_f21, D_003860A8);
    func_00216678(arg0);
    func_002113C0(arg0, 6, 4, 1);
    func_002113C0(arg0, 6, 8, 1);
    func_002113C0(arg0, 1, 0x1000, 1);
    func_002113C0(arg0, 1, 0x800, 1);
    func_002113C0(arg0, 1, 0x02000000, 1);
    func_00206958(arg0, (s64)0x8000 << 29);
    if (D_003860AC < (f32)*(s32 *)(arg0 + 0x8CC) && func_00212820(arg0) != 0 &&
        BtlMember_HasKi(arg0, func_0023FB58(arg0)) != 0) {
        if (BtlPad_Test48(arg0, 0xC) != 0) {
            func_002113C0(arg0, 1, 0x8000, 1);
            return;
        }
        if (BtlPad_Test48(arg0, 0xD) != 0) {
            func_002113C0(arg0, 1, 0x4000, 1);
        }
    }
}
