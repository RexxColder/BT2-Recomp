#include "common.h"

extern u8 D_00346BF0 __attribute__((section(".data")));

u8 *func_002BC158(s32 arg0) {
    return &D_00346BF0 + arg0 * 8;
}
