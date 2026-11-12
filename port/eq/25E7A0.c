#include "common.h"

void func_00269A40(s32 arg0, s32 arg1);
extern f32 D_00386E7C;
extern u8 *D_00387A40;

void func_0025E7A0(s32 arg0, s32 arg1) {
    u8 *p = (u8 *)arg0;
    u8 *s1;
    f32 f20;
    u16 s0;
    u16 v1;
    s32 a2;
    s32 a1;
    u8 *temp_v0;
    u8 *a0p;

    s1 = *(u8 **)(p + 0x48);
    f20 = *(f32 *)(*(u8 **)(p + 0x958) + 0x40) / D_00386E7C;
    while (1) {
        s0 = *(u16 *)(s1 + 0xA);
        if (s0 < 0x47) {
            func_00269A40(arg0, s0);
            v1 = *(u16 *)((u8 *)arg1 + 6 + s0 * 2);
            if (v1 != 0) {
                temp_v0 = (u8 *)arg1 + v1 * 4;
                if (!(*(u16 *)temp_v0 & 1)) {
                    a2 = *(u16 *)(temp_v0 + 2);
                    if (a2 != 0) {
                        a0p = temp_v0 + 4;
                        a1 = s0 * 0xC;
                        do {
                            u8 *base = *(u8 **)(D_00387A40 + 0x38208);
                            f32 x;
                            f32 y;
                            f32 y2;
                            f32 z;

                            a2 -= 1;
                            x = *(f32 *)(a0p + 0) - *(f32 *)(base + a1 + 0);
                            *(f32 *)(a0p + 0) = x;
                            y = *(f32 *)(a0p + 4) - *(f32 *)(base + a1 + 4);
                            *(f32 *)(a0p + 4) = y;
                            y2 = y * f20;
                            *(f32 *)(a0p + 4) = y2;
                            z = *(f32 *)(a0p + 8) - *(f32 *)(base + a1 + 8);
                            *(f32 *)(a0p + 8) = z;
                            *(f32 *)(a0p + 0) = x + *(f32 *)(s1 + 0x30);
                            *(f32 *)(a0p + 4) = y2 + *(f32 *)(s1 + 0x34);
                            *(f32 *)(a0p + 8) = z + *(f32 *)(s1 + 0x38);
                            a0p += 0x18;
                        } while (a2 != 0);
                    }
                }
            }
        }
        if (*(u16 *)(s1 + 6) != 0) {
            return;
        }
        s1 += *(s32 *)s1;
    }
}
