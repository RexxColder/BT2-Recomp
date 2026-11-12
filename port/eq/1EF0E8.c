#include "common.h"

extern u8 *D_00387AD8;
extern u8 *gOtFirst;

/* 0x001EF0E8: GS packet builder for a 0x30-byte packet at the cursor D_00387AD8 (advanced by 0x30).
 * The 64-bit word at +0x20 keeps its bits and takes the fields: bit 0 from arg0, bits 2..4 from
 * arg1 (low 3 bits, shifted by 2), bit 5 from arg2, bits 6..8 from arg3 (low 3 bits, shifted by 6),
 * bit 9 from arg4, bit 15 from arg5, and bits 32..43 from arg6 (low 12 bits). Words +0x00 (0xA0000002),
 * +0x10 (0x1000000000008001), +0x18 (0xE) and +0x28 (sign-extended arg7 plus 0x14) are written, and
 * the packet is linked into the list head gOtFirst. Nothing is written when the cursor is NULL. */
void func_001EF0E8(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6, u32 arg7) {
    u8 *pk = D_00387AD8;
    u64 v0;
    u64 v1;

    D_00387AD8 = pk + 0x30;
    if (pk == NULL) {
        return;
    }

    v0 = *(u64 *)(pk + 0x20);
    v0 &= ~(u64)0x2;
    v0 |= (u64)(arg0 & 1);
    v0 &= ~(u64)0x1C;
    v0 |= (u64)((arg1 & 7) << 2);
    v0 &= ~(u64)0x20;
    v0 |= (u64)((arg2 & 1) << 5);
    v0 &= ~(u64)0x1C0;
    v0 |= (u64)((arg3 & 7) << 6);
    v0 &= ~(u64)0x200;
    v0 |= (u64)((arg4 & 1) << 9);
    v0 &= ~(u64)0x8000;
    v0 |= (u64)((arg5 & 1) << 15);
    v0 &= 0xFFFFF000FFFFFFFFULL;
    v0 |= (u64)((arg6 & 0xFFF)) << 32;

    v1 = (u64)((s64)(s8)arg7 + 0x14);

    *(u64 *)(pk + 0x00) = 0xA0000002ULL;
    *(u64 *)(pk + 0x10) = 0x1000000000008001ULL;
    *(u64 *)(pk + 0x18) = 0xE;
    *(u64 *)(pk + 0x28) = v1;
    *(u64 *)(pk + 0x20) = v0;

    {
        u8 *first = gOtFirst;
        u8 *n = *(u8 **)(first + 0x4);

        *(u8 **)(n + 0x4) = pk;
        *(u8 **)(first + 0x4) = pk;
    }
}
