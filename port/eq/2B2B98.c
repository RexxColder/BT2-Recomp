#include "common.h"

void func_002B2B98(u8 *arg0, u8 *arg1) {
    s32 i;

    for (i = 0; i < 32; i++) {
        u16 a = *(u16 *)(arg0 + 0xA + 2 * i);
        u16 b = *(u16 *)(arg1 + 0x40 + 2 * i);
        u16 *d = (u16 *)(arg1 + 2 * i);

        *d = (u16)(*d ^ (a ^ b));
    }
}
