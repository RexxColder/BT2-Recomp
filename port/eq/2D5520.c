#include "common.h"

void *func_002D5210(s32 arg0, s32 arg1);
s32 func_002D5B08(s32 arg0);

void *func_002D5520(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    s32 temp_s0;
    u8 *temp_s1;
    u8 *temp_a1;

    temp_s0 = arg1 & 0xFF;
    *arg2 = 0;
    *arg3 = 0;
    temp_s1 = (u8 *)func_002D5210(arg0, temp_s0);
    if (temp_s1 == NULL) {
        return NULL;
    }
    if (func_002D5B08(temp_s0) != 0xE0) {
        return NULL;
    }
    temp_a1 = temp_s1 + 0x1C;
    *arg2 = (s32)((temp_s1[0x1C] * 0x10) | (temp_a1[1] >> 4));
    *arg3 = ((temp_a1[1] << 8) | temp_a1[2]) & 0xFFF;
    return (void *)1;
}
