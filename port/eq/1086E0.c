#include "common.h"

s32 BtlText_IsNewline(s32 arg0);

u16 *BtlText_NextLine(u16 *arg0) {
    u8 *s = (u8 *)arg0;
    u16 c;

    for (;;) {
        c = *(u16 *)s;
        if (c == 0) {
            break;
        }
        s += 2;
        if (BtlText_IsNewline((s32)c) != 0) {
            break;
        }
    }
    return (u16 *)s;
}
