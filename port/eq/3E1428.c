#include "common.h"

extern u8 *D_00427338 __attribute__((section(".data")));
extern u8 D_004279B8 __attribute__((section(".data")));

s32 func_26EB70(u8 *arg0);
void func_26EB78(u8 *arg0, u8 *arg1);
void func_26EAE0(u8 *arg0, s32 arg1);
void func_26EB08(u8 *arg0);
void func_26E9E8(u8 *arg0);

/* 0x003E1428: G = D_00427338 (pointer). If G->0xCC has bit 4: when func_26EB70(G+0x30) has bit 0 clear, call
 * func_26EB78(G+0x30, &D_004279B8) and func_26EAE0(G+0x30, 0x3C). Then if func_26EB70(G+0x30) has bit 0x200 and
 * G->0xCC bit 4 is clear, call func_26EB08(G+0x30). Finally func_26E9E8(G+0x28*j+8) for j = 0 and 1. */
void func_003E1428(void) {
    s32 s1;
    s32 j;

    if (*(s32 *)(D_00427338 + 0xCC) & 4) {
        if (!(func_26EB70(D_00427338 + 0x30) & 1)) {
            func_26EB78(D_00427338 + 0x30, &D_004279B8);
            func_26EAE0(D_00427338 + 0x30, 0x3C);
        }
    }

    s1 = 0;
    if (func_26EB70(D_00427338 + 0x30) & 0x200) {
        if (!(*(s32 *)(D_00427338 + 0xCC) & 4)) {
            func_26EB08(D_00427338 + 0x30);
            s1 = 0;
        }
    }

    for (j = 1; j >= 0; j--) {
        func_26E9E8(D_00427338 + s1 + 8);
        s1 += 0x28;
    }
}
