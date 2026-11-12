#include "common.h"

s32 func_001FA3A8(s32 arg0);
s32 func_00210DD8(s32 arg0, s32 arg1, s32 arg2);
u8 *func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0025F990(s32 arg0, s32 arg1, s32 arg2);
void func_0025FAF0(s32 arg0, s32 arg1, s32 arg2);
void func_00267550(s32 arg0, s32 arg1, s32 arg2);
void func_001F9A20(s32 arg0, s32 arg1);

void BattleSide_SetChara(u8 *arg0, s32 arg1) {
    u8 *a3;
    u8 *v1;
    s32 p;
    u8 *q;

    if (func_001FA3A8(arg1) & 0x80) {
        p = func_00210DD8((s32)arg0, arg1, 1);
        q = func_00211288(p);
        func_0025FAF0(*(s32 *)(arg0 + 0x152C), *(s32 *)(q + 0x152C), arg1);
    } else {
        func_0025F990(*(s32 *)(arg0 + 0x152C), arg1, 1);
    }
    a3 = *(u8 **)(arg0 + 0x1530);
    *(s32 *)(a3 + 0xAF0) = *(s32 *)(a3 + 0xAF0) & ~0x20;
    v1 = *(u8 **)(arg0 + 0x1530);
    *(s32 *)(v1 + 0xAF0) = *(s32 *)(v1 + 0xAF0) & ~0x40;
    if (func_00211310((s32)arg0, 2, 0x600000, (s32)a3) != 0) {
        func_00267550(*(s32 *)(arg0 + 0x1530), 0, 0);
    }
    func_002113C0((s32)arg0, 2, 0x200000, 0);
    func_002113C0((s32)arg0, 2, 0x400000, 0);
    func_002113C0((s32)arg0, 9, 0x100000, 0);
    func_001F9A20(*(s32 *)(*(u8 **)(arg0 + 0x1530) + 0xBF8), arg1);
    func_002113C0((s32)arg0, 2, 0x71, 0);
    func_002113C0((s32)arg0, 2, 2, 1);
    *(s32 *)(arg0 + 0x8E0) = arg1;
    *(s32 *)(arg0 + 0x8E4) = -1;
}
