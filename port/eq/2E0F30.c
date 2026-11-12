#include "common.h"

void func_002E0F30(u8 *arg0, u8 arg1, u8 arg2, u8 arg3) {
    u8 *p = arg0 + 0x14;

    p[2] = arg3;
    p[0] = arg1;
    p[1] = arg2;
}
