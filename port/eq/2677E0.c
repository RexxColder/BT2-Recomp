#include "common.h"

void func_002677E0(void *arg0, u32 arg1) {
    u8 *p;

    p = (u8 *)arg0;
    *(u32 *)(p + 0xAF0) = *(u32 *)(p + 0xAF0) | 0x04000000;
    if (*(u32 *)(*(u8 **)(p + 0x54)) >= arg1) {
        *(u32 *)(p + 0xDF0 + 0xC) = arg1;
    }
}
