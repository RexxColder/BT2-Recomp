#include "common.h"

void func_002EA050(s32 arg0);
extern u8 D_0037BA58[] __attribute__((section(".data")));

/* 0x002E7AC8: b = (s8)arg0[+0xE]; if b == 1 and arg0[+0xE8] != 0 return 2; if arg0 != NULL return b; otherwise
 * func_002EA050(&D_0037BA58) and return -1. */
s32 func_002E7AC8(u8 *arg0) {
    s8 b = *(s8 *)(arg0 + 0xE);

    if (b == 1) {
        if (*(s32 *)(arg0 + 0xE8) != 0) {
            return 2;
        }
    }
    if (arg0 != NULL) {
        return b;
    }
    func_002EA050((s32)D_0037BA58);
    return -1;
}
