#include "common.h"

extern u8 *D_00387A44;

s32 func_002696C0(void) {
    s32 n = 0;
    s32 off = 0;

    for (;;) {
        if (((u8 *)(D_00387A44 + off))[0xC] == 0) {
            ((u8 *)(D_00387A44 + off))[0xC] = 1;
            return (s32)(D_00387A44 + off);
        }
        n++;
        off += 0x20C0;
        if (n >= 7) {
            return 0;
        }
    }
}
