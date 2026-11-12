#include "common.h"

s32 memcmp(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0037BAA0[] __attribute__((section(".data")));
extern u8 D_0037BAA8[] __attribute__((section(".data")));

s32 func_002E92A0(s32 arg0) {
    if (memcmp(arg0, (s32)D_0037BAA0, 4) == 0 && memcmp(arg0 + 8, (s32)D_0037BAA8, 4) == 0) {
        return 1;
    }
    return 0;
}
