#include "common.h"

extern u8 *D_00348C38;
extern u8 *D_00348C3C;

/* Scans buf (len bytes) for two 4-byte tags, reads a record that follows the first tag
   (16-bit size word, format fields) and derives the decode parameters. Returns 0 when the
   record is usable, -1 otherwise. */
s32 func_002E8AC0(u8 *buf, s32 len, u16 *out_off, u8 *out_a4, u8 *out_a5, u8 *out_a6,
                  u8 *out_a7, s32 *out_a8, s32 *out_a9, s32 *out_a10, u16 *out_a11) {
    s32 i;
    s32 j;
    s32 v21;
    u8 *rec;

    i = 0;
    while (i < len && __builtin_memcmp(buf + i, D_00348C38, 4) != 0) {
        i++;
    }
    if (i == len || (i & 3) != 0) {
        return -1;
    }

    rec = buf + i + 8;
    if (*(s16 *)rec >= 2) {
        return -1;
    }

    j = 0;
    while (j < len && __builtin_memcmp(buf + j, D_00348C3C, 4) != 0) {
        j++;
    }
    if (j == len) {
        return -1;
    }

    *out_off = (u16)(j + 8);
    v21 = *(s32 *)(buf + j + 4);
    *out_a4 = 0xFF;
    *out_a8 = *(s32 *)(rec + 4);
    *out_a7 = rec[2];
    *out_a5 = rec[0xE];
    *out_a6 = rec[0xC];
    *out_a9 = v21 / (s8)*out_a6;
    *out_a10 = 1;

    switch ((s8)*out_a5) {
    case 16:
        *out_a11 = 0;
        break;
    case 8:
        *out_a11 = 1;
        break;
    case 4:
        *out_a6 = (u8)(2 * (s8)*out_a7);
        *out_a10 = 4;
        *out_a9 = (v21 / 2) / (s8)*out_a7;
        *out_a5 = 16;
        *out_a11 = 2;
        break;
    default:
        break;
    }

    if (*out_a5 == 0) {
        return -1;
    }
    if ((s8)*out_a6 == 0) {
        return -1;
    }
    if ((u8)(*out_a7 - 1) >= 2) {
        return -1;
    }
    return (*out_a8 != 0) ? 0 : -1;
}
