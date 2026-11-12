#include "common.h"

s32 BtlChar_GetPos(s32 arg0);
s32 func_00211288(s32 arg0);
s32 func_002B1DD0(s32 arg0, s32 arg1);
void func_003126C8(s32 arg0, s32 arg1);
void func_00209018(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00387930;
extern s32 D_00387E18;

void func_00208AA0(s32 arg0, s32 arg1) {
    s32 temp_a2;

    temp_a2 = (u32)arg0 < 2U;
    if (D_00387930 != 0) {
        if (temp_a2 != 0) {
            func_003126C8(arg1, BtlChar_GetPos(func_00211288(arg0)) + 0x40);
            return;
        }
    }
    if (D_00387E18 != 0) {
        if ((u32)arg0 < 3U) {
            func_003126C8(arg1, func_002B1DD0(arg0, arg1) + 0x130);
            return;
        }
    }
    func_00209018(arg0, arg1, 0);
}
