#include "common.h"

extern u8 *D_0038790C;

void BtlPool_Reset(s32 arg0) {
    u8 *p = D_0038790C + arg0 * 0x10;

    if (*(s32 *)(D_0038790C + 0x68) & (1 << (arg0 + 1))) {
        *(s32 *)(p + 0xC) = 0;
        *(s32 *)(p + 4) = *(s32 *)(p + 0);
    }
}
