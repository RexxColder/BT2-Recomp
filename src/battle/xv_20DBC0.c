#include "common.h"

f32 BtlOpp_GetDistance(s32 arg0);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
f32 func_0020DB08(s32 arg0, s32 arg1);
void func_0020FC38(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00211328(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_0020DBC0(s32 arg0) {
    f32 temp_f20;
    s32 var_v0;

    if (func_00211310(arg0, 1, 0x10000) != 0) {
        if (func_00211310(arg0, 0, 1) != 0) {
            if ((BtlPad_Test48(arg0, 0xD) != 0) && (BtlPad_Test4C(arg0, 6) != 0)) {
                *(s32 *)((u8 *)(arg0) + 0x1018) = 1;
            }
            if (BtlPad_Test48(arg0, 6) != 0) {
                var_v0 = *(s32 *)((u8 *)(arg0) + 0x1018);
                if (var_v0 > 0) {
                    var_v0 += 1;
                    *(s32 *)((u8 *)(arg0) + 0x1018) = var_v0;
                }
                if (var_v0 >= 3) {
                    func_002113C0(arg0, 0, 1, 0);
                }
            } else {
                goto block_10;
            }
        } else {
block_10:
            *(s32 *)((u8 *)(arg0) + 0x1018) = 0;
        }
    }
    if (*(s32 *)((u8 *)(arg0) + 0xB8C) > 0) {
        func_002113C0(arg0, 0, 1, 0);
        if (func_00211310(arg0, 0xA, 0x200) != 0) {
            func_002113C0(arg0, 0, 0x10000, 1);
        }
    }
    if (func_00211310(arg0, 0xA, 0x80) != 0) {
        func_002113C0(arg0, 0, 1, 0);
    }
    func_002113C0(arg0, 1, 1, 0);
    if ((func_00211310(arg0, 1, 0x800) == 0) && (func_00211310(arg0, 0, 0x400000) != 0) && (*(s32 *)((u8 *)(arg0) + 0xB8C) <= 0) && (*(s32 *)((u8 *)(arg0) + 0xB48) < 3) && (func_00211310(arg0, 0xA, 0x80) == 0)) {
        temp_f20 = func_0020DB08(arg0, 0);
        if (BtlOpp_GetDistance(arg0) < temp_f20) {
            func_002113C0(arg0, 1, 1, 1);
            func_002113C0(arg0, 0, 1, 1);
        }
    }
    func_002113C0(arg0, 1, 0x800, 0);
    if (func_00211310(arg0, 0, 1) == 0) {
        if (func_00211328(arg0, 0, 1) != 0) {
            func_0020FC38(arg0, 0x2D);
        }
    }
    if (func_00211310(arg0, 0, 1) != 0) {
        func_002113C0(arg0, 0, 0x10000, 0);
    }
}
