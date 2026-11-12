#include "m2c_macros.h"

extern s32 D_00346E2C __attribute__((section(".data")));

s32 func_002CE040(void) {
    u8 *p = (u8 *)&D_00346E2C;
    s32 i = 0;
    s32 v1 = *(s32 *)p;
    s32 v0;

    while (1) {
        p += 4;
        v0 = i;
        i++;
        if (v1 == 0) {
            return v0;
        }
        if (i >= 8) {
            return -1;
        }
        v1 = *(s32 *)p;
    }
}
