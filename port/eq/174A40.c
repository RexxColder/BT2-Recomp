#include "common.h"

/* 0x00174A40 EftTechEvt_IsRushTech: 1 when the record at +0x20 exists and its word at +0x20 is in 5..7. */
s32 EftTechEvt_IsRushTech(u8 *arg0) {
    u8 *p = *(u8 **)(arg0 + 0x20);

    if (p == NULL) {
        return 0;
    }
    return (u32)(*(s32 *)(p + 0x20) - 5) < 3U;
}
