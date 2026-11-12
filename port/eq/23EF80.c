#include "m2c_macros.h"

extern s32 Battle_GetSetup(s32 arg0);

s32 func_0023EF80(s32 arg0) {
    u8 *p;
    s8 a;

    p = (u8 *)Battle_GetSetup(arg0);
    a = *(s8 *)(p + 0x27);
    if (a != 0) {
        return a;
    }
    return *(s8 *)(p + 0x20);
}
