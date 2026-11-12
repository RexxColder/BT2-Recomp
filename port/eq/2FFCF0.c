#include "m2c_macros.h"

u32 strlen(void *s);
void func_003007F8();
extern u8 D_0037E888[] __attribute__((section(".data")));
extern u8 D_0037E8B8[] __attribute__((section(".data")));

/* Appends str to a 16-entry ring (32-byte entries at obj + 0x38) and advances the ring head at obj + 0x1C. */
s32 func_002FFCF0(u8 *obj, u8 *str, s32 a2, s32 a3, s32 t0) {
    s32 s3 = 0;
    s32 x;
    s32 y;
    s32 y2;
    s32 rem;
    s32 w;
    s32 len;
    s32 i;
    s32 count;
    s32 a0;
    s32 v3;
    s32 v0;
    s32 xnew;
    u8 *e;
    u8 *pe;

    if (obj == NULL) {
        func_003007F8(D_0037E888, str, a2, a3);
        return -1;
    }
    if (!(*(s32 *)(obj + 0x24) < 16)) {
        return -1;
    }
    if (str == NULL) {
        func_003007F8(D_0037E8B8, str, a2, a3);
        return -1;
    }
    x = *(s32 *)(obj + 0x1C);
    y = x + 15;
    y2 = (y < 0) ? x + 30 : y;
    rem = y - ((y2 >> 4) << 4);
    pe = obj + 0x38 + rem * 32;
    w = *(s32 *)pe;
    e = obj + 0x38 + x * 32;
    *(s32 *)(e + 0x4) = (s32)(long)str;
    s3 = ((w ^ 0x7FFFFFFF) != 0) ? w + 1 : 0;
    *(s32 *)e = s3;
    len = (s32)strlen(str);
    *(s32 *)(e + 0x8) = 0;
    for (i = 0; i < len; i++) {
        *(s32 *)(e + 0x8) = *(s32 *)(e + 0x8) + str[i];
    }
    *(s32 *)(e + 0x10) = a3;
    *(s32 *)(e + 0x14) = t0;
    *(s32 *)(e + 0x1C) = 0;
    *(s32 *)(e + 0x18) = 0;
    *(s32 *)(e + 0xC) = a2;

    count = *(s32 *)(obj + 0x24);
    a0 = x + 1;
    v3 = x + 16;
    v0 = (a0 < 0) ? v3 : a0;
    *(s32 *)(obj + 0x24) = count + 1;
    xnew = a0 - ((v0 >> 4) << 4);
    *(s32 *)(obj + 0x1C) = xnew;
    if ((s8)obj[1] == 1) {
        obj[1] = 2;
    }
    return s3;
}
