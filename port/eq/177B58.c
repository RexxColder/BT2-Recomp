#include "common.h"

s32 EftSpdLine_StepStreak(void *a0);
extern u8 *D_00387E94;
extern u8 *D_003876A0;

void func_00177B58(void) {
    u8 *s0;
    u8 *s1;
    u8 *prev;
    u8 *next;
    s32 r;

    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x100) != 0) {
        return;
    }
    s1 = *(u8 **)(D_00387E94 + 0x3F5C);
    while (s1 != NULL) {
        s0 = s1;
        r = EftSpdLine_StepStreak(s0);
        s1 = *(u8 **)(s0 + 0x50);
        if (r != 0) {
            *(s32 *)(s0 + 0x44) = 0;
            prev = *(u8 **)(s0 + 0x4C);
            if (prev != NULL) {
                *(u8 **)(prev + 0x50) = *(u8 **)(s0 + 0x50);
            } else {
                *(u8 **)(D_00387E94 + 0x3F5C) = s1;
            }
            next = *(u8 **)(s0 + 0x50);
            if (next != NULL) {
                *(u8 **)(next + 0x4C) = prev;
            } else {
                *(u8 **)(D_00387E94 + 0x3F60) = prev;
            }
            *(u8 **)(s0 + 0x50) = NULL;
            *(u8 **)(s0 + 0x4C) = NULL;
            *(s32 *)(D_00387E94 + 0x3D44) = *(s32 *)(D_00387E94 + 0x3D44) - 1;
        }
    }
}
