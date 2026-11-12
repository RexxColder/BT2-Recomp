#include "common.h"

s32 func_002F5358(s32 arg0);
void func_002F52A8(s32 arg0, s32 arg1);
extern s32 gStgPanBlur;

void func_00101498(void) {
    s32 v0 = func_002F5358(gStgPanBlur);
    s32 v = (v0 - 0x7D < -0x3C0) ? -0x3C0 : v0;

    func_002F52A8(gStgPanBlur, v - 0x7D);
}
