#include "common.h"

void func_0021ED80(u8 *arg0, s32 arg1) {
    if (arg1 == 0x10) {
        *(s32 *)(arg0 + 0x9A0) += 1;
    } else if (arg1 == 0x70) {
        *(s32 *)(arg0 + 0x9A8) += 1;
    }
}
