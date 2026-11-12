#include "common.h"

s32 BtlTask_SetDead(s32 arg0);
s32 func_00162518(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
u8 *func_001F3758(s32 arg0);

s32 func_00162DA8(u8 *arg0) {
    s32 temp_a2;
    s32 temp_v0;
    u8 *temp_v1;

    temp_v1 = *(u8 **)(arg0 + 0x38);
    temp_a2 = *(s32 *)(func_001F3758((s32)arg0) + 0x38);
    temp_v0 = *(s32 *)temp_v1;
    if (!(temp_v0 & 0x100)) {
        *(s32 *)temp_v1 = temp_v0 | 0x100;
        func_00162518(*(s32 *)*(u8 **)(temp_v1 + 0xB0), (s32)arg0, temp_a2, 0);
    }
    return BtlTask_SetDead((s32)arg0);
}
