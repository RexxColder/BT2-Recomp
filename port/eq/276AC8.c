#include "common.h"

extern u8 *D_003876A0;
extern u8 *gBtlStage;

/* 0x00276AC8: the byte at +0x16 of the record at gBtlStage + 4, or 0xFF when gBtlStage or that pointer is NULL or the
 * flag 0x2000 of the s64 at +0x4D8 of D_003876A0 is set. */
s32  func_00276AC8(void) {
    u8 r = 0xFF;
    u8 *p;

    if (gBtlStage != NULL && !(*(s64 *)(D_003876A0 + 0x4D8) & 0x2000)) {
        p = *(u8 **)(gBtlStage + 4);
        if (p != NULL) {
            r = *(u8 *)(p + 0x16);
        }
    }
    return (u8)(r);
}
