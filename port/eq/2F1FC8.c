#include "m2c_macros.h"

void func_002F1FC8(u8 *arg0) {
    s8 v;

    *(s32 *)(arg0 + 0x34) = 0;
    *(s32 *)(arg0 + 0x4C) = 0;
    if (*(s32 *)(arg0 + 0x14) == 0) {
        v = 3;
    } else {
        v = 2;
    }
    *(s8 *)(arg0 + 1) = v;
    *(s8 *)(arg0 + 2) = 0;
    *(s32 *)(arg0 + 0x24) = 0;
    *(s32 *)(arg0 + 0x28) = 0;
    *(s8 *)(arg0 + 0x47) = 1;
}
