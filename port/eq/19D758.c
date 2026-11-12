#include "common.h"

extern s32 func_0019C868 __attribute__((section(".data")));

void func_0019D758(s32 arg0, s32 arg1) {
    s32 temp_a0;

    if ((arg0 != 0) && (*(s32 *)(*(s32 *)(arg0 + 0x28)) == (s32)0x0019C868u)) {
        temp_a0 = *(s32 *)(arg0 + 0x38);
        if ((arg1 & 0xFF) != 0) {
            *(u16 *)(temp_a0 + 0xC24) = (u16)(*(u16 *)(temp_a0 + 0xC24) | 0x200);
            return;
        }
        *(u16 *)(temp_a0 + 0xC24) = (u16)(*(u16 *)(temp_a0 + 0xC24) & 0xFDFF);
    }
}
