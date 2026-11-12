#include "common.h"

typedef struct { u8 *p[64]; } AlphaTbl;
extern AlphaTbl D_00377150;
void OldPass_PutBits(s32 value, s32 bitpos, s32 nbits);

/* 0x00287660 OldPass_TextToBits: packs each char of the string as the 6-bit index of its position in the 64-entry
 * alphabet table D_00377150 (chars not found are skipped). */
void OldPass_TextToBits(s8 *text) {
    AlphaTbl tbl;
    s32 bitpos = 0;
    s32 i;

    tbl = D_00377150;
    while (*text != 0) {
        s8 c = *text;
        for (i = 0; i < 64; i++) {
            if (c == *(s8 *)tbl.p[i]) {
                OldPass_PutBits(i, bitpos, 6);
                bitpos += 6;
                break;
            }
        }
        text++;
    }
}
