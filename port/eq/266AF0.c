#include "common.h"

s32 rand(void);

/* 0x00266AF0: per-particle state step. arg0 is the emitter block (flags word at +0xAF0, a 64-bit
 * copy of it is tested against 0x10000002), arg1 the particle record: +0 a countdown (re-armed
 * with rand() % 90 + 0x5A when it runs below zero), +4 a second timer (re-armed to rand() % 3 + 3
 * at that point; stepped down while positive, zeroed when negative). The state word at +8 is
 * then 0, 1 or 2 (2 when the flags test passes and the word at arg0+0x54 is at least 2). Flag bit
 * 0x04000000 copies +0xC to +8 and returns; bit 0x08000000 skips the timers. */
void func_00266AF0(u8 *arg0, u8 *arg1) {
    s32 flags = *(s32 *)(arg0 + 0xAF0);
    s32 c;
    s32 t;

    if ((flags & 0x04000000) != 0) {
        *(s32 *)(arg1 + 0x8) = *(s32 *)(arg1 + 0xC);
        return;
    }

    if ((flags & 0x08000000) == 0) {
        c = *(s32 *)(arg1 + 0x0);
        *(s32 *)(arg1 + 0x0) = c - 1;
        if (c < 0) {
            *(s32 *)(arg1 + 0x4) = (rand() % 3) + 3;
            *(s32 *)(arg1 + 0x0) = (rand() % 90) + 0x5A;
        }

        t = *(s32 *)(arg1 + 0x4);
        if (t == 0) {
            *(s32 *)(arg1 + 0x8) = 0;
            return;
        }
        if (t < 0) {
            *(s32 *)(arg1 + 0x4) = 0;
            *(s32 *)(arg1 + 0x8) = 0;
            return;
        }
        *(s32 *)(arg1 + 0x4) = t - 1;
    }

    {
        s64 f64 = *(s64 *)(arg0 + 0xAF0);

        if ((f64 & 0x10000002) != 0x10000002) {
            *(s32 *)(arg1 + 0x8) = 1;
        } else if (*(u32 *)(*(u8 **)(arg0 + 0x54)) < 2) {
            *(s32 *)(arg1 + 0x8) = 1;
        } else {
            *(s32 *)(arg1 + 0x8) = 2;
        }
    }
}
