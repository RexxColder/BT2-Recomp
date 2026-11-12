#include "common.h"

extern u8 *gEftPtcl4Mgr;

void func_001BCDA0(u8 *arg0, u8 *arg1) {
    u8 *prev = *(u8 **)(arg1 + 0xE4);
    u8 *next = *(u8 **)(arg1 + 0xE0);

    if (prev != NULL) {
        *(u8 **)(prev + 0xE0) = next;
    } else {
        *(u8 **)(arg0 + 0) = next;
    }
    next = *(u8 **)(arg1 + 0xE0);
    prev = *(u8 **)(arg1 + 0xE4);
    if (next != NULL) {
        *(u8 **)(next + 0xE4) = prev;
    } else {
        *(u8 **)(arg0 + 4) = prev;
    }
    *(s32 *)(gEftPtcl4Mgr + 8) = *(s32 *)(gEftPtcl4Mgr + 8) - 1;
}
