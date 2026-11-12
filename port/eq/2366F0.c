#include "common.h"

s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00217488(s32 arg0);
void BattleSide_SetChara(s32 arg0, s32 arg1);
void func_00206958(s32 arg0, s64 arg1);
void func_00211418(s32 arg0, s32 arg1);
s32 func_00212320(s32 arg0);
void func_0020FC38(s32 arg0, s32 arg1);
s32 BtlMember_GetActiveGauge(s32 arg0);
s32 func_00203C58(s32 arg0, s64 arg1);
s32 func_00203888(s32 arg0, s32 arg1, s32 arg2);
s32 func_00241718(s32 arg0, s32 arg1);
s32 BtlChar_GetPos(s32 arg0);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
extern f32 D_003869F0;

void func_002366F0(u8 *arg0) {
    s32 a = (s32)arg0;
    s32 v0;
    s32 s1;

    func_002113C0(a, 7, (s32)0xFFFDFFFF, 0);
    if (func_00211310(a, 0, 1) != 0) {
        func_00215068(a, 1, 9, D_003869F0, 1.0f);
    }
    v0 = func_00217488(a);
    if (v0 == 0xCA) {
        BattleSide_SetChara(a, 0x11C);
        func_00206958(a, (s64)0x8000 << 38);
        func_002113C0(a, 0xF, 0x1000, 1);
        func_00211418(a, 0x80000);
    } else if (v0 == 0xCB) {
        BattleSide_SetChara(a, 0x13E);
        func_00206958(a, (s64)0x8000 << 39);
        func_002113C0(a, 0xF, 0x2000, 1);
        func_00211418(a, 0x80000);
    } else if (v0 == 0xCC) {
        BattleSide_SetChara(a, 0x182);
        func_00206958(a, (s64)0x8000 << 40);
        func_002113C0(a, 0xF, 0x4000, 1);
        func_00211418(a, 0x100000);
    }
    s1 = func_00212320(a);
    func_0020FC38(a, 0x2B);
    func_002113C0(a, 0, 2, 1);
    *(s32 *)(s32)(BtlMember_GetActiveGauge(a) + (s1 * 4 + 0x30)) += 1;
    if (func_00203C58(a, 0x10000000) != 0) {
        func_00203888(a, 0x186A0, 1);
    } else {
        func_00203888(a, func_00241718(a, s1), 1);
    }
    *(s32 *)(arg0 + 0xA30) = 0;
    *(s32 *)((u8 *)BtlChar_GetPos(a) + 0xC0) = 0;
    *(s32 *)((u8 *)BtlChar_GetPos(a) + 0xC4) = 0;
}
