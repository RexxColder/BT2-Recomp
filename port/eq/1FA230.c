#include "common.h"

s32 func_001FA230(void *arg0, f32 farg0) {
    u8 *p;
    f32 fa;
    f32 fb;

    p = *(u8 **)((u8 *)arg0 + 0x1530) + 0xBD0;
    fa = *(f32 *)(p + 0x10);
    fb = *(f32 *)(p + 0x14);
    if (fb <= fa) {
        return (fb <= farg0 && farg0 < fa) ? 1 : 0;
    }
    return (fb <= farg0 || farg0 < fa) ? 1 : 0;
}
