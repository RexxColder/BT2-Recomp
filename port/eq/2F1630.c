#include "common.h"

s32 func_002E7BE0(s32 arg0);
s32 func_002E7BE8(s32 arg0);

/* 0x002F1630: if func_002E7BE0(arg0->0x4) > 0 and (arg0->0x1 - 2) < 2 (unsigned), return func_002E7BE8(arg0->0x4);
 * otherwise 0. */
s32 func_002F1630(u8 *arg0) {
    if (func_002E7BE0(*(s32 *)(arg0 + 0x4)) > 0) {
        if ((u32)(*(u8 *)(arg0 + 0x1) - 2) < 2) {
            return func_002E7BE8(*(s32 *)(arg0 + 0x4));
        }
    }
    return 0;
}
