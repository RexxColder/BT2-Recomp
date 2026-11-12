#include "common.h"

void func_0014EEF8(s32 arg0, s32 arg1);

void func_0019CCA8(u8 *arg0) {
    u8 *temp_a0;

    temp_a0 = *(u8 **)(arg0 + 0x38);
    if (*(u16 *)(temp_a0 + 0xC24) & 0x40) {
        func_0014EEF8(*(s32 *)temp_a0, (s32)(temp_a0 + 0x90));
    }
}
