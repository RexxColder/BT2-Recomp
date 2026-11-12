#include "common.h"

s64 EftVram_AddClut(u8 *arg0);
s64 EftVram_AddImage(u8 *arg0, s32 arg1, s32 arg2);
void func_001B0798(u8 *arg0, s32 arg1);
extern u8 *D_00387858;

void func_001B03A8(u8 *arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    u8 *bytes;
    u8 *s4;
    s32 s5;
    s64 s6;
    s64 s1;
    s64 clut;

    bytes = (u8 *)sp;
    s5 = 0;
    s4 = *(u8 **)(D_00387858 + 0x170);
    sp[0] = 0;
    s6 = EftVram_AddImage(s4, arg1, arg2);
    s1 = EftVram_AddImage(s4 + 0x40, arg1, arg2);
    func_001B0798(arg0, (s32)sp);
    do {
        s5 += 1;
        if (bytes[s5] != 0) {
            clut = EftVram_AddClut(s4);
            *(s64 *)s4 = s6 | (clut << 37);
            clut = EftVram_AddClut(s4 + 0x40);
            *(s64 *)(s4 + 0x40) = s1 | (clut << 37);
        }
        s4 += 0x10;
    } while (s5 < 4);
}
