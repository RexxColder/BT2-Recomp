#include "common.h"

s32 func_003126C8(s32 arg0, u8 *arg1);
extern u8 D_003885F0[] __attribute__((section(".data")));

s32 func_0011E2D0(s32 arg0) {
    if (D_003885F0[0xC8] == 0) {
        return 0;
    }
    func_003126C8(arg0, D_003885F0 + 0x90);
    return 1;
}
