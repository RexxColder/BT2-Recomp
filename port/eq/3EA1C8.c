#include "common.h"

extern u8 *D_00428F48 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 D_00428F50[] __attribute__((section(".data")));

void func_100ED0(s32 a0, s32 a1, s32 a2, u8 *a3);
s32 func_100FC8(s32 a0);
void func_2B24C8(s32 a0, u8 *a1, s32 a2);
void Res_RelocateOffsets(u8 *a0, u8 *a1, u8 *a2);

/* 0x003EA1C8: sibling of 0x003ECCA0 on P = D_00428F48 (state at P->0x1B8, cases 1..6 = switch on state - 1).
 * Case 1 copies D_00428F50 (0x44 bytes) to a frame buffer, then calls func_100ED0 and func_100FC8(1). */
void func_003EA1C8(void) {
    u8 *P = D_00428F48;
    u8 *G = D_3876A4;
    u8 buf[0x70];

    switch ((u32)(*(s32 *)(P + 0x1B8) - 1)) {
    case 0: {
        u8 *e;
        memcpy(buf, D_00428F50, 0x44);
        e = *(u8 **)(P + 0x10) + *(s32 *)(P + 0x19C) * 16;
        func_100ED0(*(s32 *)(buf + *(s32 *)(G + 0x484) * 4) + *(s32 *)(e + 0xC), *(s32 *)(P + 0x20), 1, P);
        func_100FC8(1);
        *(s32 *)(P + 0x1B8) = 2;
        break;
    }
    case 1:
        if (func_100FC8(0) != 0) {
            *(s32 *)(P + 0x1B8) = 3;
        }
        break;
    case 2:
        func_2B24C8(*(s32 *)(P + 0x20), *(u8 **)(P + 0x24), 0);
        *(u8 **)(buf + 0x60) = *(u8 **)(P + 0x24);
        Res_RelocateOffsets(buf + 0x60, *(u8 **)(P + 0x24), *(u8 **)(P + 0x24));
        *(s32 *)(P + 0x184) = *(s32 *)(*(u8 **)(buf + 0x60) + 0x10);
        *(s32 *)(P + 0x194) |= 0x40;
        *(s32 *)(P + 0x1B8) = 4;
        break;
    case 3:
        if (*(s32 *)(P + 0x194) & 0x20) {
            *(s32 *)(P + 0x1B8) = 6;
        }
        break;
    case 4:
        *(s32 *)(P + 0x1B8) = 6;
        break;
    case 5:
        if (*(s32 *)(P + 0x194) & 0x20) {
            *(s32 *)(P + 0x194) ^= 0x20;
        }
        *(s32 *)(P + 0x1B8) = 1;
        break;
    default:
        break;
    }
}
