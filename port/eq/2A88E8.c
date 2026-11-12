#include "common.h"

void Queue_Clear(u8 *arg0) {
    *(s32 *)(arg0 + 0x10) = 0;
    *(s32 *)(arg0 + 8) = 0;
    *(s32 *)(arg0 + 0xC) = 0;
}
