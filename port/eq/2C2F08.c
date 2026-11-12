#include "common.h"

void func_002C2F08(u8 *arg0) {
    u8 *p = arg0 + 0x1FC;

    *(s32 *)(p + 4) = 0;
    *(s32 *)p = 0;
}
