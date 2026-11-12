#include "common.h"

extern u8 D_0039D650[] __attribute__((section(".data")));

void *memcpy(void *arg0, const void *arg1, u32 arg2);
void func_002E20C8(u8 *arg0);
void func_002E16D0(u8 *arg0);

u8 *func_002E1810(u8 *arg0) {
    memcpy(arg0 + 0x18, D_0039D650, 0x40);
    func_002E20C8(arg0);
    func_002E16D0(arg0 + 0x58);
    *(s32 *)(arg0 + 0x118) = 0;
    *(s32 *)(arg0 + 0) = 2;
    return arg0;
}
