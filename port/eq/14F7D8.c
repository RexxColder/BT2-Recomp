#include "common.h"

void func_00181760(s32 arg0, void *arg1);
void func_00181828(s32 arg0, f32 farg0);
void func_001817F8(s32 arg0, s32 arg1);
void func_001817A8(s32 arg0, s32 arg1);

/* 0x0014F7D8: arg0 = object (its +0x10 is passed on), arg1 = record (byte +3 and +4 read), arg2/arg5 ints, arg3 =
 * target, arg4 = flag word, arg6 = int, arg7 (f13) = float. When flag bit 1 is set: a 0x14-byte block {1, arg5,
 * arg1[3], arg2, arg0+0x10} is built and func_00181760(arg3, block) is called. Then func_001817F8(arg3, arg6) when
 * flags & 0xA, func_00181828(arg3, arg7) when flags & 0x20, and func_001817A8(arg3, arg1[4]) when flags & 2. */
void func_0014F7D8(u8 *arg0, u8 *arg1, s32 arg2, u8 *arg3, s32 arg4, s32 arg5, s32 arg6, f32 unusedF12, f32 arg7) {
    u8 blk[0x14] = {0};

    (void)unusedF12;
    if (arg4 & 1) {
        blk[0] = 1;
        *(s32 *)(blk + 0x4) = arg5;
        *(s32 *)(blk + 0x8) = arg1[3];
        *(s32 *)(blk + 0xC) = arg2;
        *(s32 *)(blk + 0x10) = (s32)(arg0 + 0x10);
        func_00181760((s32)arg3, blk);
    }
    if (arg4 & 0xA) {
        func_001817F8((s32)arg3, arg6);
    }
    if (arg4 & 0x20) {
        func_00181828((s32)arg3, arg7);
    }
    if (arg4 & 2) {
        func_001817A8((s32)arg3, arg1[4]);
    }
}
