#include "common.h"

/* 0x002100C0: for 0 <= arg1 < 0x20 (unsigned compare), set bit (arg1 & 7) of byte (arg1 >> 3) of the bit table at
 * arg0 + 0x360. Other values do nothing. */
void func_002100C0(u8 *arg0, s32 arg1) {
    if ((u32)arg1 < 0x20) {
        arg0[0x360 + (arg1 >> 3)] = (u8)(arg0[0x360 + (arg1 >> 3)] | (1 << (arg1 & 7)));
    }
}
