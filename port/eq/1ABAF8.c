#include "common.h"

s32 func_001267E8(s32 arg0, s32 arg1);
void func_001AA2B0(void *arg0);

void func_001ABAF8(void *arg0) {
    u8 *temp_s0;

    temp_s0 = *(u8 **)((u8 *)arg0 + 0x38);
    if (func_001267E8(*(s16 *)(temp_s0 + 0x52), 0) == 0) {
        if (!(*(s32 *)temp_s0 & 0x80)) {
            func_001AA2B0(arg0);
        }
    }
}
