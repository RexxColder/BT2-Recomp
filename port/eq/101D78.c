#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 *D_003876A0;

void func_00101D78(void) {
    u8 *a1;
    s32 v1;
    s32 flag;
    s32 w;

    a1 = D_003876A0 + 0x480;
    if (*(s32 *)(D_003876A0 + 0xB8) == 6) {
        memset(a1, 0, 0x50);
        return;
    }
    v1 = *(s32 *)(a1 + 4);
    flag = v1 & 0x80;
    if (v1 & 0x40) {
        *(s32 *)a1 = *(s32 *)a1 | 2;
        flag = v1 & 0x80;
    }
    if (flag != 0) {
        *(s32 *)a1 = *(s32 *)a1 | 1;
    }
    w = *(s32 *)a1;
    if (!(w & 8)) {
        if (*(s32 *)(D_003876A0 + 0xD8) & 2) {
            if (w & 1) {
                *(s32 *)(a1 + 4) = v1 | 0x10000;
            }
            *(s32 *)a1 = 1;
        } else if (w & 1) {
            *(s32 *)(a1 + 4) = v1 | 0x10000;
        }
    }
}
