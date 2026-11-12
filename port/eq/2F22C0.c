#include "common.h"

void func_002F22C0(u8 *arg0, s32 arg1) {
    if (arg1 < 0) {
        *(s32 *)(arg0 + 0x30) = *(s32 *)(arg0 + 0x14);
        return;
    }
    *(s32 *)(arg0 + 0x30) = arg1;
}
