#include "common.h"

void func_002B7AA0(s32 arg0, s32 arg1, s32 arg2);
void func_002B7AD0(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00346BEC __attribute__((section(".data")));

void func_002B7A60(s32 arg0, s32 arg1, s32 arg2) {
    if (D_00346BEC == 0) {
        func_002B7AD0(arg0, arg1, arg2);
        return;
    }
    func_002B7AA0(arg0, arg1, arg2);
}
