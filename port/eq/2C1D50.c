#include "common.h"

s32 func_002BD7B0(s32 arg0, s32 arg1, s32 arg2);
void *memcpy(void *arg0, void *arg1, u32 arg2);
extern u8 D_00393E78[] __attribute__((section(".data")));
extern u8 D_00379FE8[] __attribute__((section(".data")));

s32 func_002C1D50(u8 *arg0, s32 arg1, u8 *arg2) {
    s32 sp[4];
    s32 s0;
    s32 n;
    u8 *s1;

    s0 = (arg1 >= 0x801) ? 0x800 : arg1;
    s1 = D_00393E78;
    memcpy(D_00393E78, arg0, s0);
    if (s0 > 0) {
        do {
            n = s0;
            s0 -= 4;
            if (func_002BD7B0((s32)s1, n, (s32)sp) != 0) {
                *(s32 *)(arg2 + 0xC) = (s32)D_00379FE8;
                *(u8 *)(arg2 + 0x28) = s1[7];
                *(s32 *)(arg2 + 0x2C) = (s32)(((u32)s1[8] << 24) | (u32)s1[0xB] | ((u32)s1[0xA] << 8) | ((u32)s1[9] << 16));
                return 1;
            }
            s1 += 4;
        } while (s0 > 0);
    }
    return 0;
}
