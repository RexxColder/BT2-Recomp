#include "common.h"

s32 func_0010B0A0(s32 arg0);
s32 func_0010CD98(s32 arg0, s32 arg1);
s32 BtlRec_CallFlagged(s32 arg0, s32 arg1, s32 arg2);
s32 func_00113B00(s32 arg0, s32 arg1, s32 arg2);
void func_00113CB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001140A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_00114508(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_00110488(s32 arg0, s32 arg1) {
    s32 *temp_s1;
    s32 temp_s0;

    temp_s1 = (s32 *)(func_0010B0A0(arg1) + 0x120);
    temp_s0 = func_0010CD98(arg1, 0);
    func_00114508((s32)temp_s1, 2, 0, 2);
    if (temp_s0 != 0) {
        func_00113CB8((s32)temp_s1, 0, temp_s0, 0);
        func_00113B00((s32)temp_s1, 0x13, 0x3F);
        *temp_s1 |= 0x100;
        if (arg1 == 1) {
            func_001140A8((s32)temp_s1, 0, 1, 0, 2);
        }
        return BtlRec_CallFlagged((s32)temp_s1, 1, 2);
    }
    return 0;
}
