#include "common.h"

/* 0x00148A08: if (func_00126560(a0, a1) == 0) tail func_00208738(a0, a1); else return *(s32 *)(D_00388728 + (6*a0 + a1) * 4). */
extern u8 D_00388728[];
s32 func_00126560(s32 arg0, s32 arg1);
s32 func_00208738(s32 arg0, s32 arg1);

s32 func_00148A08(s32 a0, s32 a1) {
    if (func_00126560(a0, a1) == 0) {
        return func_00208738(a0, a1);
    }
    return *(s32 *)(D_00388728 + ((a0 * 6 + a1) << 2));
}
