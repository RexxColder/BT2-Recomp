#include "m2c_macros.h"

extern s32 D_00388A48 __attribute__((section(".data")));

s32 func_002622F0(void) {
    u8 *p = (u8 *)&D_00388A48;
    s32 i = 0;
    s32 v1 = *(s32 *)p;
    s32 v0;

    while (1) {
        p += 0x30;
        v0 = i;
        i++;
        if ((v1 & 1) == 0) {
            return v0;
        }
        if (i >= 0x10) {
            return -1;
        }
        v1 = *(s32 *)p;
    }
}
