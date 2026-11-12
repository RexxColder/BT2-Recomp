#include "common.h"

extern s8 D_003534B0[] __attribute__((section(".data")));
extern u8 func_002F07B8[] __attribute__((section(".data")));

void *func_002E7418(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002E7A90(void *arg0, void *arg1, void *arg2);
void func_002F0178(void *arg0);
s32 func_00305360(s32 arg0, s32 arg1);
u32 func_00305368(s32 arg0);
u32 func_00305370(s32 arg0);

void *func_002F01B8(s32 arg0, s32 arg1, s32 *arg2) {
    s32 orig = *arg2;
    s32 a0i = 0;
    s8 *v1 = D_003534B0;
    u8 *s2;
    s32 s1, t, u, s0r, r, i;
    void *v0 = NULL;

    if (D_003534B0[0] != 0) {
        a0i = 1;
        for (;;) {
            if (!(a0i < 0x10)) {
                break;
            }
            v1 += 0xAC;
            if (*v1 == 0) {
                break;
            }
            a0i++;
        }
    }
    if (a0i != 0x10) {
        s2 = (u8 *)D_003534B0 + a0i * 0xAC;
        s1 = func_00305360(orig, arg1);
        t = (s32)func_00305368(orig);
        s0r = ((s32)((u32)t >> 31) + t) >> 1;
        u = (s32)func_00305370(orig);
        r = s0r + (((s32)((u32)u >> 31) + u) >> 1);
        v0 = func_002E7418(arg1, s1, s0r, r);
        *(void **)(s2 + 4) = v0;
        if (v0 != NULL) {
            func_002E7A90(v0, func_002F07B8, s2);
            *(s32 *)(s2 + 8) = arg0;
            s2[2] = (u8)arg1;
            for (i = 0; i < arg1; i++) {
                *(s32 *)(s2 + 0xC + 4 * i) = arg2[i];
            }
            s2[1] = 0;
            func_002F0178(s2);
            *(s32 *)(s2 + 0x48) = 0;
            *(s32 *)(s2 + 0x4C) = 0;
            *(s32 *)(s2 + 0x50) = 0;
            *(s32 *)(s2 + 0x54) = 0;
            s2[0] = 1;
            v0 = s2;
        }
    }
    return v0;
}
