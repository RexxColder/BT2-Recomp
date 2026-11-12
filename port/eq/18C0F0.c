#include "common.h"

extern s32 D_003877B4;

/* 0x0018C0F0: 1 when the flag D_003877B4 is set, arg0 is not NULL, its pointer at +0x38 is not NULL and the word at
 * +0x1D8 of that has bit 1 set; else 0. */
s32 func_0018C0F0(u8 *arg0) {
    u8 *p;

    if (D_003877B4 == 0 || arg0 == NULL) {
        return 0;
    }
    p = *(u8 **)(arg0 + 0x38);
    if (p == NULL) {
        return 0;
    }
    return (*(s32 *)(p + 0x1D8) & 2) != 0;
}
