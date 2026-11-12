#include "common.h"

extern s32 D_00399C68 __attribute__((section(".data")));
extern s32 D_00399C90[] __attribute__((section(".data")));
extern s32 D_00399C98[] __attribute__((section(".data")));

s32 func_002C9F80(void) {
    u8 *r;
    s32 a;
    s32 idx;
    s32 *p;
    s32 v;

    r = (u8 *)&D_00399C68;
    a = *(s32 *)(r + 0x1C);
    if ((u32)(a - 1) >= 0x10U) {
        return -1;
    }
    if (*(s32 *)(r + 0x10) != 0) {
        if (*(s32 *)(r + 0x20) != 0) {
            return 0;
        }
    }
    idx = 0;
    p = D_00399C90;
    v = *p;
    for (;;) {
        if (v == 0) {
            return -1;
        }
        p += 1;
        idx += 1;
        if (idx >= 2) {
            break;
        }
        v = *p;
    }
    a = *(s32 *)(r + 0x1C);
    if (a <= 0) {
        return 0;
    }
    idx = 0;
    p = D_00399C98;
    v = *p;
    for (;;) {
        if (v == 0) {
            return -1;
        }
        p += 1;
        idx += 1;
        if (idx >= a) {
            return 0;
        }
        v = *p;
    }
}
