#include "common.h"

/* 0x00284AC8: for the 3 entries of 0x60 bytes at D_00388F30: byte +0x58 = 0; func_0029BAB0(entry + 0x40). */
extern u8 D_00388F30[] __attribute__((section(".data")));
void func_0029BAB0(s32 arg0);

void func_00284AC8(void) {
    u8 *p;
    s32 n;

    p = D_00388F30;
    n = 2;
    do {
        n--;
        p[0x58] = 0;
        func_0029BAB0((s32)(p + 0x40));
        p += 0x60;
    } while (n >= 0);
}
