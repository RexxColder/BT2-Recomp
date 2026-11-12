#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
extern u8 D_0036F940[] __attribute__((section(".data")));
extern u8 *D_00387F2C;

/* 0x00207298(obj, key): copies the eight words at D_0036F940; base = D_00387F2C + 32 * word(obj+0x1534) + 0x100C;
 * returns the copied word at the index whose table entry equals key, or 0 when none does. */
s32 func_00207298(u8 *arg0, s32 arg1) {
    s32 tab[8];
    u8 *base;
    s32 i;

    memcpy(tab, D_0036F940, 0x20);
    base = D_00387F2C + (*(s32 *)(arg0 + 0x1534) << 5) + 0x100C;
    for (i = 0; i < 8; i++) {
        if (*(s32 *)(base + 4 * i) == arg1) {
            return tab[i];
        }
    }
    return 0;
}
