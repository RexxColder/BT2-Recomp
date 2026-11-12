#include "common.h"

s32 func_002C3528(s32 arg0);
s32 func_002DC8C0(s32 arg0, u8 *arg1);
s32 func_002C2FF0(u8 *arg0, s32 arg1);
extern s32 D_00346E50 __attribute__((section(".data")));
extern u8 D_00395118[] __attribute__((section(".data")));

s32 func_002C34B8(s32 arg0) {
    if (func_002C3528(arg0) != 0) {
        for (;;) {
        }
    }
    if (func_002DC8C0(8, D_00395118) != 0) {
        return func_002C2FF0(NULL, 0xFF000D01);
    }
    D_00346E50 = 0;
    return 0;
}
