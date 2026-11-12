#include "common.h"

void func_002E0E30(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *p = arg0 + 8;
    s32 fn = *(s32 *)(arg0 + 0x18);

    if (fn != 0) {
        ((void (*)(s32, s32, s32, s32))(void *)(s64)fn)(*(s32 *)(p + 0), *(s32 *)(p + 4), *(s32 *)(p + 8), arg2);
    }
    *(s32 *)(arg0 + 4) = 0;
}
