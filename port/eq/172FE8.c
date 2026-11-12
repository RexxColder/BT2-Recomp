#include "common.h"

s32 BtlScene_IsCharStopped(s32 arg0);
s32 func_00129C38(s32 arg0, s32 arg1);

void func_00172FE8(u8 *arg0) {
    u8 *temp_s1;

    temp_s1 = *(u8 **)(arg0 + 0x38);
    if (BtlScene_IsCharStopped(*(s32 *)*(u8 **)(temp_s1 + 0xA0)) == 0 && (*(s32 *)(arg0 + 4) & 4)) {
        func_00129C38((s32)(temp_s1 + 0x70), (s32)(arg0 + 0x10));
    }
}
