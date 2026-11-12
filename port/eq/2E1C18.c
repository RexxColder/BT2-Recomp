#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
s32 func_002E1A38(s32 arg0);
void func_002E1C98(s32 arg0, s32 arg1);

/* 0x002E1C18: if func_002E1A38(a0) is nonzero, tail-call func_002E1C98(0, 0xFF030204);
 * otherwise copy 20 bytes from a0+4 to a1 (unaligned 8+8+4 copy). */
void func_002E1C18(u8 *arg0, u8 *arg1) {
    if (func_002E1A38((s32)arg0) != 0) {
        func_002E1C98(0, 0xFF030204);
        return;
    }
    memcpy(arg1, arg0 + 4, 0x10);
    *(u32 *)(arg1 + 0x10) = *(u32 *)(arg0 + 0x14);
}
