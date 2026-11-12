#include "common.h"

s32 Gsc_HasAction(s32 arg0, s32 arg1, s32 arg2);
s32 Gsc_StartAction(s32 arg0, s32 arg1);
void func_0029F250(void);
s32 func_0029F6F8(s32 arg0);
extern u8 *D_00387F2C;
extern u8 D_003B26B0[] __attribute__((section(".data")));

void func_002AD1F0(s32 arg0, s32 *arg1, s32 *arg2) {
    u8 *s1;
    u8 *s2;
    u8 *p;
    s32 s0;
    s32 a0;
    s32 a2;
    s32 v;

    s1 = D_003B26B0;
    s2 = s1 - 0x5C;
    s0 = arg0 + 0x7D0;
    *(s32 *)(s1 + 0x300) = 0;
    *(s32 *)(s1 + 0x304) = 0;
    *(s32 *)(s1 + 0x308) = 0;
    if (*(s32 *)(s2 + 0x3C) != 0) {
        s0 = arg0 + 0xBB8;
    }
    a2 = 1;
    a0 = 0;
    p = D_00387F2C;
    v = *(s16 *)(p + 0x24C2);
    for (;;) {
        if (v > 0) {
            a0 += 1;
            if (a0 >= 7) {
                break;
            }
            v = *(s16 *)(p + (a0 * 4) + 0x24C2);
        } else {
            a2 = 0;
            break;
        }
    }

    if (s0 == 0x7D0) {
        if (a2 != 0) {
            *(s32 *)(s1 + 0x304) = 0;
            *(s32 *)(s1 + 0x300) = 0x2E6;
        }
    } else if (s0 == 0xBB8) {
        if (a2 != 0) {
            *(s32 *)(s1 + 0x304) = 0;
            *(s32 *)(s1 + 0x300) = 0x2FE;
        }
    } else {
        if (Gsc_HasAction(*(s32 *)(s2 + 0xC), s0, a2) != 0) {
            s0 = Gsc_StartAction(*(s32 *)(s2 + 0xC), s0);
            while (func_0029F6F8(s0) != 0) {
                func_0029F250();
            }
        }
    }
    if (arg1 != NULL) {
        *arg1 = *(s32 *)(s1 + 0x300);
    }
    if (arg2 != NULL) {
        *arg2 = *(s32 *)(s1 + 0x304);
    }
}
