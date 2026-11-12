#include "common.h"

u8 *func_002C3D18(s32 arg0);

s32 func_002C3CB8(s32 arg0, s32 arg1) {
    u8 *t;

    t = func_002C3D18(arg0);
    if (*(s32 *)t != 0 || (*(s32 *)(t + 0x10) == 0 && *(s32 *)(t + 0x14) == 0)) {
        return arg1 == (*(s32 *)(t + 0x8) + *(s32 *)(t + 0xC));
    }
    return 0;
}
