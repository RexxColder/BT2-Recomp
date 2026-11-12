#include "common.h"

void func_00206958(s32 arg0, s64 arg1);
void func_0020FC38(s32 arg0, s32 arg1);
void BtlChar_SetSmallVibration(f32 farg0, s32 arg1);
s32 func_00217490(s32 arg0);
void func_00212DD8(s32 arg0, s32 arg1);
s32 BtlChar_GetPos(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 BtlPad_Test48();
extern f32 D_00385E74;

void func_0021E608(void *arg0) {
    s32 a;
    s32 r;
    s32 p;
    s32 val;

    a = (s32)arg0;
    func_00206958(a, 0x2000);
    func_0020FC38(a, 0x20);
    BtlChar_SetSmallVibration(D_00385E74, a);
    r = func_00217490(a);
    if (r < 0x50 && r >= 0x4A) {
        func_00212DD8(a, 0x1D);
    } else {
        func_00212DD8(a, 5);
    }
    p = BtlChar_GetPos(a);
    *(s32 *)((u8 *)p + 0xC0) = 0;
    p = BtlChar_GetPos(a);
    *(s32 *)((u8 *)p + 0xC4) = 0;
    func_002113C0(a, 0, 2, 1);
    if (BtlPad_Test48(a, 0xC) != 0) {
        val = 0x6B;
    } else if (BtlPad_Test48(a, 0xD, 0x6B) != 0) {
        val = 0x6E;
    } else if (BtlPad_Test48(a, 0xE, 0x6E) != 0) {
        val = 0x71;
    } else {
        val = (BtlPad_Test48(a, 0xF, 0x71) == 0) ? 0x6E : 0x74;
    }
    *(s32 *)((u8 *)arg0 + 0x8C8) = val;
}
