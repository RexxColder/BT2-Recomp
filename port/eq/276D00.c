#include "common.h"

extern u8 *D_003876A0;
extern u8 *gBtlStage;

/* 0x00276D00: 0 if gBtlStage is null, D_003876A0 + 0x4D8 (64-bit) has bit 0x2000, or gBtlStage->4 is null;
 * otherwise (byte at gBtlStage->4 + 0x10) != 0. */
s32 func_00276D00(void) {
    u8 *p;

    if (gBtlStage == NULL) {
        return 0;
    }
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x2000) != 0) {
        return 0;
    }
    p = *(u8 **)(gBtlStage + 0x4);
    if (p == NULL) {
        return 0;
    }
    return *(u8 *)(p + 0x10) != 0;
}
