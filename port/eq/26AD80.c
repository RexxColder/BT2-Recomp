#include "common.h"

void func_00269A40(void *a0, s32 a1, s32 a2);

void func_0026AD80(void *arg0, s32 arg2) {
    s32 frame[22];
    u8 *fb;
    u8 *p;
    u8 *s0;
    u8 *s2;
    u8 *temp_a3;
    u8 *temp_a0_2;
    s32 s1;
    s32 s3;
    s32 a1;
    s32 a2;
    s32 t0;
    s32 temp_a0;
    s32 temp_a0_3;
    s32 temp_v1;
    s32 do18;

    fb = (u8 *)frame;
    s1 = 0;
    s3 = 0;
    s2 = (u8 *)arg0 + 0x12E0;
    a2 = arg2;
    s0 = *(u8 **)((u8 *)arg0 + 0x48);
    *(s32 *)(s2 + 0x200) = 0;

    a1 = 7;
    p = s2;
    do {
        a1 -= 1;
        *(s8 *)(p + 0x20) = -1;
        *(s32 *)(p + 0x0) = 0;
        *(s32 *)(p + 0x4) = 0;
        *(s32 *)(p + 0x8) = 0;
        *(f32 *)(p + 0xC) = 1.0f;
        *(s32 *)(p + 0x10) = 0;
        *(s32 *)(p + 0x14) = 0;
        *(s32 *)(p + 0x18) = 0;
        *(f32 *)(p + 0x1C) = 1.0f;
        p += 0x40;
    } while (a1 >= 0);
    *(s32 *)(fb + 0x20) = -1;

    for (;;) {
        s3 += 1;
        func_00269A40(arg0, *(u16 *)(s0 + 0xA), a2);
        a2 = s3 * 4;
        temp_a0 = *(u16 *)(s0 + 0xA);
        t0 = -1;
        *(s32 *)(fb + 0x20 + s3 * 4) = temp_a0;
        if (temp_a0 >= 0x47) {
            temp_a3 = *(u8 **)((u8 *)arg0 + 0x95C);
            a1 = 0;
            if (temp_a3[0x234] == temp_a0) {
                t0 = 0;
            } else {
                a1 = 1;
                while (a1 < 8) {
                    if (temp_a3[0x234 + a1] == *(s32 *)(fb + 0x20 + s3 * 4)) {
                        t0 = a1;
                        break;
                    }
                    a1 += 1;
                }
            }
        }

        do18 = 1;
        if (t0 >= 0) {
            a2 = *(u8 *)(fb + 0x20 + s3 * 4 - 4);
            temp_v1 = s1 * 4;
            temp_a0_2 = s2 + ((*(s32 *)(s2 + 0x200)) << 6);
            *(s8 *)(temp_a0_2 + 0x20) = t0;
            *(u8 *)(temp_a0_2 + 0x21) = *(u8 *)(fb + 0x20 + s3 * 4);
            *(u8 *)(temp_a0_2 + 0x22) = a2;
            *(u8 **)(fb + temp_v1) = temp_a0_2;
            *(s8 *)(temp_a0_2 + 0x23) = s1;
            if (s1 > 0) {
                *(s32 *)(temp_a0_2 + 0x24) = *(s32 *)(fb + temp_v1 - 4);
            } else {
                *(s32 *)(temp_a0_2 + 0x24) = 0;
            }
            *(s32 *)(s2 + 0x200) = *(s32 *)(s2 + 0x200) + 1;
            temp_a0_3 = *(u16 *)(s0 + 0x4);
            s1 += 1;
            if (temp_a0_3 != 0) {
                s1 = s1 - (temp_a0_3 & 0xFFFF);
                if (s1 < 0) {
                    s1 = 0;
                }
            } else {
                do18 = 0;
            }
        }
        if (do18) {
            if (*(u16 *)(s0 + 0x4) != 0) {
                s3 -= *(u16 *)(s0 + 0x4);
            }
        }
        if (*(u16 *)(s0 + 0x6) == 0) {
            s0 = s0 + *(s32 *)s0;
            continue;
        }
        break;
    }
}
