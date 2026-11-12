#include "common.h"

extern u8 func_001E9428[] __attribute__((section(".data")));

s32 func_001EB038(s32 arg0) {
    u8 *temp_a0;
    u16 flag;

    if (arg0 == 0) {
        return 0;
    }
    if (*(s32 *)*(s32 *)((u8 *)arg0 + 0x28) != (s32)0x001E9428u) {
        return 0;
    }
    temp_a0 = (u8 *)*(s32 *)((u8 *)arg0 + 0x38);
    if (temp_a0 == 0) {
        return 0;
    }
    flag = *(u16 *)(temp_a0 + 0x124);
    if ((flag & 1) == 0) {
        return 0;
    }
    return (flag & 0x10) == 0;
}
