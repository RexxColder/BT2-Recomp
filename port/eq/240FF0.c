#include "common.h"

u8 *func_00208768(s32 arg0, s32 arg1);

s32 func_00240FF0(u8 *arg0, s32 arg1) {
    u8 *p = func_00208768(*(s32 *)(arg0 + 0x1534), arg1);

    if (p == 0) {
        return 1;
    }
    return *(s16 *)(p + 0x34);
}
