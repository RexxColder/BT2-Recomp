#include "common.h"

s32 BattleResult_GetFlags(u8 *arg0);
void func_00206958(u8 *arg0, s64 arg1);
s32 func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
u8 *BtlChar_GetPos(u8 *arg0);
void func_001FCF88(u8 *arg0, s32 arg1);
void func_0020E4B0(u8 *arg0, f32 farg0, f32 farg1);
s32 func_0023E520(u8 *arg0);
f32 func_0023F010(u8 *arg0);
extern f32 D_00385870;

void func_001FEED0(u8 *arg0, u8 *arg1) {
    f32 f20;
    u8 *pos;

    func_00206958(arg0, (s64)0x400000);
    if (BattleResult_GetFlags(arg0) & 0x10000) {
        func_00206958(arg0, (s64)0x20000000);
    }
    if (BattleResult_GetFlags(arg0) & 0x20000) {
        func_00206958(arg0, (s64)0x40000000);
    }
    if (BattleResult_GetFlags(arg0) & 0x40000) {
        func_00206958(arg0, (s64)0x8000 << 16);
    }
    func_002113C0(arg0, 5, 8, 0);
    func_002113C0(arg0, 4, 4, 1);
    *(s32 *)(arg0 + 0x1440) = *(s32 *)(arg0 + 0x1440) + 1;
    f20 = func_0023F010(arg0);
    if (f20 < D_00385870) {
        f20 = D_00385870;
    }
    pos = BtlChar_GetPos(arg0);
    func_0020E4B0(arg1, *(f32 *)(pos + 0xB4), f20);
    func_002113C0(arg1, 0x10, 0x1000000, 1);
    func_001FCF88(arg1, func_0023E520(arg0));
}
