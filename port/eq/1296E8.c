#include "common.h"

void func_001296E8(u8 *arg0, u8 *arg1, s32 arg2) {
    u32 i;
    u32 n = (u32)arg2 * 0x30;

    for (i = 0; i < n; i++) {
        arg0[i] = arg1[i];
    }
}
