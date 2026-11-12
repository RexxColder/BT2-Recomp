#include "common.h"

s32 func_00241C70(u8 *arg0, s32 arg1) {
    u8 *v0;
    u8 *v1;

    v0 = *(u8 **)(arg0 + 0x1530);
    v1 = *(u8 **)(v0 + 0x984) + ((arg1 != 0) * 4);
    return *(s32 *)(v1 + 8) * 0x186A0;
}
