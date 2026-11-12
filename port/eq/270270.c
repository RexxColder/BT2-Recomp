#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
s32 strcmp(u8 *arg0, u8 *arg1);

void func_00270270(u8 *arg0, u8 *arg1, u8 *arg2) {
    u8 *s2;
    u8 *cur;
    s32 s1 = 0;
    s32 s4 = 0;

    memset(arg2, 0, 8);
    s2 = *(u8 **)arg0;
    if (*(u32 *)(arg0 + 4) != 0) {
        do {
            cur = s2;
            s2 += 0xC0;
            if (strcmp(cur, arg1) == 0) {
                if (s4 == 0) {
                    *(u32 *)arg2 = s1;
                    s4 = 1;
                } else {
                    *(s32 *)(arg2 + 4) = *(s32 *)(arg2 + 4) + 1;
                }
            }
            s1 += 1;
        } while ((u32)s1 < *(u32 *)(arg0 + 4));
    }
    if (s4 == 0) {
        *(s32 *)(arg2 + 4) = 0;
        *(u32 *)arg2 = -1U;
    }
}
