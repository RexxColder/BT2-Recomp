#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 BtlPad_Test48(f32 farg0, s32 arg0, s32 arg1, s32 arg2, f32 farg1);
void func_0020FC38(s32 arg0, s32 arg1, s32 arg2);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00211418(s32 arg0, s32 arg1);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
s32 func_00217488(s32 arg0);
extern f32 D_003864B8;

void func_0022A5D0(s32 arg0) {
    BattleSide_SetChara(arg0, 0x17);
    if (func_00217488(arg0) == 0xE) {
        if (BtlPad_Test48(D_003864B8, arg0, 8, 0xC, 0.0f) == 0) {
            func_002113C0(arg0, 0, 2, 1);
        }
    } else {
        func_00215068(arg0, 0, 0xC, D_003864B8, 0.0f);
    }
    if (func_00211310(arg0, 0, 0x200) != 0) {
        func_0020FC38(arg0, 0x23, 0x100);
    } else if (func_00211310(arg0, 0, 0x100) != 0) {
        func_0020FC38(arg0, 0x39, 0x100);
    } else {
        func_0020FC38(arg0, 0x1E, 0x100);
    }
    func_002113C0(arg0, 0xE, 0x200, 1);
    func_00211418(arg0, 2);
}
