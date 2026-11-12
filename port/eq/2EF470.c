#include "common.h"

void func_002EF098(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002EF0B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002F5CE8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0030A5F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_0034BC78 __attribute__((section(".data")));

void func_002EF470(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_002EF098(arg0, arg1, arg2, arg3);
    if (D_0034BC78 != 0) {
        func_002EF0B0(arg0, arg1, arg2, arg3);
        return;
    }
    D_0034BC78 = 1;
    func_002EF0B0(arg0, arg1, arg2, arg3);
    func_002F5CE8(arg0, arg1, arg2, arg3);
    func_0030A5F0(arg0, arg1, arg2, arg3);
    D_0034BC78 = 0;
}
