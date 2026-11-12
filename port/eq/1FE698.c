#include "common.h"

void func_00206958(u8 *obj, s64 bits);
u32 BattleResult_GetFlags(u8 *obj);
s32 func_002113C0(u8 *obj, s32 a1, s32 a2, s32 a3);
s32 func_0023E520(u8 *obj);
s32 func_001FCF88(u8 *obj, s32 arg1);
f32 func_0023F238(u8 *obj);
f32 func_0023F258(u8 *obj);
void func_001FBE80(f32 farg0, f32 farg1, u8 *obj);
void BtlChar_Vibrate(f32 farg0, f32 farg1, u8 *obj);

/* 0x001FE698: (a, b) end-of-hit handler: sets state bits on a from its result flags, flags both, then vibrates both
 * (a at half strength). */
void func_001FE698(u8 *a, u8 *b) {
    f32 va;
    f32 vb;
    f32 half;

    func_00206958(a, 0x4000000);
    if ((BattleResult_GetFlags(a) & 0x10000) != 0) {
        func_00206958(a, 0x20000000);
    }
    if ((BattleResult_GetFlags(a) & 0x20000) != 0) {
        func_00206958(a, 0x40000000);
    }
    if ((BattleResult_GetFlags(a) & 0x40000) != 0) {
        func_00206958(a, 0x80000000LL);
    }
    func_002113C0(a, 5, 8, 0);
    func_002113C0(a, 4, 4, 1);
    func_002113C0(a, 0x10, 0x10000000, 1);
    func_002113C0(b, 0x10, 0x10000000, 1);
    func_001FCF88(b, func_0023E520(a));
    va = func_0023F238(a);
    vb = func_0023F258(a);
    if ((BattleResult_GetFlags(a) & 0x800) != 0) {
        func_001FBE80(va, vb, a);
    }
    func_001FBE80(va, vb, b);
    half = 0.5f;
    va = va * half;
    vb = vb * half;
    BtlChar_Vibrate(va, vb, a);
    BtlChar_Vibrate(va, vb, b);
}
