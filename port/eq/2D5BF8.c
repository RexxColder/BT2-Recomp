#include "common.h"

void func_002D6C90(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0037A880[] __attribute__((section(".data")));

s32 func_002D5BF8(u8 *arg0) {
    s32 t;

    t = *(s32 *)(arg0 + 4);
    if (t == 0x21 || t == 0x101) {
        return 1;
    }
    if (t == 0x11 || t == 0x31 || t == 0x41 || t == 0x51 || t == 0x61 || t == 0x71 || t == 0xF1 || t == 0x111 || t == 0x1001) {
        return 0;
    }
    func_002D6C90(0, 0, (s32)D_0037A880);
    return 0;
}
