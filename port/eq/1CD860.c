#include "common.h"

extern s32 EftPtcl3_IsAlive(s32 a0);

s32 func_001CD860(u8 *obj) {
    s32 alive = 0;
    s32 i;
    s32 j;
    u8 *row = *(u8 **)(obj + 0x38);
    u32 *slot;

    for (i = 0; i < 2; i++) {
        slot = (u32 *)(row + 0x10);
        for (j = 1; j >= 0; j--) {
            if (EftPtcl3_IsAlive(*slot) != 0) {
                alive = 1;
            } else {
                *slot = 0;
            }
            slot = (u32 *)((u8 *)slot + 4);
        }
        row += 8;
    }
    return alive;
}
