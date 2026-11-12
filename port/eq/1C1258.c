#include "common.h"

void func_001C1258(u8 *arg0, s32 arg1) {
    u8 *t;

    if (arg0 != NULL) {
        t = *(u8 **)(arg0 + 0x38);
        if (t != NULL && (arg1 == 0 || (arg1 & 4) || (arg1 & 2))) {
            *(s32 *)(t + 0xAC8) = arg1;
        }
    }
}
