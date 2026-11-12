#include "common.h"

s32 func_002B49F8(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x4) != 0) {
        return (*(s32 *)(arg0 + 0xC) != 0) ? 1 : 3;
    }
    if (*(s32 *)(arg0 + 0x8) == 0) {
        return 0;
    }
    if (*(s32 *)(arg0 + 0xC) == 0) {
        return 2;
    }
    return 0;
}
