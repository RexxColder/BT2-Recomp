#include "common.h"

extern s32 D_003877BC;

void func_00190900(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u16 temp_v0;
    u8 *temp_a0;

    if (D_003877BC != 0 && arg0 != NULL && arg1 != 0) {
        temp_a0 = *(u8 **)(arg0 + 0x38);
        if (temp_a0 != NULL) {
            temp_v0 = *(u16 *)(temp_a0 + 0x44);
            if (temp_v0 & 2) {
                *(u16 *)(temp_a0 + 0x44) = temp_v0 | 0x400;
                *(s32 *)temp_a0 = arg1;
                *(s8 *)(temp_a0 + 0x50) = (s8)arg3;
                *(s8 *)(temp_a0 + 0x4E) = 1;
                *(s8 *)(temp_a0 + 0x46) = (s8)arg2;
            }
        }
    }
}
