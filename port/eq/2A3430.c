#include "common.h"

void func_00256590(void);
void func_0028BB60(s32 arg0);
void func_002A3170(void);
extern u8 D_003B0F40[] __attribute__((section(".data")));

void func_002A3430(void) {
    u8 *base;
    u8 *s1;
    s32 v;
    s32 s0;

    base = D_003B0F40;
    s1 = base + 4;
    if (*(s32 *)base != 0) {
        func_0028BB60(*(s32 *)base);
    }
    s0 = 7;
    do {
        v = *(s32 *)s1;
        s1 += 4;
        if (v != 0) {
            func_0028BB60(v);
        }
        s0 -= 1;
    } while (s0 >= 0);
    if (*(s32 *)(base + 0x24) != 0) {
        func_0028BB60(*(s32 *)(base + 0x24));
    }
    if (*(s32 *)(base + 0x28) != 0) {
        func_0028BB60(*(s32 *)(base + 0x28));
    }
    if (*(s32 *)(base + 0x2C) != 0) {
        func_0028BB60(*(s32 *)(base + 0x2C));
    }
    if (*(s32 *)(base + 0x30) != 0) {
        func_00256590();
        func_0028BB60(*(s32 *)(base + 0x30));
    }
    if (*(s32 *)(base + 0x34) != 0) {
        func_0028BB60(*(s32 *)(base + 0x34));
    }
    func_002A3170();
}
