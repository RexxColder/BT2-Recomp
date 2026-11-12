#include "common.h"

s32 BattleResult_GetFlags(s32 arg0);
s32 BtlChar_GetPos(s32 arg0);
f32 func_0023F010(s32 arg0);
void func_0020E4B0(s32 arg0, f32 farg0, f32 farg1);
s32 func_0023E520(s32 arg0);
void func_001FCF88(s32 arg0, s32 arg1);
void func_00203968(s32 arg0, s32 arg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00206958(s32 arg0, s64 arg1);
s32 func_00211418(s32 arg0, s32 arg1);

s32 func_001FEB28(u8 *arg0, u8 *arg1) {
    u8 *s0;
    f32 f0v;

    func_00206958((s32)arg0, (s64)0x2000000);
    if (BattleResult_GetFlags((s32)arg0) & 0x10000) {
        func_00206958((s32)arg0, (s64)0x20000000);
    }
    if (BattleResult_GetFlags((s32)arg0) & 0x20000) {
        func_00206958((s32)arg0, (s64)0x40000000);
    }
    if (BattleResult_GetFlags((s32)arg0) & 0x40000) {
        func_00206958((s32)arg0, (s64)0x8000 << 16);
    }
    func_002113C0((s32)arg0, 4, 0x200000, 1);
    *(s32 *)(arg0 + 0x1440) = *(s32 *)(arg0 + 0x1440) + 1;
    s0 = (u8 *)BtlChar_GetPos((s32)arg0);
    f0v = func_0023F010((s32)arg0);
    func_0020E4B0((s32)arg1, *(f32 *)(s0 + 0xB4), f0v);
    func_002113C0((s32)arg1, 4, 0x100000, 1);
    func_00203968((s32)arg1, 0xC350);
    func_001FCF88((s32)arg1, func_0023E520((s32)arg0));
    return func_00211418((s32)arg1, 0x800000);
}
