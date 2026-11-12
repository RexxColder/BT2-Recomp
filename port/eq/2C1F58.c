#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
s32 func_002C2000(void *arg0, s32 arg1, s32 arg2);
extern u8 D_0037A0A0[] __attribute__((section(".data")));
extern u8 D_0037A0B0[] __attribute__((section(".data")));
extern u8 D_00346C10[] __attribute__((section(".data")));

/* 0x002C1F58(a0, a1, out): buf (0x10 bytes) from func_002C2000(buf, a0, a1); when that returns nonzero: out+0xC = 0,
 * out+0x28 byte = D_0037A0A0[4 * buf[6]], out+0x2C word = D_0037A0B0[4 * buf[3]] (as words), then the block
 * buf[0..7], buf[8], buf[9], buf[10] is copied to D_00346C10 (+0..7, +8, +9, +0xA). Returns 1, else 0. */
s32 func_002C1F58(s32 arg0, s32 arg1, u8 *arg2) {
    u8 buf[0x10];

    if (func_002C2000(buf, arg0, arg1) == 0) {
        return 0;
    }
    *(s32 *)(arg2 + 0xC) = 0;
    arg2[0x28] = D_0037A0A0[(u32)buf[6] << 2];
    *(s32 *)(arg2 + 0x2C) = *(s32 *)(D_0037A0B0 + ((u32)buf[3] << 2));
    memcpy(D_00346C10, buf, 8);
    D_00346C10[8] = buf[8];
    D_00346C10[9] = buf[9];
    D_00346C10[0xA] = buf[0xA];
    return 1;
}
