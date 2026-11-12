#include "common.h"

s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
s32 func_00217488(s32 arg0);
void BattleSide_SetChara(s32 arg0, s32 arg1);
void func_00206958(s32 arg0, s64 arg1);
void func_00211418(s32 arg0, s32 arg1);
s32 func_00212320(s32 arg0);
void func_0020FC38(s32 arg0, s32 arg1);
s32 func_00203C58(s32 arg0, s64 arg1);
void func_00203888(s32 arg0, s32 arg1, s32 arg2);
s32 func_00241718(s32 arg0, s32 arg1);
s32 BtlMember_GetActiveGauge(s32 arg0);
s32 BtlChar_GetPos();

extern f32 D_003868F8;

void func_00233008(u8 *arg0) {
    s32 s1;
    s32 v3;
    s32 a1v;
    s32 *ptr;

    func_002113C0((s32)arg0, 7, 0xFFFDFFFF, 0);
    if (func_00211310((s32)arg0, 0, 1) != 0) {
        func_00215068((s32)arg0, 1, 0xC, D_003868F8, 1.0f);
    }

    v3 = func_00217488((s32)arg0);
    if (v3 == 0xB5) {
        BattleSide_SetChara((s32)arg0, 0x11C);
        func_00206958((s32)arg0, (s64)0x8000 << 38);
        func_002113C0((s32)arg0, 0xF, 0x1000, 1);
        func_00211418((s32)arg0, 0x80000);
    } else if (v3 == 0xB7) {
        BattleSide_SetChara((s32)arg0, 0x182);
        func_00206958((s32)arg0, (s64)0x8000 << 40);
        func_002113C0((s32)arg0, 0xF, 0x4000, 1);
        func_00211418((s32)arg0, 0x100000);
    } else if (v3 == 0xB6) {
        BattleSide_SetChara((s32)arg0, 0x13E);
        func_00206958((s32)arg0, (s64)0x8000 << 39);
        func_002113C0((s32)arg0, 0xF, 0x2000, 1);
        func_00211418((s32)arg0, 0x80000);
    }

    s1 = func_00212320((s32)arg0);
    func_0020FC38((s32)arg0, 0x2B);
    if (func_00203C58((s32)arg0, 0x10000000) != 0) {
        func_00203888((s32)arg0, 0x186A0, 1);
    } else {
        func_00203888((s32)arg0, func_00241718((s32)arg0, s1), 1);
    }

    ptr = (s32 *)(BtlMember_GetActiveGauge((s32)arg0) + s1 * 4 + 0x30);
    a1v = *ptr + 1;
    *ptr = a1v;
    *(s32 *)(arg0 + 0xA30) = 0;
    *(s32 *)(BtlChar_GetPos((s32)arg0, a1v) + 0xC0) = 0;
    *(s32 *)(BtlChar_GetPos((s32)arg0) + 0xC4) = 0;
}
