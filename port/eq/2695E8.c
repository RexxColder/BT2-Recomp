#include "common.h"

s32 func_00268B28(s32 arg0);
s32 func_0028BAA8(s32 arg0);
extern s32 D_00387A44 __attribute__((section(".data")));

void func_002695E8(void) {
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 r;

    s2 = 0;
    s3 = 6;
    D_00387A44 = func_0028BAA8(0xE560);
    memset((void *)D_00387A44, 0, 0xE560);
    s1 = func_00268B28(0x120) * 4;
    do {
        s0 = s2 + 4;
        r = func_0028BAA8(s1);
        s3 -= 1;
        *(s32 *)(D_00387A44 + s2) = r;
        r = func_0028BAA8(s1);
        *(s32 *)(D_00387A44 + s0) = r;
        memset((void *)*(s32 *)(D_00387A44 + s2), 0, s1);
        memset((void *)*(s32 *)(D_00387A44 + s0), 0, s1);
        s2 += 0x20C0;
    } while (s3 >= 0);
}
