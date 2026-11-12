#include "common.h"

s32 func_002E1A38(void *arg0, void *arg1);
u64 func_002E1C98(s32 arg0, s32 arg1);

/* 0x002E1E30: if func_002E1A38(arg0, arg1) is non-zero, returns func_002E1C98(0, 0xFF03020C). Otherwise copies
 * 0x80 bytes from arg0+0x58 to arg1 in 32-byte blocks and returns the first doubleword of the last block read
 * (arg0+0xB8). */
u64 func_002E1E30(u8 *arg0, u8 *arg1) {
    u64 v0 = 0;
    s32 i;

    if (func_002E1A38(arg0, arg1) != 0) {
        return func_002E1C98(0, (s32)0xFF03020C);
    }
    for (i = 0; i < 0x80; i += 0x20) {
        u64 w0 = *(u64 *)(arg0 + 0x58 + i);
        u64 w1 = *(u64 *)(arg0 + 0x60 + i);
        u64 w2 = *(u64 *)(arg0 + 0x68 + i);
        u64 w3 = *(u64 *)(arg0 + 0x70 + i);

        *(u64 *)(arg1 + i) = w0;
        *(u64 *)(arg1 + i + 0x8) = w1;
        *(u64 *)(arg1 + i + 0x10) = w2;
        *(u64 *)(arg1 + i + 0x18) = w3;
        v0 = w0;
    }
    return v0;
}
