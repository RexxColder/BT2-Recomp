#include "common.h"

void func_002C3060(u8 *arg0, s32 arg1);
extern u8 D_00346DC4[] __attribute__((section(".data")));

s32 func_002C2FF0(u8 *arg0, s32 arg1) {
    if (arg1 == 0) {
        return 0;
    }
    if (arg0 == NULL) {
        func_002C3060(D_00346DC4, arg1);
    } else {
        s32 v;

        func_002C3060(arg0 + 0x9F8, arg1);
        v = *(s32 *)(arg0 + 0x48);
        if (v > 0) {
            *(s32 *)(arg0 + 0x48) = -v;
        }
    }
    return arg1;
}
