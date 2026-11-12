#include "common.h"

s32 func_00306F28(s32 arg0);
void func_00306FA0(s32 arg0);
s32 func_00331710(s32 arg0);
extern u8 D_0037DE80[] __attribute__((section(".data")));
extern u8 D_0037DEA0[] __attribute__((section(".data")));

void func_002FBB20(s32 arg0) {
    func_00306F28(arg0);
    if (arg0 == 0) {
        func_00331710((s32)D_0037DE80);
    } else if (*(s32 *)((u8 *)arg0 + 4) != 1) {
        *(s32 *)((u8 *)arg0 + 4) = 1;
    } else {
        func_00331710((s32)D_0037DEA0);
    }
    func_00306FA0(arg0);
}
