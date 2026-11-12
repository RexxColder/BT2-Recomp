#include "common.h"

void func_002F9300(s32 arg0);
extern u8 D_0037D318[] __attribute__((section(".data")));
extern u8 D_0037D338[] __attribute__((section(".data")));

s32 func_002F9DC8(s32 arg0) {
    s32 fp;
    s32 var_s0;

    var_s0 = 0;
    if (arg0 == 0) {
        func_002F9300((s32)D_0037D318);
        return 0;
    }
    fp = *(s32 *)(*(s32 *)arg0 + 0x18);
    if (fp == 0) {
        func_002F9300((s32)D_0037D338);
    } else {
        var_s0 = ((s32 (*)(s32))fp)(*(s32 *)((u8 *)arg0 + 4));
    }
    return var_s0;
}
