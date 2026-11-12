#include "common.h"

s32 rand(void);

void OldPass_RandomShort(void *arg0) {
    u8 *p;
    s32 r;

    p = (u8 *)arg0;
    *(s32 *)(p + 0x0) = rand() % 129;
    *(s32 *)(p + 0x4) = rand() % 129;
    *(s32 *)(p + 0xC) = rand() % 3;
    *(s32 *)(p + 0x8) = (rand() % 1048575) * 100;
    *(s32 *)(p + 0x14) = rand() % 7;
    r = rand();
    *(s32 *)(p + 0x10) = r % 2;
}
