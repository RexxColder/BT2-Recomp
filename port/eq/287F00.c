#include "common.h"

s32 rand(void);

void OldPass_RandomChar(u8 *arg0) {
    s32 s1;
    s32 *p;
    s32 hi;
    s32 hi2;

    s1 = 6;
    p = (s32 *)(arg0 + 4);
    *(s32 *)arg0 = rand() % 129;
    do {
        s1 -= 1;
        *p = rand() % 566;
        p += 1;
    } while (s1 >= 0);
    hi = rand() % 3;
    *(s32 *)(arg0 + 0x20) = hi;
    hi2 = rand() % 7;
    *(s32 *)(arg0 + 0x28) = hi2;
    *(s32 *)(arg0 + 0x24) = rand() % 2;
}
