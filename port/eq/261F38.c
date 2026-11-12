#include "common.h"

extern u8 *D_00388D4C __attribute__((section(".data")));
extern u8 D_00388A48[] __attribute__((section(".data")));

s32 func_00100ED0(s32 a0, s32 a1, s32 a2);
void func_0028BB60(s32 a0);
void *memset(void *arg0, s32 arg1, u32 arg2);

/* 0x00261F38: fills one 48-byte slot (index arg2 & 0xFFFF) of a table. arg1 & 0xFF == 1 selects
 * the table at D_00388D4C with plain stores; otherwise D_00388A48 is cleared, then refilled.
 * Each filled field goes through func_00100ED0 (flag = arg0 & 0xFF until a call clears it). */
void func_00261F38(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 s1;
    s32 idx;
    u8 *s0;

    s1 = arg0 & 0xFF;
    idx = arg2 & 0xFFFF;

    if ((arg1 & 0xFF) == 1) {
        s0 = D_00388D4C + idx * 48;
        *(s32 *)(s0 + 0x10) = arg4;
        *(s32 *)(s0 + 0x14) = arg5;
        *(s32 *)(s0 + 0xC) = arg3;
        if (arg3 >= 0) {
            *(s32 *)(s0 + 0x24) = func_00100ED0(arg3, *(s32 *)(s0 + 0x24), s1 != 0);
            s1 = 0;
        }
        if (*(s32 *)(s0 + 0x10) >= 0) {
            *(s32 *)(s0 + 0x28) = func_00100ED0(*(s32 *)(s0 + 0x10), *(s32 *)(s0 + 0x28), s1 != 0);
            s1 = 0;
        }
        if (*(s32 *)(s0 + 0x14) >= 0) {
            *(s32 *)(s0 + 0x2C) = func_00100ED0(*(s32 *)(s0 + 0x14), *(s32 *)(s0 + 0x2C), s1 != 0);
        }
        return;
    }

    s0 = D_00388A48 + idx * 48;
    if (*(s32 *)(s0 + 0xC) >= 0 && *(s32 *)(s0 + 0x24) != 0) {
        func_0028BB60(*(s32 *)(s0 + 0x24));
        *(s32 *)(s0 + 0x24) = 0;
    }
    if (*(s32 *)(s0 + 0x10) >= 0 && *(s32 *)(s0 + 0x28) != 0) {
        func_0028BB60(*(s32 *)(s0 + 0x28));
        *(s32 *)(s0 + 0x28) = 0;
    }
    if (*(s32 *)(s0 + 0x14) >= 0 && *(s32 *)(s0 + 0x2C) != 0) {
        func_0028BB60(*(s32 *)(s0 + 0x2C));
        *(s32 *)(s0 + 0x2C) = 0;
    }
    memset(s0, 0, 0x30);
    *(s32 *)(s0 + 0xC) = arg3;
    *(s32 *)(s0 + 0x10) = arg4;
    *(s32 *)(s0 + 0x14) = arg5;
    *(s32 *)s0 = *(s32 *)s0 | 1;

    if (arg3 >= 0) {
        *(s32 *)(s0 + 0x24) = func_00100ED0(arg3, 0, s1 != 0);
        s1 = 0;
    }
    if (*(s32 *)(s0 + 0x10) >= 0) {
        *(s32 *)(s0 + 0x28) = func_00100ED0(*(s32 *)(s0 + 0x10), 0, s1 != 0);
        s1 = 0;
    }
    if (*(s32 *)(s0 + 0x14) >= 0) {
        *(s32 *)(s0 + 0x2C) = func_00100ED0(*(s32 *)(s0 + 0x14), 0, s1 != 0);
    }
}
