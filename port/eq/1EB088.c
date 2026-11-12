#include "common.h"

void func_001E9428(void);

void func_001EB088(s32 arg0, s32 arg1) {
    u8 *temp_a0;
    u16 temp_v1;

    if (arg0 == 0) {
        return;
    }
    if (*(s32 *)(*(u8 **)((u8 *)arg0 + 0x28)) != (s32)0x001E9428u) {
        return;
    }
    temp_a0 = *(u8 **)((u8 *)arg0 + 0x38);
    if (temp_a0 == 0) {
        return;
    }
    temp_v1 = *(u16 *)(temp_a0 + 0x124);
    if ((temp_v1 & 1) == 0) {
        return;
    }
    if ((arg1 & 0xFF) != 0) {
        *(u16 *)(temp_a0 + 0x124) = (u16)(temp_v1 | 0x100);
        return;
    }
    *(u16 *)(temp_a0 + 0x124) = (u16)(temp_v1 & 0xFEFF);
}
