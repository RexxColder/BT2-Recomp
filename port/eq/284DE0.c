#include "common.h"

extern u8 D_00388F88[] __attribute__((section(".data")));

s32 func_00284DE0(u32 arg0) {
    u32 idx;

    idx = (arg0 >= 3U) ? 0U : arg0;
    return D_00388F88[idx * 0x60] != 0;
}
