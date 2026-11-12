#include "common.h"

void func_002F9300(s32 arg0);
extern u8 D_0037D400[] __attribute__((section(".data")));
extern u8 D_0037D420[] __attribute__((section(".data")));

s32 func_002FA020(s32 arg0) {
    s32 fp;
    s32 var_s0;

    var_s0 = 3;
    if (arg0 == 0) {
        func_002F9300((s32)D_0037D400);
        return 3;
    }
    fp = *(s32 *)(*(s32 *)arg0 + 0x2C);
    if (fp == 0) {
        func_002F9300((s32)D_0037D420);
    } else {
        var_s0 = ((s32 (*)(s32))fp)(*(s32 *)((u8 *)arg0 + 4));
    }
    return var_s0;
}
