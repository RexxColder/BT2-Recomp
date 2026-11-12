#include "common.h"

s32 func_2EF218(s32);
s32 func_003B4B90(s32);
extern s32 D_00421384 __attribute__((section(".data")));

void func_003B46A0(s32 arg0) {
    func_2EF218(arg0);
    func_003B4B90(D_00421384 + 0x20);
}
