#include "common.h"

void *memset(void *, s32, u32);

void func_002F8DE0(u8 *arg0) {
    if (arg0 != NULL) {
        *(s32 *)arg0 = 0;
        memset(arg0, 0, 0x3C);
    }
}
