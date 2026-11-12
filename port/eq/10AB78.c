#include "common.h"

void func_0028C3B0(s32 arg0, s32 arg1);
s32 func_0028C648(s32 arg0);
extern u8 D_003B0B00[] __attribute__((section(".data")));

s32 func_0010AB78(u8 *arg0) {
    s32 n;
    s32 i;

    if (func_0028C648((s32)arg0) != 0) {
        return 0;
    }
    n = *(s32 *)arg0;
    for (i = 0; i < n; i++) {
        if (*(s32 *)(D_003B0B00 + 0x134 + i * 0x180) & 8) {
            *(s32 *)(arg0 + 4) = i;
            func_0028C3B0(i, n);
            return 1;
        }
    }
    return 0;
}
