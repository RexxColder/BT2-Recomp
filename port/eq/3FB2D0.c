#include "common.h"

extern u8 *D_0042A584 __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));

s32 func_26EB60(u8 *arg0);
void func_297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x003FB2D0 (G = D_0042A584, C = D_003B0B00, cnt = G + 4*G->0x110 + 0x114). If func_26EB60(G+0x3C) == 0 return.
 * v1 = C->0x144: if 0x10: if *cnt > 0 { *cnt -= 1; func_297FE0(0,0,0x40,0x40,1) } else *cnt = 0.
 * else if 0x40: if *cnt + 5 < 0xF { *cnt += 1; func_297FE0(0,0,..) } else *cnt = 0xA.
 * else if 0x20: G->0x110 += 1, if < 3 keep else 0; func_297FE0(0,0,..).
 * else if 0x80: G->0x110 -= 1, if < 0 then 2; func_297FE0(0,0,..).
 * else if C->0x134 & 0x1000: G->0x124 |= 1, *arg0 = 0, func_297FE0(0,2,0x40,0x40,1). */
void func_003FB2D0(s32 *arg0) {
    u8 *cp;
    s32 v1;
    s32 c;

    if (func_26EB60(D_0042A584 + 0x3C) == 0) {
        return;
    }
    v1 = *(s32 *)(D_003B0B00 + 0x144);
    cp = D_0042A584 + ((u32)*(s32 *)(D_0042A584 + 0x110) << 2) + 0x114;

    if (v1 & 0x10) {
        c = *(s32 *)cp;
        if (c > 0) {
            *(s32 *)cp = c - 1;
            func_297FE0(0, 0, 0x40, 0x40, 1);
        } else {
            *(s32 *)cp = 0;
        }
    } else if (v1 & 0x40) {
        c = *(s32 *)cp;
        if (c + 5 < 0xF) {
            *(s32 *)cp = c + 1;
            func_297FE0(0, 0, 0x40, 0x40, 1);
        } else {
            *(s32 *)cp = 0xA;
        }
    } else if (v1 & 0x20) {
        *(s32 *)(D_0042A584 + 0x110) = *(s32 *)(D_0042A584 + 0x110) + 1;
        if (*(s32 *)(D_0042A584 + 0x110) >= 3) {
            *(s32 *)(D_0042A584 + 0x110) = 0;
        }
        func_297FE0(0, 0, 0x40, 0x40, 1);
    } else if (v1 & 0x80) {
        *(s32 *)(D_0042A584 + 0x110) = *(s32 *)(D_0042A584 + 0x110) - 1;
        if (*(s32 *)(D_0042A584 + 0x110) < 0) {
            *(s32 *)(D_0042A584 + 0x110) = 2;
        }
        func_297FE0(0, 0, 0x40, 0x40, 1);
    } else if (*(s32 *)(D_003B0B00 + 0x134) & 0x1000) {
        *(s32 *)(D_0042A584 + 0x124) = *(s32 *)(D_0042A584 + 0x124) | 0x1;
        *arg0 = 0;
        func_297FE0(0, 2, 0x40, 0x40, 1);
    }
}
