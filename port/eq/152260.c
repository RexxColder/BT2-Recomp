#include "common.h"

s32 EftShot_TestBits(s32 arg0, s32 arg1);
void func_00152328(s32 arg0, s32 arg1, s32 arg2);

void func_00152260(s32 arg0, s32 arg1) {
    s32 s0;

    s0 = (EftShot_TestBits(arg0, 2) == 0) ? 0 : 2;
    if (EftShot_TestBits(arg0, 4) != 0) {
        s0 = s0 | 4;
    }
    if (EftShot_TestBits(arg0, 8) != 0) {
        s0 = s0 | 8;
    }
    if (EftShot_TestBits(arg0, 0x10) != 0) {
        s0 = s0 | 0x10;
    }
    if (EftShot_TestBits(arg0, 0x20) != 0) {
        s0 = s0 | 0x20;
    }
    if (EftShot_TestBits(arg0, 0x40) != 0) {
        s0 = s0 | 0x40;
    }
    func_00152328(arg0, arg1, (EftShot_TestBits(arg0, 0x80) == 0) ? s0 : (s0 | 0x80));
}
