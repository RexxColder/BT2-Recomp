#include "common.h"

u8 *func_0025CFE0(u8 *arg0);
u8 *func_0025D018(void);

void func_0025D100(u8 *arg0) {
    u8 *s0;
    u8 *s1;
    u8 *v;

    s1 = *(u8 **)(arg0 + 0x48);
    for (;;) {
        s0 = func_0025D018();
        *(s32 *)(s0 + 0xD4) = *(u16 *)(s1 + 0xA);
        v = func_0025CFE0(arg0 + 0xDE8);
        if (v != NULL) {
            *(u8 **)(v + 0xDC) = s0;
            *(u8 **)(s0 + 0xD8) = v;
            *(s32 *)(s0 + 0xDC) = 0;
        } else {
            *(u8 **)(arg0 + 0xDE8) = s0;
            *(s32 *)(s0 + 0xDC) = 0;
            *(u8 **)(s0 + 0xD8) = NULL;
        }
        if (*(u16 *)(s1 + 0x6) != 0) {
            break;
        }
        s1 += *(s32 *)s1;
    }
    *(u8 **)(arg0 + 0xDEC) = *(u8 **)(arg0 + 0xDE8);
}
