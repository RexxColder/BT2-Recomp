#include "common.h"

s32 func_002F1F10(u8 *arg0, s32 arg1);
s32 func_002F3190(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0xC) = arg1;
    return func_002F1F10(arg0, 0);
}
