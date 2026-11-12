#include "common.h"

u16 *BtlText_NextLine(u16 *arg0, u16 arg1);
s32 Font_GetGlyphHeight(void);
s32 func_001081C0(void);

s32 func_00109818(void) {
    s32 s0;
    s32 s3;
    s32 s5;
    s32 s6;
    s32 v0;
    s32 r;
    u16 c;
    u16 s2;
    u16 *s1;

    s0 = 0;
    s2 = 0;
    s3 = 0;
    s5 = 1;
    r = func_001081C0();
    s1 = (u16 *)((u8 *)r + 2);
    s6 = Font_GetGlyphHeight() * 0x12;

    for (;;) {
        c = *s1;
        if (c == 0x25) {
            if (*(u16 *)((u8 *)s1 + 2) == 0x30) {
                s0 += 6;
            } else if (s2 == 0x24) {
                s0 += 6;
            }
        } else if (c < 0x26) {
            if (c == 0x24) {
                s0 = (s3 != 0) ? (s0 + 0xC) : (s0 + 6);
            }
        } else {
            if (c == 0x40) {
                s5 = 0;
            }
        }
        s2 = c;
        s1 = BtlText_NextLine(s1, c);
        v0 = s0 - s6;
        if (*s1 != 0) {
            s0 += 0x19;
            s3 += 1;
            if (s5 == 0) {
                v0 = s0 - s6;
                break;
            }
            continue;
        }
        break;
    }

    v0 = v0 + 6;
    return (v0 >= 0) ? v0 : 0;
}
