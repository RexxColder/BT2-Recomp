#include "common.h"

s32 func_002D1800(s32 arg0, s32 arg1, s32 arg2);

void func_002D1640(s32 arg0, u8 *arg1, u8 *arg2) {
    if (func_002D1800(arg0, (s32)arg1, (s32)arg2) != 0) {
        *(s32 *)arg1 = -2;
        *(s32 *)arg2 = 1;
    }
}
