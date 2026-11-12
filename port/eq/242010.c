#include "common.h"

s32 func_00242010(u8 *arg0, s32 arg1) {
    u8 *p = *(u8 **)(*(u8 **)(arg0 + 0x1530) + 0x984) + ((arg1 != 0) * 4);
    return *(s32 *)(p + 0xA8) / 30;
}
