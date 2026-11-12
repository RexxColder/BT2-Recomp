#include "common.h"

void func_002D0AD8(s32 arg0, s32 arg1, s32 *arg2) {
    s32 *temp_v0;

    temp_v0 = *(s32 **)((u8 *)arg0 + arg1 * 0x44 + 0x1F38);
    if (temp_v0 != NULL) {
        *arg2 = *temp_v0;
        return;
    }
    *arg2 = 0;
}
