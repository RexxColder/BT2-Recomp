#include "common.h"

void func_002C6110(u8 *arg0) {
    u8 *p = arg0 + 0xE48;

    if (*(s32 *)(p + 0x24) != 0x7FFFFFFF) {
        *(s32 *)p = 1;
    }
}
