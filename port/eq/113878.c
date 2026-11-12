#include "common.h"

void func_00113878(s32 arg0, s32 arg1, s32 arg2) {
    s64 temp_v1;
    s16 a2;

    a2 = (s16)arg2;
    temp_v1 = *(s64 *)((s32)(a2 << 6) + *(s32 *)(arg1 + 0x10) + 0x30);
    *(s16 *)(arg0 + 8) = a2;
    *(s16 *)(arg0 + 4) = (s16)(1 << (((s64)((u64)temp_v1 << 6) >> 0x20) & 0xF));
    *(s16 *)(arg0 + 6) = (s16)(1 << (((s64)((u64)temp_v1 << 2) >> 0x20) & 0xF));
    *(s16 *)(arg0 + 0) = 0;
    *(s16 *)(arg0 + 2) = 0;
}
