#include "common.h"

extern u8 *gEftPtcl3Mgr;

/* 0x001B8B78 EftPtcl_UnlinkPtcl (BT3 name, BT2 layout): list head/tail at arg0 +0 / +4, node next = +0x120,
 * prev = +0x124; unlink arg1 and decrement the count at gEftPtcl3Mgr + 8. */
void EftPtcl_UnlinkPtcl(u8 *arg0, u8 *arg1) {
    u8 *prev = *(u8 **)(arg1 + 0x124);
    u8 *next = *(u8 **)(arg1 + 0x120);

    if (prev != NULL) {
        *(u8 **)(prev + 0x120) = next;
    } else {
        *(u8 **)(arg0 + 0x0) = next;
    }
    if (next != NULL) {
        *(u8 **)(next + 0x124) = prev;
    } else {
        *(u8 **)(arg0 + 0x4) = prev;
    }
    *(s32 *)(gEftPtcl3Mgr + 0x8) = *(s32 *)(gEftPtcl3Mgr + 0x8) - 1;
}
