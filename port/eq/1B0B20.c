#include "common.h"

void func_001AE5C8(s32 arg0);
extern u8 *D_00387858;

void func_001B0B20(s32 arg0) {
    s32 off;
    s32 off2;
    u8 *s0;
    u8 *s1;
    u8 *v;

    off = arg0 * 4;
    off2 = off + 0xD0;
    s0 = *(u8 **)(D_00387858 + off + 0xC0 + 0xC);
    while (s0 != NULL) {
        s1 = *(u8 **)(s0 + 4);
        func_001AE5C8(*(s32 *)s0);
        v = *(u8 **)(s0 + 8);
        if (v != NULL) {
            *(u8 **)(v + 4) = *(u8 **)(s0 + 4);
        } else {
            *(u8 **)(D_00387858 + off + 0xC0 + 0xC) = *(u8 **)(s0 + 4);
        }
        v = *(u8 **)(s0 + 4);
        if (v != NULL) {
            *(u8 **)(v + 8) = *(u8 **)(s0 + 8);
        } else {
            *(u8 **)(D_00387858 + off2 + 4) = *(u8 **)(s0 + 8);
        }
        *(u8 **)(s0 + 8) = NULL;
        *(s32 *)s0 = 0;
        *(u8 **)(s0 + 4) = NULL;
        s0 = s1;
        *(s32 *)(D_00387858 + 0xC + off2) -= 1;
    }
}
