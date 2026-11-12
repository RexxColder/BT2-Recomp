#include "common.h"

void func_002C94B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_t0;
    u32 temp_v1;
    s32 temp_a0;
    s32 temp_a1;

    temp_t0 = *(s32 *) (arg0 + 0x38);
    if (temp_t0 != 3) {
        *(s32 *) arg2 = 0;
        *(s32 *) arg3 = 0;
        return;
    }
    temp_v1 = *(u32 *) (arg1 + 0xA4);
    if (temp_v1 == 2) {
        temp_a0 = *(s32 *) (arg1 + 0x160);
        *(s32 *) arg2 = *(s32 *) (temp_a0 + 0x40);
        *(s32 *) arg3 = *(s32 *) (temp_a0 + 0x44);
        return;
    }
    if ((temp_v1 < 3U) || (temp_v1 != (u32) temp_t0)) {
        *(s32 *) arg2 = 0;
        *(s32 *) arg3 = 0;
        return;
    }
    temp_a1 = *(s32 *) (arg1 + 0x164);
    temp_a0 = *(s32 *) (arg1 + 0x160);
    *(s32 *) arg2 = *(s32 *) (temp_a0 + 0x40) + *(s32 *) (temp_a1 + 0x40);
    *(s32 *) arg3 = *(s32 *) (temp_a0 + 0x44) + *(s32 *) (temp_a1 + 0x44);
}
