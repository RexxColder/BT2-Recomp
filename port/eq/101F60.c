#include "common.h"

extern u8 *func_00101A88(s32 arg0);

void func_00101F60(void) {
    s32 side;

    for (side = 0; side < 2; side++) {
        u8 *list = func_00101A88(side);
        s32 count = *(s32 *)list;
        s32 i;

        if (count >= 2) {
            u8 *entry = list + 0x54;

            for (i = 0; i < count; i++) {
                *(s32 *)entry = *(s32 *)(entry + 4);
                entry += 0x58;
                count = *(s32 *)list;
            }
        }
    }
}
