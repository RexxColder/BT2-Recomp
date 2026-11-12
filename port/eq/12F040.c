#include "common.h"

extern u8 *D_00387AD8;
extern u8 *D_00387AE4;

/* 0x0012F040: GS packet builder. Writes one 0xC0-byte packet at the cursor D_00387AD8 (which then
 * advances by 0xC0): a 0xA000000B header, the tag word 0x100000000000800A, arg0 (low half) with
 * arg4 (high half) and arg3 / (arg1 >> 6) in the 0x20 word, the fixed register-set words, and the
 * (arg1 - 1, arg2 - 1) pair in the 0x70 word; the packet is then linked from the list head
 * D_00387AE4 (its +4 link is set to the packet). */
void func_0012F040(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4) {
    u8 *pk = D_00387AD8;
    u64 a0w = (u64)arg0 | ((u64)arg4 << 32);
    u64 a3w = ((u64)arg3 << 24) | ((u64)(arg1 >> 6) << 16);
    u64 t8 = a0w | a3w;
    u64 a1w = (u64)(arg1 - 1) << 16;
    u64 a2w = (u64)(arg2 - 1) << 48;
    u8 *link;

    D_00387AD8 = pk + 0xC0;

    *(u64 *)(pk + 0x00) = 0xA000000B;
    *(u64 *)(pk + 0x10) = (u64)0x100000000000800AULL;
    *(u64 *)(pk + 0x18) = 0xE;
    *(u64 *)(pk + 0x20) = t8;
    *(u64 *)(pk + 0x28) = 0x4C;
    *(u64 *)(pk + 0x30) = 0x131000158ULL;
    *(u64 *)(pk + 0x38) = 0x4E;
    *(u64 *)(pk + 0x40) = 0;
    *(u64 *)(pk + 0x48) = 0x4A;
    *(u64 *)(pk + 0x50) = 0x30003ULL;
    *(u64 *)(pk + 0x58) = 0x47;
    *(u64 *)(pk + 0x60) = 0x00007C8000007C00ULL;
    *(u64 *)(pk + 0x68) = 0x18;
    *(u64 *)(pk + 0x70) = a1w | a2w;
    *(u64 *)(pk + 0x78) = 0x40;
    *(u64 *)(pk + 0x80) = 1;
    *(u64 *)(pk + 0x88) = 0x46;
    *(u64 *)(pk + 0x90) = 0x44;
    *(u64 *)(pk + 0x98) = 0x42;
    *(u64 *)(pk + 0xA0) = 0;
    *(u64 *)(pk + 0xA8) = 0x14;
    *(u64 *)(pk + 0xB0) = 0;
    *(u64 *)(pk + 0xB8) = 0x3F;

    link = *(u8 **)(D_00387AE4 + 0x4);
    *(u8 **)(link + 0x4) = pk;
    *(u8 **)(D_00387AE4 + 0x4) = pk;
}
