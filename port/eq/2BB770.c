#include "common.h"

void func_002B8790(s32 arg0, s32 arg1, s32 arg2);
void func_002BAEA0(s32 arg0, s32 arg1, s32 arg2);

void func_002BB770(s32 arg0) {
    s32 sp0;
    s32 sp4;

    func_002B8790(arg0, (s32)&sp0, (s32)&sp4);
    if (sp0 / sp4 >= *(s32 *)(arg0 + 0x2FC) / 1000 && *(s32 *)(arg0 + 0x2E8) == 2) {
        func_002BAEA0(arg0, 1000, 2);
        *(s32 *)(arg0 + 0x2E8) = 3;
    }
}
