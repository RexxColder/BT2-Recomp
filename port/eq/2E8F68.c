#include "common.h"

s32 func_002F8E20(s32 arg0);

void func_002E8F68(u8 *arg0) {
    u8 *temp_s1;
    u8 *temp_s2;
    u8 *var_a3;
    s32 state;
    s32 a3;
    s32 t0;
    s32 t1;
    s32 t1_2;
    s32 t1_3;
    s32 t2;
    s32 t3;

    temp_s1 = arg0 + 0x48;
    temp_s2 = *(u8 **)(arg0 + 0x48);
    state = *(s32 *)(arg0 + 4);
    if (state == 1) {
        if (func_002F8E20(*(s32 *)(arg0 + 8)) != 0) {
            state = *(s32 *)(arg0 + 4);
        } else {
            ((void (*)(s32, void *, void *, void *))(*(s32 *)(arg0 + 0x78)))(*(s32 *)(arg0 + 0x7C), arg0 + 0x68,
                                                                              arg0 + 0x6C, arg0 + 0x70);
            a3 = *(s32 *)(temp_s1 + 0x20);
            t1 = *(s32 *)(temp_s1 + 0x18) - a3;
            t1_2 = (*(s32 *)(temp_s1 + 0x24) < t1) ? *(s32 *)(temp_s1 + 0x24) : t1;
            t1_3 = (*(s32 *)(temp_s1 + 4) < t1_2) ? *(s32 *)(temp_s1 + 4) : t1_2;
            t2 = *(s32 *)(temp_s1 + 0x14);
            t3 = t2 + (a3 * 2);
            if (*(s8 *)(arg0 + 0xE) == 2) {
                t0 = 0;
                if (t1_3 > 0) {
                    var_a3 = temp_s2;
                    do {
                        s32 a0v = t0 * 2;
                        u8 *a1p = (u8 *)(t3 + a0v);
                        u8 *a0p = (u8 *)(t2 + ((*(s32 *)(temp_s1 + 0x1C) + a3) * 2) + a0v);
                        t0 += 1;
                        *(s16 *)a1p = (s16)((var_a3[0] + 0xFF80) << 8);
                        *(s16 *)a0p = (s16)((var_a3[1] + 0xFF80) << 8);
                        var_a3 += 2;
                    } while (t0 < t1_3);
                }
            } else {
                t0 = 0;
                if (t1_3 > 0) {
                    u8 *a1p = (u8 *)t3;
                    do {
                        u8 b = temp_s2[t0];
                        t0 += 1;
                        *(s16 *)a1p = (s16)((b + 0xFF80) << 8);
                        a1p += 2;
                    } while (t0 < t1_3);
                }
            }
            state = 2;
            *(s32 *)(arg0 + 4) = 2;
            *(s32 *)(arg0 + 0x90) = t1_3;
            *(s32 *)(arg0 + 0x94) = t1_3 * (s32)*(s8 *)(arg0 + 0xE);
        }
    }
    if (state == 2) {
        ((void (*)(s32, s32, s32))(*(s32 *)(arg0 + 0x80)))(*(s32 *)(arg0 + 0x84), *(s32 *)(arg0 + 0x94),
                                                           *(s32 *)(arg0 + 0x90));
        *(s32 *)(arg0 + 4) = 3;
    }
}
