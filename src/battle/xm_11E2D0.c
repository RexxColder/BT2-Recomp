#include "m2c_macros.h"

void func_003126C8(s32, void *);
extern u8 D_003885F0[] __attribute__((section(".data")));

// Returns 1 after calling func_003126C8 (a0 passed through unchanged, a1 = D_003885F0+0x90) when the byte at +0xC8 is set; 0 otherwise.
s32 func_0011E2D0(s32 arg0) {
    if (D_003885F0[0xC8] != 0) {
        func_003126C8(arg0, D_003885F0 + 0x90);
        return 1;
    }
    return 0;
}
