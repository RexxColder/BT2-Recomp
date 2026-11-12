#include "common.h"

s8 *func_002D4D90(s8 *arg0, s32 *arg1) {
    s8 *p;
    s8 c;
    s32 a2;
    s32 temp;

    p = arg0;
    c = *p;
    a2 = 0;
    if (c != 0x2E && c != 0x20 && c != 0 && (u32)(c - 0x30) < 10U) {
        for (;;) {
            p += 1;
            temp = a2 * 10 + c;
            c = *p;
            a2 = temp - 0x30;
            if (c == 0x2E || c == 0x20 || c == 0) {
                break;
            }
            if ((u32)(c - 0x30) >= 10U) {
                break;
            }
        }
    }
    *arg1 = a2;
    return p;
}
