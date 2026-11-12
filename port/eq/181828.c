#include "common.h"

void func_00181828(void **arg0, f32 farg0) {
    u8 *temp_a0;
    u8 *temp_v0;
    temp_a0 = (u8 *)*arg0;
    if (temp_a0 != NULL) {
        temp_v0 = *(u8 **)(temp_a0 + 0x38);
        *(f32 *)(temp_v0 + 0xB0) = farg0;
    }
}
