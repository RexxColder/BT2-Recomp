#include "common.h"

void func_100ED0(s32 arg0, s32 arg1, s32 arg2);
s32 func_00100FC8(s32 arg0);
s32 func_002B24C8(s32 arg0, s32 arg1, s32 arg2);
void Res_RelocateOffsets(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_003879D0;

void func_00253EC8(void) {
    s32 base = D_003879D0;
    s32 state = *(s32 *)(base + 0x294);
    u8 sp[16];

    switch (state) {
    case 1: {
        s32 cur = *(s32 *)(base + 0x298);
        s32 val;
        s32 idx;
        s32 mode;

        if (cur != 0) {
            val = *(s32 *)(base + 0x204 + 20 * *(s32 *)(base + 0x274));
        } else {
            mode = *(s32 *)(base + 0x16C);
            if (mode == 0 || mode == 2) {
                idx = *(s32 *)(base + 0x168);
                val = *(s32 *)(base + 0x1A0 + 20 * idx);
                if (val < 0) {
                    val = 0;
                }
            } else {
                idx = *(s32 *)(base + 0x160);
                val = *(s32 *)(base + 0x174 + 8 * idx);
            }
        }
        func_100ED0(val + 0x56B, *(s32 *)(base + 0x8 + cur * 4), 1);
        func_00100FC8(1);
        *(s32 *)(base + 0x294) = 2;
        return;
    }
    case 2:
        if (func_00100FC8(0) != 0) {
            *(s32 *)(base + 0x294) = 3;
        }
        return;
    case 3: {
        s32 cur = *(s32 *)(base + 0x298);
        s32 nxt;
        s32 flags;
        s32 ptr;

        func_002B24C8(*(s32 *)(base + 0x8 + cur * 4), *(s32 *)(base + 0x10 + cur * 4), 0);
        ptr = *(s32 *)(base + 0x10 + cur * 4);
        *(s32 *)sp = ptr;
        Res_RelocateOffsets((s32)sp, ptr, ptr);
        ptr = *(s32 *)sp;
        if (cur != 0) {
            *(s32 *)(base + 0x98) = *(s32 *)(ptr + 0x10);
        } else {
            *(s32 *)(base + 0x94) = *(s32 *)(ptr + 0x10);
        }
        flags = *(s32 *)(base + 0x15C);
        flags = flags | (0x10 << cur);
        *(s32 *)(base + 0x15C) = flags;
        nxt = cur ^ 1;
        if ((flags & (4 << nxt)) != 0) {
            *(s32 *)(base + 0x298) = nxt;
            *(s32 *)(base + 0x294) = 6;
        } else {
            *(s32 *)(base + 0x294) = 4;
        }
        return;
    }
    case 4: {
        s32 flags = *(s32 *)(base + 0x15C);

        if ((flags & 4) != 0) {
            *(s32 *)(base + 0x298) = 0;
            *(s32 *)(base + 0x294) = 6;
        } else if ((flags & 8) != 0) {
            *(s32 *)(base + 0x298) = 1;
            *(s32 *)(base + 0x294) = 6;
        }
        return;
    }
    case 5: {
        s32 cur = *(s32 *)(base + 0x298);
        s32 nxt = cur ^ 1;
        s32 flags = *(s32 *)(base + 0x15C);

        if ((flags & (4 << nxt)) != 0) {
            *(s32 *)(base + 0x298) = nxt;
        }
        *(s32 *)(base + 0x294) = 6;
        return;
    }
    case 6: {
        s32 cur = *(s32 *)(base + 0x298);
        s32 bit = 4 << cur;
        s32 flags = *(s32 *)(base + 0x15C);

        if ((flags & bit) != 0) {
            *(s32 *)(base + 0x15C) = flags ^ bit;
        }
        *(s32 *)(base + 0x294) = 1;
        return;
    }
    default:
        return;
    }
}
