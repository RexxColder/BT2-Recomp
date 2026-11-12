#include "common.h"

extern u8 *D_00387A40;
s32 func_003126C8(u8 *arg0, s32 arg1);

s32 func_001EDD10(s32 arg0, s32 arg1) {
    return func_003126C8(*(u8 **)(D_00387A40 + 8) + arg0 * 0x1520 + 0x9B0, arg1);
}
