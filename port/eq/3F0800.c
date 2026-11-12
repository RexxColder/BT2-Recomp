#include "common.h"

extern u8 *D_0042A570 __attribute__((section(".data")));

void func_100ED0(s32 a0, s32 a1, s32 a2, s32 a3);
s32 func_100FC8(s32 a0);
u8 *func_2B24C8(u8 *a0, u8 *a1, s32 a2);
void Res_RelocateOffsets(u8 *a0, u8 *a1, u8 *a2);

/* 0x003F0800: state machine on X = D_0042A570 (state at X->0x36B8, 1..6; flags at X->0x218, slot index at X->0x210
 * with B = X + 4 * slot). State 1 fills X->0x24C from a table and calls func_100ED0 / func_100FC8(1); 2 waits on
 * func_100FC8(0); 3 relocates a word (out to X->0x124 or X->0x13C) and toggles slot bits; 4 and 6 flip flags; 5 toggles
 * the slot. */
void func_003F0800(void) {
    u8 *X;
    s32 st;
    s32 idx;
    s32 bit;
    s32 p;
    s32 val;
    s32 a3v;
    s32 t1;
    u8 *base2;
    u8 *B;
    u8 frame[0x10];

    X = D_0042A570;
    st = *(s32 *)(X + 0x36B8);
    switch ((u32)(st - 1)) {
    case 0:
        idx = *(s32 *)(X + 0x210);
        B = X + idx * 4;
        a3v = *(s32 *)(B + 0x224);
        t1 = *(s32 *)(X + idx * 4 + 0x21C);
        base2 = *(u8 **)(B + 0x258);
        val = *(s32 *)(base2 + (a3v * 7 + t1) * 44);
        *(s32 *)(X + idx * 4 + 0x24C) = val;
        func_100ED0(val + 0x56B, *(s32 *)(B + 0x8), 1, a3v);
        func_100FC8(1);
        *(s32 *)(X + 0x36B8) = 2;
        break;
    case 1:
        if (func_100FC8(0) != 0) {
            *(s32 *)(X + 0x36B8) = 3;
        }
        break;
    case 2:
        idx = *(s32 *)(X + 0x210);
        B = X + idx * 4;
        func_2B24C8(*(u8 **)(B + 0x8), *(u8 **)(B + 0x10), 0);
        *(u8 **)frame = *(u8 **)(B + 0x10);
        Res_RelocateOffsets(frame, *(u8 **)(B + 0x10), *(u8 **)(B + 0x10));
        val = *(s32 *)(*(u8 **)frame + 0x10);
        if (*(s32 *)(X + 0x210) == 0) {
            *(s32 *)(X + 0x124) = val;
        } else {
            *(s32 *)(X + 0x13C) = val;
        }
        *(s32 *)(X + 0x218) = *(s32 *)(X + 0x218) | (0x40 << (*(s32 *)(X + 0x210) & 31));
        p = *(s32 *)(X + 0x210) ^ 1;
        bit = (*(s32 *)(X + 0x218) >> (p & 31)) & 1;
        if (bit != 0) {
            *(s32 *)(X + 0x210) = p;
            *(s32 *)(X + 0x36B8) = 6;
        } else {
            *(s32 *)(X + 0x36B8) = 4;
        }
        break;
    case 3:
        if (*(s32 *)(X + 0x218) & 1) {
            *(s32 *)(X + 0x210) = 0;
            *(s32 *)(X + 0x36B8) = 6;
        } else if (*(s32 *)(X + 0x218) & 2) {
            *(s32 *)(X + 0x210) = 1;
            *(s32 *)(X + 0x36B8) = 6;
        }
        break;
    case 4:
        p = *(s32 *)(X + 0x210) ^ 1;
        bit = (*(s32 *)(X + 0x218) >> (p & 31)) & 1;
        if (bit != 0) {
            *(s32 *)(X + 0x210) = p;
        }
        *(s32 *)(X + 0x36B8) = 6;
        break;
    case 5:
        bit = (*(s32 *)(X + 0x218) >> (*(s32 *)(X + 0x210) & 31)) & 1;
        if (bit != 0) {
            *(s32 *)(X + 0x218) = *(s32 *)(X + 0x218) ^ (1 << (*(s32 *)(X + 0x210) & 31));
        }
        *(s32 *)(X + 0x36B8) = 1;
        break;
    default:
        break;
    }
}
