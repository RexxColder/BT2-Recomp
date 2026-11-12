#include "common.h"

s32 func_002113C0(u8 *a0, s32 a1, s32 a2, s32 a3);
s32 func_00211310(u8 *a0, s32 a1, s32 a2);
void func_00215068(u8 *a0, s32 a1, s32 a2, f32 farg0, f32 farg1);
s32 func_00217488(u8 *a0);
void BattleSide_SetChara(u8 *a0, s32 a1);
s32 func_00206958(u8 *a0, s64 a1);
void func_00211418(u8 *a0, s32 a1);
void func_0020FC38(u8 *a0, s32 a1);
u8 *BtlChar_GetPos(u8 *a0);
extern f32 D_0038699C;

void func_00234F50(u8 *arg0) {
    s32 v;
    u8 *p;

    func_002113C0(arg0, 7, (s32)0xFFFDFFFF, 0);
    if (func_00211310(arg0, 0, 1) != 0) {
        func_00215068(arg0, 1, 0xC, D_0038699C, 1.0f);
    }
    v = func_00217488(arg0);
    if (v == 0xBC) {
        BattleSide_SetChara(arg0, 0x13E);
        func_00206958(arg0, (s64)0x8000 << 39);
        func_002113C0(arg0, 0xF, 0x2000, 1);
        func_00211418(arg0, 0x80000);
    } else if (v == 0xBB) {
        BattleSide_SetChara(arg0, 0x11C);
        func_00206958(arg0, (s64)0x8000 << 38);
        func_002113C0(arg0, 0xF, 0x1000, 1);
        func_00211418(arg0, 0x80000);
    } else if (v == 0xBD) {
        BattleSide_SetChara(arg0, 0x182);
        func_00206958(arg0, (s64)0x8000 << 40);
        func_002113C0(arg0, 0xF, 0x4000, 1);
        func_00211418(arg0, 0x100000);
    }
    func_0020FC38(arg0, 0x2B);
    func_002113C0(arg0, 0, 2, 1);
    *(s32 *)(arg0 + 0xA30) = 0;
    p = BtlChar_GetPos(arg0);
    *(s32 *)(p + 0xC0) = 0;
    BtlChar_GetPos(arg0);
}
