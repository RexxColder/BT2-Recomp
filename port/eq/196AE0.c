#include "m2c_macros.h"

void func_001EC460(void *arg0);

void func_00196AE0(void *arg0) {
    u8 *temp_a0;
    s32 temp_v0;

    temp_a0 = *(u8 **)((u8 *)arg0 + 0x38) + 0xA10;
    temp_v0 = *(s32 *)(temp_a0 + 0xB0);
    if (temp_v0 != 0) {
        if (!(temp_v0 & 0x20)) {
            if (temp_v0 & 1) {
                func_001EC460(temp_a0);
            }
        }
    }
}
