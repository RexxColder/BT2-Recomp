#include "common.h"

s32 BattleResult_GetFlags(u8 *arg0);
void func_00206958(u8 *arg0, s64 arg1);
s32 func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212DD8(u8 *arg0, s32 arg1);
s32 func_00203888(u8 *arg0, s32 arg1, s32 arg2);
s32 func_0023FB20(u8 *arg0);
s32 func_0023E520(u8 *arg0);
void func_001FCF88(u8 *arg0, s32 arg1);

void func_001FEC50(u8 *arg0, u8 *arg1) {
    func_00206958(arg0, (s64)0x10000000);
    if (BattleResult_GetFlags(arg0) & 0x10000) {
        func_00206958(arg0, (s64)0x20000000);
    }
    if (BattleResult_GetFlags(arg0) & 0x20000) {
        func_00206958(arg0, (s64)0x40000000);
    }
    if (BattleResult_GetFlags(arg0) & 0x40000) {
        func_00206958(arg0, (s64)0x8000 << 16);
    }
    func_002113C0(arg0, 4, 0x200000, 1);
    *(s32 *)(arg0 + 0x988) = 2;
    *(s32 *)(arg0 + 0x98C) = 1;
    *(s32 *)(arg0 + 0x1440) = *(s32 *)(arg0 + 0x1440) + 1;
    func_002113C0(arg1, 4, 0x10, 1);
    func_00212DD8(arg1, 0x12);
    *(s32 *)(arg1 + 0x988) = 3;
    *(s32 *)(arg1 + 0x98C) = 0;
    func_00203888(arg1, func_0023FB20(arg1), 0);
    func_002113C0(arg1, 0x10, 0x400000, 1);
    func_001FCF88(arg1, func_0023E520(arg0));
}
