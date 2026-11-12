#include "common.h"

void BtlMenu_EndDraw(s32 arg0, s32 arg1, f32 farg0);
s32 func_002B0DA0(s32 arg0, s32 arg1, f32 farg0);
s32 func_002B0DB0(s32 arg0, s32 arg1);
extern f32 D_00387424;
extern f32 D_00387428;

s32 func_002AEFF0(s32 arg0) {
    if (func_002B0DB0(arg0, 0x05000000) != 0) {
        BtlMenu_EndDraw(arg0, 0x800, D_00387424);
        return 0xA;
    }
    if (func_002B0DA0(arg0, 0x800, D_00387424) != 0) {
        BtlMenu_EndDraw(arg0, 0x800, D_00387428);
        return 0xC;
    }
    return -1;
}
