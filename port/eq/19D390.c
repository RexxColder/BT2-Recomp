#include "common.h"

s64 EftVram_AddImage(u8 *arg0, s32 arg1, s32 arg2);
s64 EftVram_AddClut(u8 *arg0);

void func_0019D390(u8 *arg0) {
    u8 *s2 = arg0 + 0xAB0;
    u8 *s1;
    u8 *base;
    s32 s3;
    s32 s4;
    s64 s0;
    s64 clut;

    base = *(u8 **)(s2 + 0x48);
    if (*(s32 *)(base + 0x200) > 0) {
        s4 = 0;
        s1 = arg0;
        do {
            base = *(u8 **)(s2 + 0x48);
            s3 = 1 << (s4 & 31);
            if ((*(s32 *)(base + 0x204) & s3) == 0) {
                s0 = EftVram_AddImage(s1 + 0x50, 1, 0);
                clut = EftVram_AddClut(s1 + 0x60);
                base = *(u8 **)(s2 + 0x48);
                *(s64 *)(base + s4 * 16) = s0 | (clut << 37);
                base = *(u8 **)(s2 + 0x48);
                *(s32 *)(base + 0x204) = *(s32 *)(base + 0x204) | s3;
            }
            base = *(u8 **)(s2 + 0x48);
            s4 += 1;
            s1 += 0x20;
        } while (s4 < *(s32 *)(base + 0x200));
    }
}
