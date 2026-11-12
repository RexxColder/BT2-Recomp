#include "m2c_macros.h"

extern void func_00206958(s32 arg0, s64 arg1);
extern s32 BattleResult_GetFlags(s32 arg0);
extern s32 BtlChar_GetPos(s32 arg0);
extern f32 func_0023F010(s32 arg0);
extern void func_0020E4B0(s32 arg0, f32 farg0, f32 farg1);
extern s32 func_0023F3F0(s32 arg0);
extern s32 func_0023E520(s32 arg0);
extern void func_001FCF88(s32 arg0, s32 arg1);
extern void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_00211418(s32 arg0, s32 arg1);

void func_001FE4F8(s32 arg0, s32 arg1) {
    s32 s0;
    s32 v;
    f32 f;

    func_00206958(arg0, 0x400000);
    if (BattleResult_GetFlags(arg0) & 0x10000) {
        func_00206958(arg0, 0x20000000);
    }
    if (BattleResult_GetFlags(arg0) & 0x20000) {
        func_00206958(arg0, 0x40000000);
    }
    if (BattleResult_GetFlags(arg0) & 0x40000) {
        func_00206958(arg0, (s32)0x80000000);
    }
    func_002113C0(arg0, 5, 8, 0);
    func_002113C0(arg0, 4, 4, 1);
    *(s32 *)(arg0 + 0x1440) = *(s32 *)(arg0 + 0x1440) + 1;
    s0 = BtlChar_GetPos(arg0);
    f = func_0023F010(arg0);
    func_0020E4B0(arg1, *(f32 *)(s0 + 0xB4), f);
    v = func_0023F3F0(arg0);
    if (v == 0) {
        func_002113C0(arg1, 4, 0x200, 1);
    } else if (v == 1 || v == 2) {
        func_002113C0(arg1, 4, 0x400, 1);
    } else {
        func_002113C0(arg1, 4, 0x200, 1);
    }
    func_001FCF88(arg1, func_0023E520(arg0));
    func_00211418(arg1, 0x800000);
}
