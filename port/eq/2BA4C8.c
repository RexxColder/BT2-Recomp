#include "common.h"

void func_002D6E78(s32 arg0, s32 arg1, s32 arg2);

void func_002BA4C8(u8 *arg0, u8 *arg1, u8 *arg2) {
    s32 loc[2];

    func_002D6E78(*(s32 *)(arg0 + 0xA8), (s32)&loc[0], (s32)&loc[1]);
    *(s32 *)arg2 = loc[1];
    *(s32 *)arg1 = loc[0];
}
