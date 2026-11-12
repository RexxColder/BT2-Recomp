#include "common.h"

extern u8 D_003B0C48[] __attribute__((section(".data")));
void func_0028C3B0(s32 arg0) {
    *(s32 *)(D_003B0C48 + arg0 * 0x180) = 1;
}
