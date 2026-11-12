#include "common.h"

void func_001E04C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0);

void func_001E0370(u8 *arg0, s32 arg1, s32 arg2) {
    u32 temp_a2;
    u8 *temp_v0;

    temp_a2 = arg2 & 0xFF;
    if (temp_a2 < *(u8 *)(arg0 + 0x10F00)) {
        temp_v0 = arg0 + (temp_a2 * 0x21E0);
        if (temp_v0[0x21DD] != 0) {
            func_001E04C8((s32)temp_v0, arg1, (s32)temp_a2, (s32)arg0,
                          *(f32 *)(arg0 + (temp_a2 * 4) + 0x10F04));
        }
    }
}
