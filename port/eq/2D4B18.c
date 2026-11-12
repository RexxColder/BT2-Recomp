#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
void *memcpy(void *arg0, const void *arg1, u32 arg2);
s32 func_002D45E8(u8 *arg0, u8 *arg1);

s32 func_002D4B18(u8 *arg0, u8 *arg1) {
    u8 *s1;

    *(u8 *)(arg1 + 0) = 0;
    s1 = *(u8 **)(arg0 + 4) + 0xE0;
    if (func_002D45E8(arg0, arg1) == 0) {
        return 0;
    }
    memset(arg1, 0, 0x41);
    memcpy(arg1, s1, 0x40);
    return 1;
}
