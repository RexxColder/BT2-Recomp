#include "common.h"

s32 EftWaterSpray_Update(s32 arg0);
extern u8 *D_003876A0;
extern u8 *gEftDust;

void EftWaterSpray_UpdateList(s32 arg0, s32 arg1) {
    s32 s0;
    s32 s1;
    s32 a0;
    s32 v1;
    s32 v0;

    if (*(s32 *)(gEftDust + 0x34) == 0) {
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
        s1 = *(s32 *)(s0 + 0x8C);
        if (EftWaterSpray_Update(a0) != 0) {
            v1 = *(s32 *)(s0 + 0x88);
            *(s32 *)(s0 + 0x84) = 0;
            if (v1 == 0) {
                *(s32 *)arg0 = s1;
            } else {
                *(s32 *)(v1 + 0x8C) = *(s32 *)(s0 + 0x8C);
            }
            v1 = *(s32 *)(s0 + 0x8C);
            v0 = *(s32 *)(s0 + 0x88);
            if (v1 == 0) {
                *(s32 *)arg1 = v0;
            } else {
                *(s32 *)(v1 + 0x88) = v0;
            }
            *(s32 *)(s0 + 0x8C) = 0;
            *(s32 *)(s0 + 0x88) = 0;
            *(s32 *)(gEftDust + 0x34) = *(s32 *)(gEftDust + 0x34) - 1;
        }
        a0 = s1;
    } while (s1 != 0);
}
