#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002C3210(s32 arg0);
s32 func_002D07B0(s32 arg0, s32 arg1);
extern s32 D_00346C28[] __attribute__((section(".data")));

s32 func_002D0710(s32 arg0, s32 arg1, s32 *arg2) {
    if (arg0 == 0) {
        *arg2 = D_00346C28[arg1];
        return 0;
    }
    if (func_002C3210(arg0) != 0) {
        return func_002C2FF0(0, 0xFF000113);
    }
    *arg2 = func_002D07B0(arg0, arg1);
    return 0;
}
