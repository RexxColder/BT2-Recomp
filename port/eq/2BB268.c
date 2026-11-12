#include "common.h"

s32 func_002B8280(s32 a0);
s32 func_002BAF58(s32 a0);
s32 func_002BB330(s32 a0, s32 a1);
s32 func_002BB348(s32 a0, s32 a1);
void Rand_Range();
extern s32 D_00379D58 __attribute__((section(".data")));
extern s32 D_00379D88 __attribute__((section(".data")));

s32 func_002BB268(s32 arg0, s32 arg1) {
    if (func_002B8280(arg0) != 1) {
        Rand_Range(&D_00379D58);
        return 0;
    }
    if (arg1 < func_002BAF58(arg0)) {
        if (arg1 < 0) {
            Rand_Range(&D_00379D88, arg1);
            return 0;
        }
        return func_002BB348(arg0, func_002BB330(arg0, arg1));
    }
    return 0;
}
