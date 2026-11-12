#include "common.h"

extern s32 D_003475E0 __attribute__((section(".data")));
extern s32 D_003475E4 __attribute__((section(".data")));
extern s32 D_003475E8 __attribute__((section(".data")));
extern u8 D_0037AE70[] __attribute__((section(".data")));

void func_002D8940(void) {
    D_003475E0 -= 1;
    if (D_003475E0 == 0 && D_003475E4 != -1 && (D_003475E8 & 0xC7) != 0x82) {
        *(s32 *)(*(u8 **)(D_0037AE70 + (D_003475E4 << 2))) = D_003475E8 ^ 0xC00;
    }
    if (D_003475E0 < 0) {
        D_003475E0 = 0;
    }
}
