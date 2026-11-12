#include "common.h"

void func_002BA0D8(u8 *arg0) {
    u8 *p = arg0 + 0x194;
    *(s32 *)(p + 8) = 0;
    *(s32 *)(arg0 + 0x194) = 0;
    *(s32 *)(p + 4) = 0;
    *(s32 *)(arg0 + 0x190) = -1;
}
