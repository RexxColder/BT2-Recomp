#include "common.h"
extern u8 D_00388DB0[] __attribute__((section(".data")));

void func_00283988(u32 arg0) {
    if (arg0 < 8) {
        *(s32 *)(D_00388DB0 + arg0 * 0x30) = 0;
    }
}
