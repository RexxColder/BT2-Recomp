#include "common.h"

extern u8 D_003B2A0C[];
void func_00259DE0(void);
void *memset(void *dst, s32 c, u32 n);

void func_002AB0E0(void) {
    func_00259DE0();
    memset(D_003B2A0C, 0, 0x228);
    *(s32 *)(D_003B2A0C + 0x14) = -1;
    *(s32 *)(D_003B2A0C + 0x8) = -1;
    *(s32 *)(D_003B2A0C + 0xC) = -1;
    *(s32 *)(D_003B2A0C + 0x10) = -1;
}
