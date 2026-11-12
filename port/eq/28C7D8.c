#include "common.h"

/* 0x0028C7D8: s = D_003B0B00; sceVibGetProfile(*(s + 0x100), s + 0x14E); return sceVibGetProfile(*(s + 0x280), s + 0x2CE). */
extern u8 D_003B0B00[];
s32 sceVibGetProfile(s32 arg0, s32 arg1);

s32 func_0028C7D8(void) {
    u8 *s;

    s = D_003B0B00;
    sceVibGetProfile(*(s32 *)(s + 0x100), (s32)(s + 0x14E));
    return sceVibGetProfile(*(s32 *)(s + 0x280), (s32)(s + 0x2CE));
}
