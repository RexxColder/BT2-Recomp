#include "common.h"

void func_001E06E0(void *arg0, s32 arg1, f32 farg0) {
    u32 temp_a1;

    temp_a1 = arg1 & 0xFF;
    if (temp_a1 < *(u8 *)((u8 *)arg0 + 0x10F00)) {
        *(f32 *)((u8 *)arg0 + temp_a1 * 4 + 0x10F04) = farg0;
    }
}
