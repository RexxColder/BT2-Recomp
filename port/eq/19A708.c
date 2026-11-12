#include "common.h"

s32 EftAura_CommandAlt(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 *gEftGlow;
extern u8 *gEftGlowCfg;

s32 func_0019A708(s32 arg0, s32 arg2, s32 arg3) {
    s32 table;
    u8 *temp;
    u8 *p;
    s32 flags;
    s32 a3;

    table = *(s32 *)(gEftGlow + 0x6F0);
    temp = *(u8 **)(arg0 * 4 + table);
    if (temp == NULL) {
        EftAura_CommandAlt(arg0, 1, arg2, arg3);
        return 1;
    }
    p = *(u8 **)(temp + 0x38);
    flags = *(s32 *)p;
    a3 = flags & 2;
    if (flags & 1) {
        if (a3 == 0) {
            *(s32 *)p = flags | 2;
            *(s32 *)(p + 0x34) = 2;
            *(s32 *)(p + 0x14) = 9;
            *(f32 *)(p + 0x38) = *(f32 *)(gEftGlowCfg + 0x1AC);
            *(f32 *)(p + 0x3C) = 1.0f;
            EftAura_CommandAlt(arg0, 1, (s32)p, a3);
            return 1;
        }
    }
    return 0;
}
