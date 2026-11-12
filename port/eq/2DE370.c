#include "common.h"

void func_002DE370(u8 *arg0, s32 *arg1, s32 *arg2) {
    u8 *p = arg0 + 0x3EC;

    if (arg1 != 0) {
        *arg1 = *(s32 *)p;
    }
    if (arg2 != 0) {
        *arg2 = *(s32 *)(p + 8);
    }
}
