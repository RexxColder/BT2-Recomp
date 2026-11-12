#include "common.h"

s32 func_002F8E20(s32 arg0);

void func_002E8920(u8 *arg0) {
    u8 *p = arg0 + 0x48;
    u8 *s2 = *(u8 **)(arg0 + 0x48);
    s32 var_v1 = *(s32 *)(arg0 + 4);
    s32 a3;
    s32 v1;
    s32 t1;
    s32 a1;
    u8 *t2;
    u8 *t3;
    s32 t0;
    s32 off;
    u16 v0;
    s32 byte;

    if (var_v1 == 1) {
        if (func_002F8E20(*(s32 *)(arg0 + 8)) != 0) {
            var_v1 = *(s32 *)(arg0 + 4);
        } else {
            ((void (*)(s32, s32, s32, s32))(*(u32 *)(arg0 + 0x78)))(*(s32 *)(arg0 + 0x7C),
                (s32)(arg0 + 0x68), (s32)(arg0 + 0x6C), (s32)(arg0 + 0x70));
            a3 = *(s32 *)(p + 0x20);
            t1 = *(s32 *)(p + 0x18) - a3;
            v1 = *(s32 *)(p + 0x24);
            a1 = *(s32 *)(p + 4);
            t1 = (v1 < t1) ? v1 : t1;
            t3 = *(u8 **)(p + 0x14);
            t1 = (a1 < t1) ? a1 : t1;
            t2 = t3 + a3 * 2;
            byte = *(s8 *)(arg0 + 0xE);
            if (byte == 2) {
                t0 = 0;
                if (t1 > 0) {
                    u8 *src = s2;
                    t3 = t3 + (*(s32 *)(p + 0x1C) + a3) * 2;
                    do {
                        off = t0 * 2;
                        t0 += 1;
                        *(u16 *)(t2 + off) = *(u16 *)(src + 0);
                        v0 = *(u16 *)(src + 2);
                        src += 4;
                        *(u16 *)(t3 + off) = v0;
                    } while (t0 < t1);
                } else {
                    t3 = t3 + (*(s32 *)(p + 0x1C) + a3) * 2;
                }
            } else {
                t0 = 0;
                if (t1 > 0) {
                    do {
                        off = t0 * 2;
                        t0 += 1;
                        *(u16 *)(t2 + off) = *(u16 *)(s2 + off);
                    } while (t0 < t1);
                }
            }
            var_v1 = 2;
            *(s32 *)(arg0 + 4) = 2;
            *(s32 *)(arg0 + 0x90) = t1;
            *(s32 *)(arg0 + 0x94) = t1 * byte * 2;
        }
    }
    if (var_v1 == 2) {
        ((void (*)(s32, s32, s32))(*(u32 *)(arg0 + 0x80)))(*(s32 *)(arg0 + 0x84), *(s32 *)(arg0 + 0x94),
            *(s32 *)(arg0 + 0x90));
        *(s32 *)(arg0 + 4) = 3;
    }
}
