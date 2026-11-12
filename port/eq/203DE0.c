#include "common.h"

void func_001E7598(s32 arg0);
void BtlFacade_ClearCtrl10D(s32 arg0);
void BtlFacade_SetCtrl10D(s32 arg0);

/* 0x00203DE0(obj): f = the 64-bit word at obj+0x338. Bit 0 calls func_001E7598(*(obj+0x1534)), bit 1 calls
 * BtlFacade_ClearCtrl10D(*(obj+0x1534)), bit 2 calls BtlFacade_SetCtrl10D(*(obj+0x1534)). */
void func_00203DE0(u8 *arg0) {
    s64 f = *(s64 *)(arg0 + 0x338);

    if (f & 0x1) {
        func_001E7598(*(s32 *)(arg0 + 0x1534));
    }
    if (f & 0x2) {
        BtlFacade_ClearCtrl10D(*(s32 *)(arg0 + 0x1534));
    }
    if (f & 0x4) {
        BtlFacade_SetCtrl10D(*(s32 *)(arg0 + 0x1534));
    }
}
