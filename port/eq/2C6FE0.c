#include "common.h"

s32 func_002C1370(s32 arg0, s32 arg1, s32 arg2);
s32 func_002E0A98(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_00379FE8[] __attribute__((section(".data")));

s32 func_002C6FE0(u8 *arg0) {
    s32 sp[2];
    s32 temp_v0;
    s32 temp_v0_2;
    u8 *temp_s1;

    temp_s1 = arg0 + 0xD30;
    if (*(s32 *)(*(u8 **)arg0 + 0xC) != (s32)D_00379FE8) {
        sp[1] = 0xAC44;
        sp[0] = 0;
    } else {
        if (func_002C1370((s32)arg0, (s32)sp, (s32)&sp[1]) == 0) {
            return -1;
        }
    }
    temp_v0_2 = *(s32 *)(temp_s1 + 0x1F0) + sp[0];
    *(s32 *)(temp_s1 + 0x1F0) = temp_v0_2;
    temp_v0 = func_002E0A98(temp_v0_2, *(s32 *)(arg0 + 0xD94), sp[1]) - *(s32 *)(temp_s1 + 0x164);
    return (temp_v0 < 0) ? 0 : temp_v0;
}
