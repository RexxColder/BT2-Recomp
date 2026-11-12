#include "common.h"

extern u8 D_003B0F40[] __attribute__((section(".data")));

void *func_002A3E48(void) {
    s32 temp_a0;

    temp_a0 = *(s32 *)(D_003B0F40 + 0x38);
    *(s32 *)(D_003B0F40 + 0x38) = temp_a0 + 1;
    return (void *)(D_003B0F40 + 0x3C + temp_a0 * 104);
}
