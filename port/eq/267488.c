#include "common.h"

s32 func_00267488(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x54) == 0) {
        return -1;
    }
    return *(s32 *)(arg0 + 0xDF0 + 8) - 1;
}
