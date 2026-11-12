#include "common.h"

extern u8 *D_00428F4C __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 D_00429A90[] __attribute__((section(".data")));

void func_100ED0(s32 a0, s32 a1, s32 a2, u8 *a3);
s32 func_100FC8(s32 a0);
void func_2B24C8(s32 a0, u8 *a1, s32 a2);
void Res_RelocateOffsets(u8 *a0, u8 *a1, u8 *a2);

/* 0x003ECCA0: loader state machine on P = D_00428F4C, state at P->0x1EC, cases 1..6 (switch on state - 1).
 * Case 1 copies D_00429A90 (0x44 bytes) to a frame buffer and calls func_100ED0 / func_100FC8(1). */
void func_003ECCA0(void) {
    u8 *P = D_00428F4C;
    u8 *Q = D_3876A4;
    u8 buf[0x60];

    switch ((u32)(*(s32 *)(P + 0x1EC) - 1)) {
    case 0: {
        s32 idx;
        u8 *e;
        memcpy(buf, D_00429A90, 0x44);
        idx = *(s32 *)(Q + 0x484);
        e = *(u8 **)(P + 0x1C8) + *(s32 *)(P + 0x1A4) * 8;
        func_100ED0(*(s32 *)(buf + idx * 4) + *(s32 *)(e + 4), *(s32 *)(P + 0x1C), 1, P);
        func_100FC8(1);
        *(s32 *)(P + 0x1EC) = 2;
        break;
    }
    case 1:
        if (func_100FC8(0) != 0) {
            *(s32 *)(P + 0x1EC) = 3;
        }
        break;
    case 2:
        func_2B24C8(*(s32 *)(P + 0x1C), *(u8 **)(P + 0x20), 0);
        *(u8 **)(buf + 0x50) = *(u8 **)(P + 0x20);
        Res_RelocateOffsets(buf + 0x50, *(u8 **)(P + 0x20), *(u8 **)(P + 0x20));
        *(s32 *)(P + 0x140) = *(s32 *)(*(u8 **)(buf + 0x50) + 0x10);
        *(s32 *)(P + 0x174) |= 0x80;
        *(s32 *)(P + 0x1EC) = 4;
        break;
    case 3:
        if (*(s32 *)(P + 0x174) & 0x40) {
            *(s32 *)(P + 0x1EC) = 6;
        }
        break;
    case 4:
        *(s32 *)(P + 0x1EC) = 6;
        break;
    case 5:
        if (*(s32 *)(P + 0x174) & 0x40) {
            *(s32 *)(P + 0x174) ^= 0x40;
        }
        *(s32 *)(P + 0x1EC) = 1;
        break;
    default:
        break;
    }
}
