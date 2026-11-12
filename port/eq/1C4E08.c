#include "common.h"

extern u8 *gEftRibbonMgr;

void *func_001C4E08(void *arg0) {
    u8 *ring;
    u8 *t0;
    u8 *entry;
    u8 *a3;
    s32 a1;
    s32 a2;
    s32 v0;
    s32 v1;

    ring = gEftRibbonMgr;
    t0 = (u8 *)arg0;
    a3 = NULL;
    a2 = 0;
    a1 = *(s32 *)(ring + 4);
    for (;;) {
        entry = *(u8 **)ring + a1 * 80;
        if (*(s32 *)entry == 0) {
            a3 = entry;
            *(s32 *)(entry + 0x40) = 0;
            *(s32 *)(entry + 0x44) = 0;
            *(s32 *)(gEftRibbonMgr + 4) = a1 + 1;
            if (*(s32 *)(gEftRibbonMgr + 4) >= 0x1F4) {
                *(s32 *)(gEftRibbonMgr + 4) = 0;
            }
            break;
        }
        a1 += 1;
        a2 += 1;
        v0 = a1 < 0x1F4;
        v1 = a2 < 0x1F4;
        if (v0 == 0) {
            a1 = 0;
        }
        if (v1 == 0) {
            break;
        }
    }
    if (a3 == NULL) {
        return NULL;
    }
    if (*(void **)t0 == NULL) {
        *(void **)t0 = a3;
    }
    if (*(void **)(t0 + 4) == NULL) {
        *(void **)(t0 + 4) = a3;
    } else {
        *(void **)(a3 + 0x44) = *(void **)(t0 + 4);
        *(void **)(*(u8 **)(t0 + 4) + 0x40) = a3;
        *(void **)(t0 + 4) = a3;
    }
    return a3;
}
