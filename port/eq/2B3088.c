#include "common.h"

s32 func_002B93D0(s32 arg0, s32 arg1);
s32 func_002B9FC0(void *arg0);

s32 func_002B3088(void *arg0) {
    s32 temp_s1;
    s32 temp_v0;

    temp_s1 = func_002B93D0(*(s32 *)((u8 *)arg0 + 0x8), *(s32 *)((u8 *)arg0 + 0xC));
    temp_v0 = func_002B9FC0(arg0);
    if (temp_v0 == 1) {
        temp_s1 += 0x20000;
    }
    return temp_s1;
}
