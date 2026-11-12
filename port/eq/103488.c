#include "common.h"

s32 func_00100FC8(s32 arg0);
s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0025E068(void);
void func_00261F38(s32 arg0, s32 arg1, u16 arg2, s32 arg3, s32 arg4, s32 arg5);
s32 func_002622F0(void);
void func_00262330(s32 arg0, s32 arg1, u16 arg2);
void func_00206E60(s32 arg0, s32 arg1, s32 arg2);
void func_00277E28(void);
void func_00277E50(s32 arg0);
extern u8 *D_003876A0;

s32 func_00103488(s32 arg0) {
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_v0;
    s32 var_v1;

    temp_v1 = *(s32 *)arg0;
    if (temp_v1 == 0) {
        func_00277E28();
        temp_v0 = func_002622F0();
        *(s32 *)(arg0 + 4) = temp_v0;
        if (temp_v0 == -1) {
            return 1;
        }
        func_00261F38(1, 0, (u16)*(s32 *)(arg0 + 4), *(s32 *)(arg0 + 0xC), -1, -1);
        func_00100FC8(1);
        *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) | 0x1000;
        *(s32 *)arg0 = *(s32 *)arg0 + 1;
        return 0;
    }
    if (temp_v1 == 1) {
        var_v0 = func_00100FC8(0);
        if (var_v0 == 0) {
            return 0;
        }
        func_002113C0(func_00211288(*(s32 *)(arg0 + 0x18)), 0xC, 0x40, 1);
        *(s32 *)arg0 = *(s32 *)arg0 + 1;
    } else if (temp_v1 != 2) {
        return 1;
    }
    /* state 2 (and state 1 after its step) */
    if (*(s64 *)(D_003876A0 + 0x4D8) & 0x100) {
        return 0;
    }
    var_v0 = func_00211310(func_00211288(*(s32 *)(arg0 + 0x18)), 0xC, 0x80);
    if (var_v0 == 0) {
        return 0;
    }
    temp_v0_2 = func_0025E068();
    func_00262330(1, temp_v0_2 & 0xFFFF, (u16)*(s32 *)(arg0 + 4));
    func_00206E60(func_00211288(*(s32 *)(arg0 + 0x18)), temp_v0_2, *(s32 *)(arg0 + 4));
    *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) & (s64)~0x1000;
    func_00277E50((s32)D_003876A0);
    temp_a0 = *(s32 *)(arg0 + 0x18);
    if (temp_a0 == 0) {
        var_v1 = -2;
    } else if (temp_a0 == 1) {
        var_v1 = -3;
    } else {
        return 1;
    }
    *(s32 *)(D_003876A0 + 0x4E0) = *(s32 *)(D_003876A0 + 0x4E0) & var_v1;
    return 1;
}
