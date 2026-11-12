#include "common.h"

s32 *func_00202E60(u8 *arg0, s32 arg1);

void func_00203280(u8 *arg0) {
    s32 s1;
    s32 hi;
    s32 v;

    s1 = *(s32 *)(arg0 + 0x1184) - 1;
    if (s1 < 0) {
        return;
    }
    do {
        v = *(s32 *)(arg0 + 0x118C) + s1;
        s1 -= 1;
        hi = v % *(s32 *)(arg0 + 0x1184);
        if (hi != *(s32 *)(arg0 + 0x1180)) {
            if (*func_00202E60(arg0, hi) > 0) {
                *(s32 *)(arg0 + 0x118C) = hi;
                return;
            }
        }
        if (s1 < 0) {
            return;
        }
    } while (1);
}
