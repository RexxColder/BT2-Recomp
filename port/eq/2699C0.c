#include "common.h"

extern u8 *D_00387A40;

s32 func_002699C0(void) {
    u8 *p;
    s32 cnt = 0;
    s32 i = 15;

    p = (u8 *)(*(s32 *)(D_00387A40 + 8) + 0x13CEC);
    do {
        if (*(s32 *)p != 0) {
            cnt++;
        }
        p -= 0x1520;
        i--;
    } while (i >= 0);
    return cnt;
}
