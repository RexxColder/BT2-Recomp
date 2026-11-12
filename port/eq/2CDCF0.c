#include "common.h"

s32 func_002D11B0(void *arg0, void *arg1, void *arg2);

s32 func_002CDCF0(void *arg0) {
    u8 *temp_a2;

    temp_a2 = (u8 *)arg0 + 0x950;
    if (*(s32 *)((u8 *)arg0 + 0x48) != 4) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0x50) == 1) {
        return 0;
    }
    if (*(s32 *)(temp_a2 + 0x20) == 1) {
        return 0;
    }
    return func_002D11B0(arg0, arg0, temp_a2) != 0;
}
