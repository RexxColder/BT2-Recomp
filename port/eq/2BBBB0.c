#include "common.h"

s32 func_002BC1A0(s32 arg0);

void func_002BBBB0(u8 *arg0) {
    s32 (*temp_v0_2)(s32, s32);
    u8 *temp_v0;

    if (func_002BC1A0((s32)arg0) == 1) {
        temp_v0 = *(u8 **)(arg0 + 8);
        if (temp_v0 != NULL) {
            temp_v0_2 = *(s32 (**)(s32, s32))(temp_v0 + 0x14);
            if (temp_v0_2 != NULL) {
                temp_v0_2(*(s32 *)(arg0 + 0x1C), *(s32 *)(arg0 + 0x14));
            }
        }
    }
}
