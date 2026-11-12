#include "common.h"

s32 func_001304E0(s32 arg0);
extern u8 *D_003876A0;
extern u8 *gEftBubble;

void EftBubble_UpdateList(s32 arg0, s32 arg1) {
    s32 s0;
    s32 s1;
    s32 a0;
    s32 v1;
    s32 v0;

    if (*(s32 *)(gEftBubble + 0x10) == 0) {
        return;
    }
    if (*(s64 *)(D_003876A0 + 0x4D8) & 0x100) {
        return;
    }
    s1 = *(s32 *)arg0;
    if (s1 == 0) {
        return;
    }
    a0 = s1;
    do {
        s0 = s1;
        s1 = *(s32 *)(s0 + 0x5C);
        if (func_001304E0(a0) != 0) {
            v1 = *(s32 *)(s0 + 0x58);
            *(s8 *)(s0 + 0x55) = 0;
            if (v1 == 0) {
                *(s32 *)arg0 = s1;
            } else {
                *(s32 *)(v1 + 0x5C) = *(s32 *)(s0 + 0x5C);
            }
            v1 = *(s32 *)(s0 + 0x5C);
            v0 = *(s32 *)(s0 + 0x58);
            if (v1 == 0) {
                *(s32 *)arg1 = v0;
            } else {
                *(s32 *)(v1 + 0x58) = v0;
            }
            *(s32 *)(s0 + 0x5C) = 0;
            *(s32 *)(s0 + 0x58) = 0;
            *(s32 *)(gEftBubble + 0x10) = *(s32 *)(gEftBubble + 0x10) - 1;
        }
        a0 = s1;
    } while (s1 != 0);
}
