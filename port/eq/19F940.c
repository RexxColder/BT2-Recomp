#include "common.h"

void func_0019F940(u8 *arg0, s32 arg1) {
    if (arg0 == NULL) {
        return;
    }
    if (*(s32 *)(*(u8 **)(arg0 + 0x28)) != (s32)0x0019FAC8) {
        return;
    }
    if (*(u8 *)(arg0 + 0) & 1) {
        return;
    }
    *(s8 *)(*(u8 **)(arg0 + 0x38) + 0x2C) = (s8)(arg1 & 0xFF);
}
