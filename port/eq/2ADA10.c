#include "common.h"

void func_0025E1E8(void);
void func_00262428(void);
s32 func_002AD188(s32 arg0);
extern u8 D_003B2654[] __attribute__((section(".data")));

void func_002ADA10(void) {
    if (D_003B2654[0x18] != 0) {
        if (func_002AD188(*(s32 *)(D_003B2654 + 0x4)) != 3) {
            func_0025E1E8();
            func_00262428();
        }
    } else {
        func_0025E1E8();
        func_00262428();
    }
    D_003B2654[0x18] = 0;
}
