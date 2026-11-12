#include "common.h"

/* 0x00237DD0: func_002113C0(a0, 2, 0x100, 1); if (!(*(u32 *)(a0 + 0x8DC) & 1)) tail func_00237088(a0).
 * Otherwise returns the stale masked bit (1). */
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00237088(s32 arg0);

s32 func_00237DD0(u8 *a0) {
    u32 bit;

    func_002113C0((s32)a0, 2, 0x100, 1);
    bit = *(u32 *)(a0 + 0x8DC) & 1;
    if (bit == 0) {
        return func_00237088((s32)a0);
    }
    return bit;
}
