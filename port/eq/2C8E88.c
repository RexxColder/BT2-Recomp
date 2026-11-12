#include "common.h"

/* 0x002C8E88(obj): when the word at obj+0xDF0+0x24 < the word at obj+0xE6C (signed), copies the 44 bytes at
 * obj+0xDF0 to obj+0xE1C. */
void func_002C8E88(u8 *arg0) {
    u8 *src = arg0 + 0xDF0;
    u8 *dst = arg0 + 0xE1C;
    s32 k;

    if (*(s32 *)(src + 0x24) < *(s32 *)(arg0 + 0xE6C)) {
        for (k = 0; k < 0x2C; k++) {
            dst[k] = src[k];
        }
    }
}
