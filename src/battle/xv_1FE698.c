#include "common.h"

s32 BattleResult_GetFlags(s32 arg0);
void BtlChar_Vibrate(s32 arg0, f32 farg0, f32 farg1);
void func_001FBE80(s32 arg0, f32 farg0, f32 farg1);
void func_001FCF88(s32 arg0, s32 arg1);
void func_00206958(s32 arg0, s64 arg1);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0023E520(s32 arg0);
f32 func_0023F238(s32 arg0);
f32 func_0023F258(s32 arg0);

/* battle start setup for two fighters (arg0, arg1): flag words, flag calls, then halved vibration */
void func_001FE698(s32 arg0, s32 arg1) {
    f32 f21;
    f32 f22;

    func_00206958(arg0, 0x04000000);
    if (BattleResult_GetFlags(arg0) & 0x10000) {
        func_00206958(arg0, 0x20000000);
    }
    if (BattleResult_GetFlags(arg0) & 0x20000) {
        func_00206958(arg0, 0x40000000);
    }
    if (BattleResult_GetFlags(arg0) & 0x40000) {
        func_00206958(arg0, (s64)0x8000 << 16);
    }
    func_002113C0(arg0, 5, 8, 0);
    func_002113C0(arg0, 4, 4, 1);
    func_002113C0(arg0, 0x10, 0x10000000, 1);
    func_002113C0(arg1, 0x10, 0x10000000, 1);
    func_001FCF88(arg1, func_0023E520(arg0));
    f21 = func_0023F238(arg0);
    f22 = func_0023F258(arg0);
    if (BattleResult_GetFlags(arg0) & 0x800) {
        func_001FBE80(arg0, f21, f22);
    }
    func_001FBE80(arg1, f21, f22);
    BtlChar_Vibrate(arg0, f21 * 0.5f, f22 * 0.5f);
    BtlChar_Vibrate(arg1, f21 * 0.5f, f22 * 0.5f);
}
