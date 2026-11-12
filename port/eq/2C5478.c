#include "common.h"

s32 func_002C54C8(s32 arg0);

s32 func_002C5478(s32 arg0) {
    s32 field = *(s32 *)((u8 *)arg0 + 0x36B0);

    if (field == 0) {
        return 0;
    }
    if (func_002C54C8(arg0) <= 0) {
        return *(s32 *)((u8 *)arg0 + 0x36B0) + 0x8A0;
    }
    return 0;
}
