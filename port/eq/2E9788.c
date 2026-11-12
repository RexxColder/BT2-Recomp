#include "common.h"

/* 0x002E9788: parse a header record (big-endian 0x8000 tag at +0, s24 field at +2..+3 >= 0x0E,
 * big-endian u16 at +0x10 stored to *a2). Returns -1 if a1 < 0x12, -2 if the tag is wrong,
 * -1 if the field is small, else 0. */
s32 func_002E9788(void *arg0, s32 arg1, s16 *arg2) {
    u8 *p = (u8 *)arg0;
    u16 tag;
    s32 field;
    u16 val;

    if (arg1 < 0x12) {
        return -1;
    }
    tag = (u16)((p[0] << 8) | p[1]);
    if (tag != 0x8000) {
        return -2;
    }
    field = (s16)(p[3] | ((p[2] << 8) & ~0xFF));
    if (field < 0xE) {
        return -1;
    }
    val = (u16)((p[0x10] << 8) | p[0x11]);
    *arg2 = (s16)val;
    return 0;
}
