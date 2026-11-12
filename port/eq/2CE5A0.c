#include "common.h"

s32 func_002D2F30(u8 *arg0, s32 arg1);

s32 func_002CE5A0(u8 *arg0) {
    *(s32 *)(arg0 + 0x4C) = 0;
    *(s32 *)(arg0 + 0x48) = 0;
    return func_002D2F30(arg0, 4);
}
