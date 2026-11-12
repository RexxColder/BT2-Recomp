#include "common.h"

s32 EftWaterRing_Update(s32 arg0);
extern u8 *D_003876A0;
extern u8 *gEftDust;

void EftWaterRing_UpdateList(s32 arg0, s32 arg1) {
    s32 s0;
    s32 s1;
    s32 a0;
    s32 v1;
    s32 v0;

    if (*(s32 *)(gEftDust + 0x30) == 0) {
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
        s1 = *(s32 *)(s0 + 0x44);
        if (EftWaterRing_Update(a0) != 0) {
            v1 = *(s32 *)(s0 + 0x40);
            *(s32 *)(s0 + 0x3C) = 0;
            if (v1 == 0) {
                *(s32 *)arg0 = s1;
            } else {
                *(s32 *)(v1 + 0x44) = *(s32 *)(s0 + 0x44);
            }
            v1 = *(s32 *)(s0 + 0x44);
            v0 = *(s32 *)(s0 + 0x40);
            if (v1 == 0) {
                *(s32 *)arg1 = v0;
            } else {
                *(s32 *)(v1 + 0x40) = v0;
            }
            *(s32 *)(s0 + 0x44) = 0;
            *(s32 *)(s0 + 0x40) = 0;
            *(s32 *)(gEftDust + 0x30) = *(s32 *)(gEftDust + 0x30) - 1;
        }
        a0 = s1;
    } while (s1 != 0);
}
