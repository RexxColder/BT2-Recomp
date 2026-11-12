#include "common.h"

extern u8 *D_00387760;

/* 0x00147E70 EftShot_IsSlotFlag2000: record at D_00387760[4] + arg0 * 0x270 + arg1 * 0x50; its pointer at +0x20 ->
 * word at +0x30 has bit 0x2000. Returns 1 if set. */
s32 EftShot_IsSlotFlag2000(s32 arg0, s32 arg1) {
    u8 *p;

    if (D_00387760 == NULL) {
        return 0;
    }
    p = *(u8 **)(D_00387760 + 0x4) + arg0 * 0x270 + arg1 * 0x50;
    u8 *q = *(u8 **)(p + 0x20);

    return (*(s32 *)(q + 0x30) & 0x2000) != 0;
}
