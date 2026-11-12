#include "common.h"

extern u8 *D_00387850;

void func_001ADF88(void) {
    u8 *p = D_00387850 + 0x344;
    s32 v1 = 2;

    do {
        v1 -= 1;
        *(s32 *)p = 0;
        p -= 0x118;
    } while (v1 >= 0);
    *(s32 *)(D_00387850 + 0x594) = 0;
    *(s32 *)(D_00387850 + 0x474) = 0;
}
