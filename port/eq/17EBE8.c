#include "common.h"

void EftBolt_FreeSegs(u8 *arg0);
s32 EftBolt_Step(f32 arg0, u8 *arg1);
void func_00208DE8(s32 arg0, u8 *arg1, s32 arg2);
void func_00312650(u8 *arg0, u8 *arg1, u8 *arg2);
s32 rand(void);

void func_0017EBE8(u8 *arg0, s32 arg1) {
    f32 vec[4];
    u8 *s1;
    u8 *s0;
    u8 *s2;
    s32 s5;
    s32 take;
    s32 v1;
    s32 a0;
    s32 n;
    f32 f0;

    s1 = arg0;
    s5 = 9;
    do {
        if (*(s32 *)(s1 + 0x1C) & 1) {
            s0 = s1 + 0x40;
            s2 = s1 + 0x10;
            if ((*(s32 *)(s1 + 0x1C) & 4) == 0) {
                func_00208DE8(arg1, s0, *(s32 *)(s1 + 0x24));
                func_00208DE8(arg1, (u8 *)vec, *(s32 *)(s1 + 0x28));
                func_00312650((u8 *)vec, (u8 *)vec, s0);
                f0 = *(f32 *)(s1 + 0x30);
                *(f32 *)(s1 + 0x40) = *(f32 *)(s1 + 0x40) + vec[0] * f0;
                *(f32 *)(s1 + 0x44) = *(f32 *)(s1 + 0x44) + vec[1] * f0;
                *(f32 *)(s1 + 0x48) = *(f32 *)(s1 + 0x48) + vec[2] * f0;
                if (EftBolt_Step(*(f32 *)(arg0 + 0xEA0), s2) != 0) {
                    *(s32 *)(s1 + 0x1C) = *(s32 *)(s1 + 0x1C) | 4;
                }
                take = 0;
                if ((*(s32 *)(s1 + 0x1C) & 2) != 0) {
                    take = 1;
                } else {
                    v1 = *(s32 *)(s1 + 0x14);
                    a0 = *(s32 *)(s1 + 0x18);
                    if (v1 < a0) {
                        n = v1 + a0;
                        *(s32 *)(s1 + 0x14) = n;
                        if (n >= a0) {
                            *(s32 *)(s1 + 0x14) = a0;
                            *(s32 *)(s1 + 0x1C) = *(s32 *)(s1 + 0x1C) | 2;
                            take = 1;
                        }
                    }
                }
                if (take != 0) {
                    if (*(s32 *)(s1 + 0x14) > 0) {
                        a0 = (*(s32 *)(s1 + 0x14) - (rand() % 2)) - 2;
                        *(s32 *)(s1 + 0x14) = (a0 < 0) ? 0 : a0;
                    }
                }
                f0 = *(f32 *)(s1 + 0x2C) - 1.0f;
                *(f32 *)(s1 + 0x2C) = f0;
                if (f0 <= 0.0f) {
                    *(s32 *)(s1 + 0x1C) = *(s32 *)(s1 + 0x1C) | 4;
                }
            } else {
                EftBolt_FreeSegs(s2);
                *(s32 *)(s1 + 0x1C) = 0;
                *(s32 *)(arg0 + 0xE78) = *(s32 *)(arg0 + 0xE78) - 1;
            }
        }
        s5 -= 1;
        s1 += 0x90;
    } while (s5 >= 0);
}
