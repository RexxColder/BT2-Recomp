#include "common.h"

extern s32 D_003876A0;
extern s32 gEftSurf;
extern void *memset(void *dst, s32 c, u32 n);
extern void *memcpy(void *dst, const void *src, u32 n);

s32 BtlPool_GetCurrent(void);
s32 BtlPool_Alloc(s32 arg0, s32 arg1);
void EftSurf_Relocate(s32 arg0);
void EftTexSet_Load34(s32 arg0, s32 arg1);
void GfxClut_InitPacket(u8 *arg0, s32 arg1, s32 arg2);
s32 func_002768D8(s32 arg0, s64 arg1, s32 arg2, s32 arg3);

/* 0x00135F50 (EftSurf setup). Allocates the 0x1380-byte surface record from the pool, lays out its pointers (the
 * block at base+0x40 or base, with the entry count at +0x18 and the entry table at +0x1C of the block at surf+4), and,
 * for every entry flagged with bit 0x800 while the record at +0x1114 has bit 0 clear, loads the texture set, the three
 * CLUT packets, and the entry's float parameters from the packet that func_002768D8 returns; then sets 0x1114 |= 9. */
void func_00135F50(void) {
    u8 *base = (u8 *)D_003876A0;
    u8 *s2;
    u8 *s0;
    u8 *s4;
    u8 *s5;
    u8 *surf;
    u8 *src;
    u8 *pk;
    s32 old34;
    s32 old28;
    s32 s1v;
    s32 count;
    s32 k;
    s32 flags20;
    s32 v1;
    s64 flagword;

    flagword = *(s64 *)(base + 0x4D8);
    s2 = *(u8 **)(base + 4);
    if ((flagword & ((s64)1 << 62)) != 0) {
        s2 = s2 + 0x40;
    }

    old34 = *(s32 *)(s2 + 0x34);
    s1v = *(s32 *)(s2 + 0x38) - old34;
    s0 = s2 + ((u32)old34 & ~3u);

    gEftSurf = (s32)BtlPool_Alloc(BtlPool_GetCurrent(), 0x1380);
    memset((void *)gEftSurf, 0, 0x1380);

    surf = (u8 *)gEftSurf;
    *(u8 **)(surf + 0) = s0;
    *(u8 **)(surf + 4) = s0 + 0x40;
    *(s32 *)(surf + 8) = s1v;

    EftSurf_Relocate((s32)*(u8 **)(surf + 4));
    s0 = surf + 0x240;

    src = *(u8 **)(surf + 4);
    count = *(s32 *)(src + 0x18);
    if (count <= 0) {
        return;
    }
    s4 = *(u8 **)(src + 0x1C);
    s5 = surf + 0x12C0;

    for (k = count; k != 0; k--) {
        flags20 = *(s32 *)(s4 + 0x20);
        s4 = s4 + 0x60;
        if ((flags20 & 0x800) == 0 || (*(s32 *)(s0 + 0x1114) & 1) != 0) {
            continue;
        }

        old28 = *(s32 *)(s2 + 0x28);
        EftTexSet_Load34((s32)(s0 + 0xE50), (s32)(s2 + ((u32)old28 & ~3u)));
        GfxClut_InitPacket(s0, 0x3E80, 0);
        GfxClut_InitPacket(s0 + 0x4C0, 0x3E84, 0);
        GfxClut_InitPacket(s0 + 0x980, 0x3E88, 0);

        v1 = *(s32 *)(s0 + 0x1070);
        *(s32 *)(s0 + 0x1108) = v1 - 4;
        *(s32 *)(s0 + 0x110C) = v1 - 2;
        *(s32 *)(s0 + 0x1104) = v1 - 4;

        src = *(u8 **)(surf + 0);
        memcpy(s5, src, 0x40);
        pk = (u8 *)(s32)func_002768D8(8, *(s64 *)(src + 0x28), *(s32 *)(src + 0x30), *(s32 *)(src + 0x38));

        *(f32 *)(s5 + 0) = (f32)pk[0x17];
        *(f32 *)(s0 + 0x1084) = (f32)pk[0x18];
        *(f32 *)(s0 + 0x1088) = (f32)pk[0x19];
        *(f32 *)(s0 + 0x108C) = (f32)pk[0x1A];
        *(f32 *)(s0 + 0x1090) = (f32)pk[0x1B];
        *(f32 *)(s0 + 0x1094) = (f32)pk[0x1C];
        *(f32 *)(s0 + 0x1098) = (f32)pk[0x1D];
        *(f32 *)(s0 + 0x109C) = (f32)pk[0x1E];
        *(f32 *)(s0 + 0x10A0) = *(f32 *)(pk + 0);
        *(f32 *)(s0 + 0x10A4) = *(f32 *)(pk + 4);
        *(f32 *)(s0 + 0x10A8) = *(f32 *)(pk + 8);
        *(f32 *)(s0 + 0x10AC) = 1.0f;
        *(f32 *)(s0 + 0x10B0) = *(f32 *)(pk + 0xC);
        *(s32 *)(s0 + 0x10B4) = *(u16 *)(pk + 0x14);
        if (*(f32 *)(pk + 0x10) == 0.0f) {
            *(f32 *)(s0 + 0x10B8) = 1000.0f;
        } else {
            *(f32 *)(s0 + 0x10B8) = *(f32 *)(pk + 0x10);
        }
        *(s32 *)(s0 + 0x1078) = (s32)(s0 + 0xE50);
        *(s32 *)(s0 + 0x1114) = *(s32 *)(s0 + 0x1114) | 9;
    }
}
