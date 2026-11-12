#include "common.h"

s32 func_00217488(s32 arg0);
void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 BtlMember_GetActiveGauge(s32 arg0);
void BtlMember_SubBlast(s32 arg0, s32 arg1);
void func_00206958(s32 arg0, s64 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00211418(s32 arg0, s32 arg1);
s32 func_00212320(s32 arg0);
s32 func_00241C70(s32 arg0, s32 arg1);

void func_0023B6D0(s32 arg0) {
    s32 var_a1;
    s32 var_s0;
    s32 temp_v0;
    s32 temp_s0;
    s32 *p;

    var_s0 = 0x11A;
    temp_v0 = func_00217488(arg0);
    if (temp_v0 == 0xDC) {
        func_00206958(arg0, (s64)0x8000 << 36, 0xDD);
        func_002113C0(arg0, 0xF, 0x400, 1);
        var_a1 = var_s0;
    } else if (temp_v0 == 0xDD) {
        func_00206958(arg0, (s64)0x8000 << 37, 0xDD);
        var_s0 = 0x11B;
        func_002113C0(arg0, 0xF, 0x800, 1);
        var_a1 = var_s0;
    } else {
        var_a1 = var_s0;
    }
    BattleSide_SetChara(arg0, var_a1);
    temp_s0 = func_00212320(arg0);
    func_002113C0(arg0, 0, 2, 1);
    p = (s32 *)(BtlMember_GetActiveGauge(arg0) + (temp_s0 * 4) + 0x30);
    *p += 1;
    BtlMember_SubBlast(arg0, func_00241C70(arg0, temp_s0));
    func_00211418(arg0, 0x40000);
}
