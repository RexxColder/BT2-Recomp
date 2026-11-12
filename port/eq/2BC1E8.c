#include "common.h"

s32 func_00307AF8(s32 arg0);
extern s32 D_00393E40 __attribute__((section(".data")));
extern s32 D_00393E44 __attribute__((section(".data")));
extern s32 D_00393E48 __attribute__((section(".data")));
extern s32 D_00393E4C __attribute__((section(".data")));

void func_002BC1E8(s32 arg0) {
    func_00307AF8(arg0);
    D_00393E40 = 0;
    D_00393E44 = 0;
    D_00393E48 = 0;
    D_00393E4C = 0;
}
