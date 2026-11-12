#include "common.h"

void BtlMenu_EndDraw(f32 farg0, s32 arg1);
s32 func_002B0DA0();
s32 func_002B0DB0();
s32 func_002B20B0();
extern f32 D_00387364;
extern f32 D_00387368;
extern f32 D_0038736C;
extern f32 D_00387370;
extern f32 D_00387374;
extern f32 D_00387378;

s32 func_002AE468(void *arg0) {
    s32 a;

    a = (s32)arg0;
    if (*(u8 *)((u8 *)arg0 + 0x188) != 0) {
        BtlMenu_EndDraw(D_00387364, a);
        return 1;
    }
    if (func_002B0DA0(a, 0x400) != 0) {
        BtlMenu_EndDraw(D_00387368, a);
        return 6;
    }
    if (func_002B0DB0(a, 0x100) != 0) {
        BtlMenu_EndDraw(D_0038736C, a);
        return 3;
    }
    if (func_002B0DB0(a, 0x800) != 0) {
        BtlMenu_EndDraw(D_00387370, a);
        return 4;
    }
    if (func_002B0DB0(a, 0x200) != 0) {
        BtlMenu_EndDraw(D_00387374, a);
        return 5;
    }
    if (func_002B0DA0(a, 0x4000) == 0) {
        return -1;
    }
    if (func_002B20B0(a) < 0) {
        return -1;
    }
    BtlMenu_EndDraw(D_00387378, a);
    return 7;
}
