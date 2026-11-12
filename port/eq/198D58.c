#include "common.h"

s32 EftAura_IsVisible(s32 arg0);
void EftAura_CommandAlt(s32 arg0, s32 arg1);
void EftGlow_Emit(s32 arg0, s32 arg1);
void EftGlow_UpdateFrames(s32 arg0, s32 arg1);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
extern u8 *gEftGlowCfg;

void func_00198D58(u8 *arg0, s32 arg1) {
    s32 s3;
    s32 s2;
    u8 *s0;
    s32 v1;
    f32 f;

    if (!(*(s32 *)arg0 & 2) && (EftAura_IsVisible(arg1) == 0)) {
        EftAura_CommandAlt(arg1, 0);
    }
    s3 = 0x490;
    s0 = arg0 + 0x1B0;
    s2 = 9;
    do {
        s2 -= 1;
        func_00208DE8(arg1, (s32)s0, *(s32 *)(gEftGlowCfg + s3));
        s3 += 0x18;
        s0 += 0x10;
    } while (s2 >= 0);
    EftGlow_UpdateFrames((s32)arg0, arg1);
    EftGlow_Emit((s32)arg0, arg1);

    v1 = *(s32 *)(arg0 + 0x34);
    if (v1 != 0) {
        if (v1 == 1) {
            f = *(f32 *)(arg0 + 0x3C) + (1.0f / *(f32 *)(gEftGlowCfg + 0x1A8));
            *(f32 *)(arg0 + 0x3C) = f;
            if (f >= 1.0f) {
                *(f32 *)(arg0 + 0x3C) = 1.0f;
                *(s32 *)(arg0 + 0x34) = 0;
            }
        } else {
            f = *(f32 *)(arg0 + 0x3C) - (1.0f / *(f32 *)(gEftGlowCfg + 0x1AC));
            *(f32 *)(arg0 + 0x3C) = f;
            if (f <= 0.0f) {
                *(f32 *)(arg0 + 0x3C) = 0.0f;
                *(s32 *)(arg0 + 0x34) = 0;
                *(s32 *)arg0 = *(s32 *)arg0 | 4;
            }
        }
    }
}
