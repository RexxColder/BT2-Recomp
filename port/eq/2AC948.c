#include "common.h"

void func_002AC580(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 *D_003876A4;
extern u8 D_003B2654[] __attribute__((section(".data")));

s32 func_002AC948(void) {
    u8 *temp_s0;

    temp_s0 = D_003B2654 - 0x54;
    memset(D_003B2654, 0, 0x5C);
    *(s32 *)(temp_s0 + 0) = *(s32 *)(D_003876A4 + 0x30);
    *(s32 *)(temp_s0 + 4) = *(s32 *)(D_003876A4 + 0x34);
    func_002AC580((s32)D_003876A4);
    return 1;
}
