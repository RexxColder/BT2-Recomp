#include "common.h"

void func_00134758(u8 *arg0) {
    s32 temp_v1;
    s32 p;
    s32 v0;
    s32 a2;
    s32 a2_2;
    u8 *a1;

    temp_v1 = *(s32 *)(arg0 + 4);
    if (*(s32 *)(arg0 + 0x14) != 1) {
        p = (s32)arg0;
        *(s32 *)(arg0 + 0x14) = 1;
        v0 = *(s32 *)(arg0 + 8) + p;
        *(s32 *)(arg0 + 8) = v0;
        a1 = (u8 *)v0;
        if (temp_v1 > 0) {
            a2 = temp_v1;
            do {
                a2 -= 1;
                *(s32 *)(a1 + 8) = *(s32 *)(a1 + 8) + p;
                *(s32 *)(a1 + 0xC) = *(s32 *)(a1 + 0xC) + p;
                a1 += 0x18;
            } while (a2 != 0);
        }
        a2_2 = 0;
        v0 = *(s32 *)(arg0 + 0x10) + p;
        *(s32 *)(arg0 + 0x10) = v0;
        a1 = (u8 *)v0;
        if (*(s32 *)(arg0 + 0xC) > 0) {
            do {
                a2_2 += 1;
                *(s32 *)(a1 + 0x38) = *(s32 *)(a1 + 0) + p;
                *(s32 *)(a1 + 0x3C) = *(s32 *)(a1 + 4) + p;
                a1 += 0x40;
            } while (a2_2 < *(s32 *)(arg0 + 0xC));
        }
    }
}
