#include "common.h"

extern u8 *D_0042311C __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));
extern s32 D_003B0C34 __attribute__((section(".data")));
extern u8 D_00424E78[] __attribute__((section(".data")));

s32 func_26EB60(u8 *arg0);
void func_26EB78(u8 *arg0, u8 *arg1);
void func_2493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x003CEDD0: if func_26EB60(G+0x8C) != 0 and (*0x3B0C34 & 0x4000) (G = D_0042311C): with t = G->0x118:
 * if (t & 0x10) { G->0x118 = t ^ 0x10; G->0x118 |= 0x40; v = 0xD, or 0xB/0xC by *(s16*)(*0x387F2C + 0x424) < 4
 * unless G->0x118 & 0x20; G->0x11C = v; func_26EB78(G+0x8C, &D_00424E78); func_2493C0(G->8, 0x342E, 0x3847, 0, G->0x11C); }
 * else if (t & 0xC) G->0x150 = 8; else { G->0x118 = t | 1 | 2; G->0x124 = 0xF; }
 * Then func_297FE0(0, 1, 0x40, 0x40, 1). */
void func_003CEDD0(void) {
    s32 t;
    s32 v;

    if (func_26EB60(D_0042311C + 0x8C) != 0 && (D_003B0C34 & 0x4000)) {
        t = *(s32 *)(D_0042311C + 0x118);
        if (t & 0x10) {
            *(s32 *)(D_0042311C + 0x118) = t ^ 0x10;
            *(s32 *)(D_0042311C + 0x118) = *(s32 *)(D_0042311C + 0x118) | 0x40;
            v = 0xD;
            if (!(*(s32 *)(D_0042311C + 0x118) & 0x20)) {
                if (*(s16 *)(D_00387F2C + 0x424) < 4) {
                    v = 0xB;
                } else {
                    v = 0xC;
                }
            }
            *(s32 *)(D_0042311C + 0x11C) = v;
            func_26EB78(D_0042311C + 0x8C, D_00424E78);
            func_2493C0(*(s32 *)(D_0042311C + 0x8), 0x342E, 0x3847, 0, *(s32 *)(D_0042311C + 0x11C));
        } else if (t & 0xC) {
            *(s32 *)(D_0042311C + 0x150) = 8;
        } else {
            *(s32 *)(D_0042311C + 0x118) = t | 1;
            *(s32 *)(D_0042311C + 0x118) = *(s32 *)(D_0042311C + 0x118) | 2;
            *(s32 *)(D_0042311C + 0x124) = 0xF;
        }
        func_297FE0(0, 1, 0x40, 0x40, 1);
    }
}
