#include "common.h"

s32 Battle_GetSetup(s32 arg0);

s32  func_0023EF48(s32 arg0) {
    s8 v;
    u8 *p;

    p = (u8 *)Battle_GetSetup(arg0);
    v = *(s8 *)(p + 0x26);
    if (v == 0) {
        v = *(s8 *)(p + 0x20);
    }
    return (s8)(v);
}
