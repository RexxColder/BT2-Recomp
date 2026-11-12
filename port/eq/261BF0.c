#include "common.h"

#define LD(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define ST(p, off, v) (*(s32 *)((u8 *)(p) + (off)) = (v))

extern u8 D_00388D48[] __attribute__((section(".data")));
void func_0028BB60(s32 arg0);

void func_00261BF0(void) {
    s32 count;
    s32 i;
    s32 j;
    s32 off;
    s32 p;
    u8 *g;

    g = D_00388D48;

    count = LD(g, 0xC);
    if (count != 0) {
        i = 0;
        if (count + 1 > 0) {
            do {
                p = LD(g, 0);
                func_0028BB60(LD(p + i * 0x10, 0xC));
                i++;
            } while (i < LD(g, 0xC) + 1);
        }
        j = 0;
        off = 0;
        if (count > 0) {
            do {
                p = LD(g, 4) + off;
                if (LD(p, 0x28) != 0) {
                    func_0028BB60(LD(p, 0x28));
                    ST(LD(g, 4) + off, 0x28, 0);
                }
                p = LD(g, 4) + off;
                if (LD(p, 0x2C) != 0) {
                    func_0028BB60(LD(p, 0x2C));
                    ST(LD(g, 4) + off, 0x2C, 0);
                }
                j++;
                off += 0x30;
            } while (j < LD(g, 0xC));
        }
        if (LD(g, 0) != 0) {
            func_0028BB60(LD(g, 0));
            ST(g, 0, 0);
        }
        if (LD(g, 4) != 0) {
            func_0028BB60(LD(g, 4));
            ST(g, 4, 0);
        }
    }
}
