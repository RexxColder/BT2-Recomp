#include "common.h"

/* 0x00120FF0: src = arg0 + 0x10. Copies src[0..15] to arg0 + 0x24..0x33 and the word src[0x10] to arg0 + 0x34, then
 * sets src[0..3] to 0x80 bytes, src word +4 = 0 and src word +8 = (src word +8 + 1) & 0x3FFFFFFF. */
void func_00120FF0(u8 *arg0) {
    u8 *src = arg0 + 0x10;
    s32 k;
    s32 w8;

    for (k = 0; k < 8; k++) {
        arg0[0x24 + k] = src[k];
    }
    for (k = 0; k < 8; k++) {
        arg0[0x2C + k] = src[8 + k];
    }
    *(s32 *)(arg0 + 0x34) = *(s32 *)(src + 0x10);
    for (k = 0; k < 4; k++) {
        src[k] = 0x80;
    }
    *(s32 *)(src + 0x4) = 0;
    w8 = *(s32 *)(src + 0x8);
    *(s32 *)(src + 0x8) = (w8 + 1) & 0x3FFFFFFF;
}
