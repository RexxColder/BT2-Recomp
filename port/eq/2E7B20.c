#include "common.h"

s32 func_002E7B20(s32 arg0) {
    s16 type;
    s16 sub;

    type = *(s16 *)((u8 *)arg0 + 0x98);
    if (type == 0) {
        return 0x10;
    }
    if (type == 2) {
        sub = *(s16 *)((u8 *)arg0 + 0x9C);
        if (sub == 2) {
            return 4;
        }
        return ((sub ^ 1) != 0) ? 0x10 : 8;
    }
    if (type == 1) {
        sub = *(s16 *)((u8 *)arg0 + 0x9C);
        return ((sub ^ 2) != 0) ? 0x10 : 4;
    }
    return 0x10;
}
