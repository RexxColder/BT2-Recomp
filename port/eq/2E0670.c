#include "common.h"

extern u8 D_00399DA8[] __attribute__((section(".data")));

void func_002E0670(s32 arg0, s32 arg1) {
    s32 count = *(s32 *)(D_00399DA8 + 0x54);
    u8 *p = (u8 *)*(s32 *)(D_00399DA8 + 0x58);

    while (count > 0) {
        count -= 1;
        if (*(s32 *)(p + 0x188) == 2) {
            *(s32 *)(p + arg0 * 4 + 0x190) = arg1;
        }
        p += 0x440;
    }
}
