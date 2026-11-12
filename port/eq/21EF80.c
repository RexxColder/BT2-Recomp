#include "common.h"

void func_00206958(s32 arg0, s64 arg1);
void func_0020FC38(s32 arg0, s32 arg1);
void BtlChar_SetSmallVibration(s32 arg0, f32 farg0);
void func_00212DD8(s32 arg0, s32 arg1);
s32 BtlChar_GetPos(s32 arg0);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00217488(s32 arg0);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
extern f32 D_00385EB0;

void func_0021EF80(s32 arg0) {
    s32 p;
    s32 v;
    s32 a0;

    func_00206958(arg0, 0x2000);
    func_0020FC38(arg0, 0x20);
    BtlChar_SetSmallVibration(arg0, D_00385EB0);
    func_00212DD8(arg0, 5);
    p = BtlChar_GetPos(arg0);
    *(s32 *)(p + 0xC0) = 0;
    p = BtlChar_GetPos(arg0);
    *(s32 *)(p + 0xC4) = 0;
    func_002113C0(arg0, 0, 2, 1);
    v = func_00217488(arg0);
    if (v == 0x79) {
        a0 = 0x6B;
    } else if (v == 0x6B || v == 0x7A) {
        a0 = 0x6E;
    } else {
        a0 = 0x6B;
        if (BtlPad_Test48(arg0, 0xC) == 0) {
            a0 = 0x6E;
            if (BtlPad_Test48(arg0, 0xD) == 0) {
                a0 = 0x71;
                if (BtlPad_Test48(arg0, 0xE) == 0) {
                    a0 = (BtlPad_Test48(arg0, 0xF) == 0) ? 0x6E : 0x74;
                }
            }
        }
    }
    *(s32 *)(arg0 + 0x8C8) = a0;
}
