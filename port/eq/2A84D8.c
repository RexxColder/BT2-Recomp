#include "common.h"

f32 Gsc_GetFloat(void);
s32 Gsc_GetInt(void);
s32 func_002A0010(s32 arg0);
u8 *func_002A3DB8(s32 arg0);

s32 func_002A84D8(s32 arg0) {
    s32 t;
    u8 *ent;
    f32 f;
    s32 r;

    switch (arg0) {
    case 0:
        t = Gsc_GetInt();
        if (t < 0) {
            return 1;
        }
        ent = func_002A3DB8(t);
        f = Gsc_GetFloat() * 300.0f;
        *(s32 *)(ent + 0x20) = 2;
        *(s8 *)(ent + 0xB) = -0x80;
        *(s8 *)(ent + 0x18) = 1;
        *(s16 *)(ent + 0x26) = 0;
        /* cvt.w.s (funct 0x24 in the .word): truncates toward zero */
        r = (s32)f;
        *(s16 *)(ent + 0x24) = (s16)r;
        return func_002A0010(0x77) == 0;
    case 1:
        return 0;
    case 2:
        t = Gsc_GetInt();
        ent = func_002A3DB8(t);
        return *(s32 *)(ent + 0x20) == 0;
    default:
        return 0;
    }
}
