#include "common.h"

s32 func_00284DE0(s32 arg0);
extern u8 D_00388F30[] __attribute__((section(".data")));

s32 func_00284E08(u32 arg0) {
    u8 *s0;
    s32 ret;
    u32 idx;

    idx = (arg0 >= 3U) ? 0U : arg0;
    s0 = D_00388F30 + idx * 0x60;
    ret = func_00284DE0((s32)idx);
    if (ret != 0) {
        ret = (*(u8 *)(s0 + 0x58) & 8) != 0;
    }
    return ret;
}
