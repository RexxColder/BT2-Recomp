#include "common.h"

s32 EftSpdLine_StepTrail(void *a0);
extern u8 *D_00387E94;
extern u8 *D_003876A0;

void func_00177700(void) {
    u8 *s0;
    u8 *s1;
    u8 *prev;
    u8 *next;
    s32 r;

    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x100) != 0) {
        return;
    }
    s1 = *(u8 **)(D_00387E94 + 0x3F54);
    while (s1 != NULL) {
        s0 = s1;
        r = EftSpdLine_StepTrail(s0);
        s1 = *(u8 **)(s0 + 0x4C);
        if (r != 0) {
            *(s32 *)(s0 + 0x40) = 0;
            prev = *(u8 **)(s0 + 0x48);
            if (prev != NULL) {
                *(u8 **)(prev + 0x4C) = *(u8 **)(s0 + 0x4C);
            } else {
                *(u8 **)(D_00387E94 + 0x3F54) = s1;
            }
            next = *(u8 **)(s0 + 0x4C);
            if (next != NULL) {
                *(u8 **)(next + 0x48) = prev;
            } else {
                *(u8 **)(D_00387E94 + 0x3F58) = prev;
            }
            *(u8 **)(s0 + 0x4C) = NULL;
            *(u8 **)(s0 + 0x48) = NULL;
            *(s32 *)(D_00387E94 + 0x3D40) = *(s32 *)(D_00387E94 + 0x3D40) - 1;
        }
    }
}
