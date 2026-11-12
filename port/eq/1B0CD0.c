#include "common.h"

extern u8 *D_00387870;

s32 func_001B0CD0(void *arg0, s32 arg1) {
    u8 *t1;
    s32 t0;
    s32 t3;
    s32 a2;
    s32 a3;
    s32 v0;
    s32 v1;
    u8 *node;

    t1 = NULL;
    t0 = 0;
    t3 = 0;
    a2 = *(s32 *)(D_00387870 + 4);
    for (;;) {
        node = *(u8 **)D_00387870 + a2 * 0x70;
        a3 = a2 + 1;
        if (*(s32 *)node == 0) {
            *(s32 *)(node + 0x60) = 0;
            if (t1 != NULL) {
                *(void **)(t1 + 0x60) = node;
            } else {
                *(void **)arg0 = node;
            }
            *(s32 *)(D_00387870 + 4) = a3;
            t1 = node;
            if (*(s32 *)(D_00387870 + 4) >= 0x1F4) {
                *(s32 *)(D_00387870 + 4) = 0;
            }
            t0 += 1;
            if (t0 >= arg1) {
                *(s32 *)((u8 *)arg0 + 4) = t0;
                return 1;
            }
        }
        a2 = a3;
        t3 += 1;
        v0 = a2 < 0x1F4;
        v1 = t3 < 0x1F4;
        if (v0 == 0) {
            a2 = 0;
        }
        if (v1 == 0) {
            break;
        }
    }
    *(s32 *)((u8 *)arg0 + 4) = t0;
    return 1;
}
