#include "common.h"

extern u8 D_003B0C34[] __attribute__((section(".data")));
s32 func_0028C490(s32 arg0) {
    return (*(s32 *)(D_003B0C34 + arg0 * 0x180) & 0x5800) != 0;
}
