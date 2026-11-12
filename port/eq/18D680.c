#include "common.h"

void func_0018CBC8(void *a0, s32 a1, s32 a2, void *a3, void *t0, void *t1, s32 t2, void *t3, s32 s9, s32 s10);
void func_0018D730(void *a0, void *a1, void *a2);
extern u8 *D_003877B8;

s32 func_0018D680(void *arg0) {
    s32 cnt;
    u8 *s1;
    u8 *s0;

    s0 = (u8 *)arg0;
    cnt = 0;
    s1 = D_003877B8;
    for (;;) {
        cnt += 1;
        if (*(s32 *)(s1 + 0xEC) == 0) {
            *(s32 *)(s1 + 0xEC) = 1;
            func_0018CBC8(s1, *(s32 *)(s0 + 4), *(s32 *)(s0 + 8), s0 + 0x10, s0 + 0x20, s0 + 0x44,
                          *(u8 *)(s0 + 0x4C), s0 + 0x4D, *(u8 *)(s0 + 0x4E),
                          (*(u16 *)(s0 + 0x56) >> 10) & 1);
            func_0018D730(s0 + 0x158, s0 + 0x15C, s1);
            return 1;
        }
        s1 += 0x100;
        if (cnt >= 0x96) {
            return 0;
        }
    }
}
