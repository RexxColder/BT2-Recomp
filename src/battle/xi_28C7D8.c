#include "m2c_macros.h"

M2C_UNK sceVibGetProfile(s32, void *);              /* extern */
extern u8 D_003B0B00 __attribute__((section(".data")));

// Two sceVibGetProfile calls on the vibration tables in D_003B0B00: (word +0x100, +0x14E) and (word +0x280, +0x2CE).
void func_0028C7D8(void) {
    u8 *base;

    base = &D_003B0B00;
    sceVibGetProfile(*(s32 *)(base + 0x100), base + 0x14E);
    sceVibGetProfile(*(s32 *)(base + 0x280), base + 0x2CE);
}
