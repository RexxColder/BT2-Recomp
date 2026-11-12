#include "common.h"

extern u8 D_003B2654 __attribute__((section(".data")));

void func_002ACE58(s32 arg0) {
    s32 temp_v1;
    temp_v1 = *(s32 *)(&D_003B2654 + 4);
    *(s32 *)(&D_003B2654 + 4) = arg0;
    *(s32 *)(&D_003B2654 + 8) = temp_v1;
}
