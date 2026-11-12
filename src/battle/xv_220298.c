#include "common.h"

void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/* calls func_002113C0(arg0, 2, 0x100, 1), then stores 0x1E at +0xB84 of the object */
void func_00220298(s32 arg0) {
    s32 v;
    func_002113C0(arg0, 2, 0x100, 1);
    v = 0x1E;
    *(s32 *)((u8 *)arg0 + 0xB84) = v;
}
