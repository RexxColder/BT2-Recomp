#include "common.h"

f32 func_00241FA0(s32 arg0, s32 arg1);
f32 func_00241FC0(s32 arg0, s32 arg1);
f32 func_00241AB0(s32 arg0, s32 arg1);
f32 func_00241218(s32 arg0, s32 arg1);
f32 func_00241660(s32 arg0, s32 arg1);
f32 func_002416B0(s32 arg0, s32 arg1);
void func_00147FE8(s32 arg0);

/* 0x00204478: picks the highest of the flag bits 51..55 of the 64-bit word at +0x338 as a level
 * s0 (0..4; -1 when none is set) and returns if there is none. Otherwise a 0x20-byte frame gets
 * the two table words (+0x1534, and +0x9F0 of the block at +0x1530) and the level, followed by
 * floats from the level functions: for level 0 or 1 from func_00241FA0 and func_00241FC0, for
 * levels 2..4 from func_00241AB0, func_00241218, func_00241660 and func_002416B0. Then func_00147FE8
 * is called on the frame. */
void func_00204478(u8 *arg0) {
    s64 a1 = *(s64 *)(arg0 + 0x338);
    s32 s0 = -1;
    s32 sp[8];

    if ((a1 & ((s64)1 << 51)) != 0) {
        s0 = 0;
    }
    if ((a1 & ((s64)1 << 52)) != 0) {
        s0 = 1;
    }
    if ((a1 & ((s64)1 << 53)) != 0) {
        s0 = 2;
    }
    if ((a1 & ((s64)1 << 54)) != 0) {
        s0 = 3;
    }
    if ((a1 & ((s64)1 << 55)) != 0) {
        s0 = 4;
    }
    if (s0 < 0) {
        return;
    }

    sp[0] = *(s32 *)(arg0 + 0x1534);
    sp[1] = s0;
    sp[2] = *(s32 *)(*(u8 **)(arg0 + 0x1530) + 0x9F0);

    if (s0 < 2) {
        *(f32 *)&sp[3] = func_00241FA0((s32)arg0, s0);
        sp[4] = 0;
        *(f32 *)&sp[5] = func_00241FC0((s32)arg0, s0);
        sp[6] = 0;
    } else if (s0 < 5) {
        *(f32 *)&sp[3] = func_00241AB0((s32)arg0, s0);
        *(f32 *)&sp[4] = func_00241218((s32)arg0, s0);
        *(f32 *)&sp[5] = func_00241660((s32)arg0, s0);
        *(f32 *)&sp[6] = func_002416B0((s32)arg0, s0);
    }

    func_00147FE8((s32)sp);
}
