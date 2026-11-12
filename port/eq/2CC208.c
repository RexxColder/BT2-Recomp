#include "common.h"

void func_003162E8(s32 arg0);
void func_002CB748(s32 arg0);
s32 func_002CC168(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0037A358[] __attribute__((section(".data")));

s32 func_002CC208(s32 arg0, s32 arg1, u8 *arg2) {
    s32 temp_v0;
    u8 *temp_s0;
    u8 *temp_s1;

    temp_v0 = *(s32 *)(arg2 + 0x1FC0);
    temp_s1 = (u8 *)(temp_v0 + 0x1128);
    temp_s0 = (u8 *)(temp_v0 + 0x1198);
    if (*(s32 *)(temp_s1 + 0x18) == 1) {
        func_003162E8(temp_v0 + 0x1150);
    } else {
        func_002CB748((s32)temp_s0);
        if ((*(s32 *)(temp_s1 + 0x14) != 0) && (*(s32 *)(temp_s0 + 0x10) == 0)) {
            *(s32 *)(temp_s1 + 0x18) = 1;
            func_002CC168((s32)temp_s0, (s32)D_0037A358, 0x10);
            *(s32 *)(temp_s0 + 0x14) = *(s32 *)(temp_s0 + 0x18);
            func_002CB748((s32)temp_s0);
        }
    }
    return 1;
}
