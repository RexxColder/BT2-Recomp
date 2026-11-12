#include "common.h"

extern u8 *gBtlStage __attribute__((section(".data")));

s32 func_002745F8(s32 arg0) {
    u8 *p;

    p = *(u8 **)(gBtlStage + 0x5C) + *(s32 *)(gBtlStage + 0x48) * 4;
    return (*(s32 *)(p + arg0 * 0x50) & 1) != 0;
}
