#include "m2c_macros.h"

s32 func_26E9E8(s32);
extern s32 D_00423114 __attribute__((section(".data")));

void func_003C8A48(void) {
    s32 i = 3;
    s32 off = 0;

    while (1) {
        i -= 1;
        func_26E9E8(D_00423114 + off + 0x20);
        off += 0x28;
        if (i < 0) {
            break;
        }
    }
}
