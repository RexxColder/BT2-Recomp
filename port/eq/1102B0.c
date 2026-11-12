#include "common.h"

s32 func_0010B0A0(s32 arg0);
void func_00114508(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00113860(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
s32 func_00113B00(s32 arg0, s32 arg1, s32 arg2);
void func_00113D80(s32 arg0, s32 arg1);
void func_001140A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void BtlRec_CallFlagged(s32 arg0, s32 arg1, s32 arg2);
extern void *D_003876A0;

void func_001102B0(u8 *arg0, s32 arg1) {
    u8 *s0;
    s32 s1;

    s1 = func_0010B0A0(arg1);
    s0 = arg0 + arg1 * 0x750;
    func_00114508(s1, 2, 0, 3);
    func_00113860(s1 + 0xC, 0, 0, 0x5E, 0x20, 0x14);
    s0 += 0xD0;
    func_00113D80(s1, 0);
    func_00113B00(s1, 0x11, 0x3F);
    if (*(s32 *)(s0 + 0x728) >= 3 && *(s32 *)((u8 *)D_003876A0 + 0xC8) != 2) {
        s0 = (u8 *)(s1 + 0x60);
        func_00113860(s1 + 0x6C, 0x5F, 0, 0x80, 0x20, 0x14);
        func_00113D80((s32)s0, 0);
        if (arg1 == 0) {
            func_00113B00((s32)s0, 3, 0x3F);
        } else {
            func_00113B00((s32)s0, 2, 0x3F);
        }
    }
    if (arg1 == 1) {
        func_001140A8(s1, 0, 1, 0, 3);
    }
    BtlRec_CallFlagged(s1, 1, 3);
}
