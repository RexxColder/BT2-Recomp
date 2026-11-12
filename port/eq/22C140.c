#include "common.h"

void *BtlChar_GetPos(void *arg0);
void *BtlMember_GetActiveGauge(void *arg0);
s32 BtlObjXf_Update(void *arg0);
void func_001F9D78(void *arg0, s32 arg1);
void func_001F9FB0(void *arg0, s32 arg1);
void func_001FA110(void *arg0, s32 arg1);
void func_00206958(void *arg0, s64 arg1);
f32 func_00207E90(void *arg0);
void func_0020D048(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_0020D240(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_0020D7E8(void *arg0, f32 farg0, f32 farg1);
void func_0020FC38(void *arg0, s32 arg1);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
void func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212878(void *arg0);
void func_00215068(void *arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(void *arg0, s32 arg1, f32 farg0);
void func_00216208(void *arg0, f32 farg0, f32 farg1);
void func_00216678(void *arg0);
void func_00216890(void *arg0, f32 farg0, f32 farg1);
f32 func_00217360(void *arg0);
s32 func_0023F410(void *arg0);
s32 func_0023F440(void *arg0);
f32 func_00240D50(void *arg0, s32 arg1);
f32 func_00240DD0(void *arg0, s32 arg1);

extern f32 D_003865AC;
extern f32 D_003865B0;
extern f32 D_003865B4;
extern f32 D_003865B8;
extern f32 D_003865BC;
extern f32 D_003865C0;

void func_0022C140(void *arg0) {
    s32 var_a1;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f20_3;
    f32 temp_f13;
    f32 var_f22;
    s32 temp_v0;
    u8 *p;

    var_a1 = 1;
    if (func_00211310(arg0, 0, 0x100) == 0) {
        var_a1 = 0;
    }
    temp_f20 = func_00240D50(arg0, var_a1);
    var_f22 = temp_f20 * func_00207E90(arg0);
    temp_v0 = BtlObjXf_Update(arg0);
    switch (temp_v0) {
    case 0x38:
        func_001FA110(arg0, 0);
        temp_f20_2 = func_00240D50(arg0, 0x11);
        temp_f13 = func_00240DD0(arg0, 1);
        func_00216890(arg0, temp_f20_2, temp_f13);
        if ((func_00217360(arg0) < 1.0f) || (func_00211310(arg0, 0, 4) != 0)) {
            if (func_00212878(arg0) != 0) {
                if (func_00211310(arg0, 0, 0x8000) == 0) {
                    p = *(u8 **)((u8 *)arg0 + 0x1530);
                    if (*(f32 *)(p + 0xE64) < -10.0f) {
                        goto block_14;
                    }
                } else {
                    goto block_14;
                }
            } else {
block_14:
                p = *(u8 **)((u8 *)arg0 + 0x1530);
                if (!(*(s32 *)(p + 0xE80) & 0x40)) {
                    func_001F9D78(arg0, 0x39);
                    if (func_0023F440(arg0) == 4) {
                        func_0020D240(BtlChar_GetPos(arg0), 100.0f, 1000.0f, D_003865AC, D_003865B0);
                        func_0020D048(BtlChar_GetPos(arg0), 100.0f, 1000.0f, 3.0f, D_003865B4);
                        func_0020FC38(arg0, 0x25);
                        func_00206958(arg0, (s64)0x8000 << 23);
                    } else {
                        if (func_0023F410(arg0) & 0x8000) {
                            func_0020FC38(arg0, 0xB);
                        } else {
                            func_0020FC38(arg0, 0x30);
                        }
                        func_00206958(arg0, (s64)0x8000 << 20);
                    }
                }
            }
        }
        func_002113C0(arg0, 9, 0x80000, 1);
        break;
    case 0x39:
        func_001F9FB0(arg0, 0);
        func_00216678(arg0);
        var_f22 = 0.0f;
        func_002113C0(arg0, 0, 2, 0);
        break;
    }
    temp_f20_3 = D_003865B8;
    func_00215068(arg0, 0, 0xC, D_003865BC, temp_f20_3);
    func_00215E88(arg0, 0, temp_f20_3);
    func_00216208(arg0, var_f22, D_003865C0);
    func_0020D7E8(arg0, 20.0f, 50.0f);
    if (*(u8 *)((u8 *)BtlMember_GetActiveGauge(arg0) + 0x29) != 0) {
        func_002113C0(arg0, 6, 8, 1);
    }
}
