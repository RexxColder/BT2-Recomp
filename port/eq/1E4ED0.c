#include "common.h"

void func_001E4CD0(u8 *arg0, u8 *arg1);
extern u8 *D_003878E4;

/* 0x001E4ED0: D_003878E4 holds 12-byte entries (count at +0x600). Pass 1 clears word +0x204 of each entry's word2 object.
 * Pass 2: entry word0 != 0 and byte +0x21E5 set -> func_001E4CD0(word0 + 0x10, word2); else word0 == 0, word1 != 0
 * and byte +0x21DA of word1 set -> func_001E4CD0(word1, word2). */
void func_001E4ED0(void) {
    s32 i;
    s32 w0;
    s32 w1;
    s32 w2;

    for (i = 0; i < *(s32 *)(D_003878E4 + 0x600); i++) {
        w2 = *(s32 *)(D_003878E4 + 12 * i + 8);
        *(s32 *)((u8 *)w2 + 0x204) = 0;
    }
    for (i = 0; i < *(s32 *)(D_003878E4 + 0x600); i++) {
        w0 = *(s32 *)(D_003878E4 + 12 * i);
        w1 = *(s32 *)(D_003878E4 + 12 * i + 4);
        w2 = *(s32 *)(D_003878E4 + 12 * i + 8);
        if (w0 != 0) {
            if (*(u8 *)(w0 + 0x21E5) != 0) {
                func_001E4CD0((u8 *)(w0 + 0x10), (u8 *)w2);
            }
        } else if (w1 != 0) {
            if (*(u8 *)(w1 + 0x21DA) != 0) {
                func_001E4CD0((u8 *)w1, (u8 *)w2);
            }
        }
    }
}
