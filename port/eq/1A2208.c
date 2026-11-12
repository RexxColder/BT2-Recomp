#include "common.h"

extern u8 *D_0038781C;

void *func_001A2208(void *arg0) {
    u8 *ring;
    u8 *t0;
    u8 *entry;
    u8 *a2;
    s32 a1;
    s32 a3;
    s32 v0;
    s32 v1;

    ring = D_0038781C;
    t0 = (u8 *)arg0;
    a2 = NULL;
    a3 = 0;
    a1 = *(s32 *)(ring + 4);
    for (;;) {
        entry = *(u8 **)ring + a1 * 304;
        if (*(s32 *)entry == 0) {
            a2 = entry;
            *(s32 *)(entry + 0x120) = 0;
            *(s32 *)(entry + 0x124) = 0;
            *(s32 *)(D_0038781C + 4) = a1 + 1;
            if (*(s32 *)(D_0038781C + 4) >= 0x64) {
                *(s32 *)(D_0038781C + 4) = 0;
            }
            break;
        }
        a1 += 1;
        a3 += 1;
        v0 = a1 < 0x64;
        v1 = a3 < 0x64;
        if (v0 == 0) {
            a1 = 0;
        }
        if (v1 == 0) {
            break;
        }
    }
    if (a2 == NULL) {
        return NULL;
    }
    if (*(void **)t0 == NULL) {
        *(void **)t0 = a2;
    }
    if (*(void **)(t0 + 4) == NULL) {
        *(void **)(t0 + 4) = a2;
    } else {
        *(void **)(a2 + 0x124) = *(void **)(t0 + 4);
        *(void **)(*(u8 **)(t0 + 4) + 0x120) = a2;
        *(void **)(t0 + 4) = a2;
    }
    return a2;
}
