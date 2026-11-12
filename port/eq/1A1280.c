#include "common.h"

extern u8 *D_0038780C;

s32 func_001A1280(s32 arg0) {
    return *(s32 *)(D_0038780C + arg0 * 4) != 0;
}
