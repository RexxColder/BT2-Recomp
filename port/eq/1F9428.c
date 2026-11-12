#include "common.h"

/* 0x001F9428: p = arg0 + arg2 + 20 * arg1; with arg4 != 0: byte at p + 0xAFC += arg3, else it is set to arg3. */
void func_001F9428(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *p = arg0 + arg2 + arg1 * 20;

    if (arg4 != 0) {
        *(u8 *)(p + 0xAFC) = (u8)(*(u8 *)(p + 0xAFC) + arg3);
    } else {
        *(u8 *)(p + 0xAFC) = (u8)arg3;
    }
}
