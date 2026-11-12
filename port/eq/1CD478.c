#include "common.h"

void func_001CD478(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    *(s32 *)(arg0 + 0) = arg1;
    *(s32 *)(arg0 + 4) = arg2;
    *(u16 *)(arg0 + 0xC) = (u16)(*(u16 *)(arg0 + 0xC) | 1);
    *(s32 *)(arg0 + 8) = arg3;
}
