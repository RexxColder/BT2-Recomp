#include "common.h"

/* 0x0020FC38: for 0 <= arg1 < 0x80 (unsigned compare), set bit (arg1 & 7) of byte (arg1 >> 3) of the bit table at
 * arg0 + 0x340. Other values do nothing. */
void func_0020FC38(u8 *arg0, s32 arg1) {
    if ((u32)arg1 < 0x80) {
        arg0[0x340 + (arg1 >> 3)] = (u8)(arg0[0x340 + (arg1 >> 3)] | (1 << (arg1 & 7)));
    }
}
