#include "common.h"

extern u8 *D_0042BB74 __attribute__((section(".data")));

void func_100ED0(s32 a0, s32 a1, s32 a2, u8 *a3);
s32 func_100FC8(s32 a0);
u8 *func_2B24C8(u8 *a0, u8 *a1, s32 a2);
void Res_RelocateOffsets(u8 *a0, u8 *a1, u8 *a2);

/* 0x00405898: state machine on X = D_0042BB74 (state at X->0x36C0 in 1..6; slot at X->0x20C; flags at X->0x210).
 * B = X + 4 * slot. Same shape as 0x003F0800 with the field offsets moved: state 1 loads from B->0x260 and calls
 * func_100ED0(... , B) / func_100FC8(1); 2 waits on func_100FC8(0); 3 relocates B->0x8/0x10 and stores the word to
 * X->0x120 (slot 0) or X->0x124; 4 and 6 flip flags; 5 toggles the slot. */
void func_00405898(void) {
    u8 *X;
    u8 *B;
    u8 *base;
    u8 *out;
    s32 slot;
    s32 st;
    s32 p;
    s32 bit;
    s32 val;
    s32 t0;
    s32 a3v;
    u8 frame[0x10];

    X = D_0042BB74;
    st = *(s32 *)(X + 0x36C0);
    switch ((u32)(st - 1)) {
    case 0:
        slot = *(s32 *)(X + 0x20C);
        B = X + slot * 4;
        a3v = *(s32 *)(B + 0x21C);
        t0 = *(s32 *)(B + 0x214);
        base = *(u8 **)(B + 0x260);
        val = *(s32 *)(base + (a3v * 7 + t0) * 44);
        *(s32 *)(B + 0x244) = val;
        func_100ED0(val + 0x56B, *(s32 *)(B + 0x8), 1, B);
        func_100FC8(1);
        *(s32 *)(X + 0x36C0) = 2;
        break;
    case 1:
        if (func_100FC8(0) != 0) {
            *(s32 *)(X + 0x36C0) = 3;
        }
        break;
    case 2:
        slot = *(s32 *)(X + 0x20C);
        B = X + slot * 4;
        func_2B24C8(*(u8 **)(B + 0x8), *(u8 **)(B + 0x10), 0);
        *(u8 **)frame = *(u8 **)(B + 0x10);
        Res_RelocateOffsets(frame, *(u8 **)(B + 0x10), *(u8 **)(B + 0x10));
        out = *(u8 **)frame;
        if (*(s32 *)(X + 0x20C) != 0) {
            *(s32 *)(X + 0x124) = *(s32 *)(out + 0x10);
        } else {
            *(s32 *)(X + 0x120) = *(s32 *)(out + 0x10);
        }
        *(s32 *)(X + 0x210) = *(s32 *)(X + 0x210) | (0x40 << (*(s32 *)(X + 0x20C) & 31));
        p = *(s32 *)(X + 0x20C) ^ 1;
        bit = (*(s32 *)(X + 0x210) >> (p & 31)) & 1;
        if (bit != 0) {
            *(s32 *)(X + 0x20C) = p;
            *(s32 *)(X + 0x36C0) = 6;
        } else {
            *(s32 *)(X + 0x36C0) = 4;
        }
        break;
    case 3:
        if (*(s32 *)(X + 0x210) & 1) {
            *(s32 *)(X + 0x20C) = 0;
            *(s32 *)(X + 0x36C0) = 6;
        } else if (*(s32 *)(X + 0x210) & 2) {
            *(s32 *)(X + 0x20C) = 1;
            *(s32 *)(X + 0x36C0) = 6;
        }
        break;
    case 4:
        p = *(s32 *)(X + 0x20C) ^ 1;
        bit = (*(s32 *)(X + 0x210) >> (p & 31)) & 1;
        if (bit != 0) {
            *(s32 *)(X + 0x20C) = p;
        }
        *(s32 *)(X + 0x36C0) = 6;
        break;
    case 5:
        bit = (*(s32 *)(X + 0x210) >> (*(s32 *)(X + 0x20C) & 31)) & 1;
        if (bit != 0) {
            *(s32 *)(X + 0x210) = *(s32 *)(X + 0x210) ^ (1 << (*(s32 *)(X + 0x20C) & 31));
        }
        *(s32 *)(X + 0x36C0) = 1;
        break;
    default:
        break;
    }
}
