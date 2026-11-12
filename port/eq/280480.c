#include "common.h"

void func_0027FA28(s32 arg0, s32 arg1, s32 arg2);
void func_0027FAC8(s32 arg0, s32 arg1, s32 arg2);
void func_0027FCA8(s32 arg0, s32 arg1, s32 arg2);
void func_0027FD28(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_003876A0;

void func_00280480(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;

    temp_s0 = arg1 & 0xFF;
    func_0027FA28(arg0, temp_s0, arg2);
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x100) == 0) {
        func_0027FAC8(arg0, temp_s0, arg2);
    }
    func_0027FCA8(arg0, temp_s0, arg2);
    func_0027FD28(arg0, temp_s0, arg2);
}
