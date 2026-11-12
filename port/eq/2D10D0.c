#include "common.h"

s32 func_002D07B0(s32 arg0, s32 arg1);

void func_002D10D0(s32 arg0, u8 *arg1) {
    if (func_002D07B0(arg0, 0x47) == 1) {
        *(s32 *)(arg1 + 0x2D0) = *(s32 *)(arg1 + 0x2A8);
    } else {
        *(s32 *)(arg1 + 0x2D0) = *(s32 *)(arg1 + 0x2DC);
    }
}
