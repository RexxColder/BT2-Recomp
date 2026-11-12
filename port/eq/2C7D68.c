#include "common.h"

void func_002C7E60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4);
void func_002C8078(u8 *arg0, u8 *arg1, s32 arg2);

void func_002C7D68(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s1;
    u16 temp_v1;
    u8 *temp_s0;

    temp_s0 = arg0 + 0xD30;
    temp_s1 = *(s32 *)(arg1 + 0x14);
    temp_a2 = *(s32 *)(arg1 + 0x1C);
    temp_a1 = *(s32 *)(arg1 + 0x10);
    if ((arg3 != 0) && (arg2 >= 0)) {
        func_002C7E60(arg2, temp_a1, temp_a2, temp_s1, arg0 + 0xD4C);
        return;
    }
    if (*(s32 *)(temp_s0 + 0x68) == 0) {
        if (*(s32 *)(arg0 + 0x36B0) == 0) {
            *(s32 *)(temp_s0 + 0x1C) = temp_a1;
            *(s32 *)(temp_s0 + 0x30) = 0;
            *(s32 *)(temp_s0 + 0x20) = 0;
            *(s32 *)(temp_s0 + 0x24) = 0;
            *(s32 *)(temp_s0 + 0x28) = 0;
            *(s32 *)(temp_s0 + 0x2C) = 0;
        }
    } else {
        if (arg3 != 0) {
            func_002C8078(temp_s0 + 0x6C, temp_s0 + 0x1C, temp_a2);
            temp_v1 = *(u16 *)(temp_s0 + 0x3A);
            *(u16 *)(temp_s0 + 0x4B2) = temp_v1;
            *(u16 *)(temp_s0 + (temp_s1 * 4) + 0x4B2) = temp_v1;
            return;
        }
        *(s32 *)(temp_s0 + 0x1C) = *(s32 *)(temp_s0 + 0x6C);
        *(s32 *)(temp_s0 + 0x30) = *(s32 *)(temp_s0 + 0x80);
        *(s32 *)(temp_s0 + 0x20) = *(s32 *)(temp_s0 + 0x70);
        *(s32 *)(temp_s0 + 0x24) = *(s32 *)(temp_s0 + 0x74);
        *(s32 *)(temp_s0 + 0x28) = *(s32 *)(temp_s0 + 0x78);
        *(s32 *)(temp_s0 + 0x2C) = *(s32 *)(temp_s0 + 0x7C);
    }
}
