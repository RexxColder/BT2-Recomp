#include "common.h"

extern s32 D_003879D0;

void func_00254138(s32 arg0) {
    s32 sh = arg0 & 31;
    s32 bit = 0x10 << sh;
    s32 v1 = *(s32 *)(D_003879D0 + 0x15C);

    if ((v1 & bit) == 0) {
        if (*(s32 *)(D_003879D0 + 0x298) == arg0) {
            *(s32 *)(D_003879D0 + 0x294) = 5;
        }
    } else {
        *(s32 *)(D_003879D0 + 0x15C) = v1 ^ bit;
    }
    v1 = *(s32 *)(D_003879D0 + 0x15C);
    bit = 0x200 << sh;
    if ((v1 & bit) != 0) {
        *(s32 *)(D_003879D0 + 0x15C) = v1 ^ bit;
    }
    v1 = *(s32 *)(D_003879D0 + 0x15C);
    *(s32 *)(D_003879D0 + 0x15C) = v1 | (4 << sh);
}
