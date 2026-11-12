#include "common.h"

extern s32 D_003534A8;
extern u8 D_003534B0[];
void *memset(void *dst, s32 c, u32 n);

void func_002F0130(void) {
    D_003534A8 = D_003534A8 - 1;
    if (D_003534A8 == 0) {
        memset(D_003534B0, 0, 0xAC0);
    }
}
