#include "common.h"

extern u8 D_00346BF0 __attribute__((section(".data")));

s32 func_002BC170(s32 arg0) {
    return *(s32 *)(&D_00346BF0 + arg0 * 8);
}
