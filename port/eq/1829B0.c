#include "common.h"

void func_00182380(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 BtlTask_SetDead(s32 arg0);

s32 func_001829B0(u8 *arg0) {
    u8 *p = (u8 *)*(s32 *)(arg0 + 0x38);
    s32 v = *(s32 *)(p + 0xA80);

    if ((v & 0x200) == 0) {
        *(s32 *)(p + 0xA80) = v | 0x200;
        func_00182380((s32)arg0, *(s32 *)(p + 0xA24), 1, (s32)(p + 0xA00));
    }
    return BtlTask_SetDead((s32)arg0);
}
