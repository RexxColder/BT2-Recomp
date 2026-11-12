#include "m2c_macros.h"

extern u8 *gBtlCam;

s32 func_0025C018(void) {
    u8 *p = gBtlCam + 0x258;
    s32 i = 0;
    s32 v1 = *(s32 *)p;
    s32 v0;

    while (1) {
        p += 0x300;
        v0 = i;
        i++;
        if (v1 == 0) {
            return v0;
        }
        if (i >= 2) {
            return -1;
        }
        v1 = *(s32 *)p;
    }
}
