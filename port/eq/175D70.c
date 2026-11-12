#include "common.h"

f32 BtlCharApi_GetHeight(s32 arg0);
void Vec4_Set(void *dst, f32 x, f32 y, f32 z, f32 w);
void *EftGeyser_Create(void *param);
s32 func_001F3758(s32 arg0);
s32 func_0020B3D0(s32 arg0);
void func_0019D758(s32 arg0, s32 arg1);
void func_0019D7B0(s32 arg0, s32 arg1);
void func_0019D6B8(s32 arg0, s32 arg1);

/* 0x00175D70: create a geyser (particle column) for unit a0 in slot a1 (slot pointer at unit + 0xAC0 + 4 * a1).
   The parameter block S (0x90 bytes) is built from the unit and a 7-float template (3, 5, 0.5, 0.5, 0.1, 1, 2),
   copied to B, given the direction (0, -1, 0, 1) with Vec4_Set, and used for EftGeyser_Create. The height
   result only fed scratch stack slots (dead), so it is only called. */
void func_00175D70(s32 a0, s32 a1) {
    static const u32 tmpl[7] = {0x40400000, 0x40A00000, 0x3F000000, 0x3F000000,
                                0x3DCCCCCC, 0x3F800000, 0x40000000};
    u8 S[0x90];
    u8 B[0x90];
    u8 *unit = (u8 *)a0;
    s32 v3;
    u8 *v6;
    u8 *v7;
    u8 **slot;
    void *geyser;

    v3 = func_001F3758(a0);
    v6 = *(u8 **)(v3 + 0x38);
    v7 = *(u8 **)(unit + 0xC0);

    *(u32 *)(S + 0x00) = *(u32 *)(v6 + 0x1E84);
    *(u32 *)(S + 0x04) = 0;
    *(u8 **)(S + 0x08) = v7;
    *(u8 **)(S + 0x0C) = v6;
    *(u8 **)(S + 0x10) = unit + 0x870;
    __builtin_memcpy(S + 0x14, tmpl, sizeof(tmpl));
    *(f32 *)(S + 0x30) = 128.0f;
    *(f32 *)(S + 0x34) = 128.0f;
    *(f32 *)(S + 0x38) = 128.0f;
    *(f32 *)(S + 0x3C) = 128.0f;
    *(u64 *)(S + 0x40) = *(u64 *)(unit + 0x70);
    *(u64 *)(S + 0x48) = *(u64 *)(unit + 0x78);
    *(u64 *)(S + 0x50) = *(u64 *)(unit + 0xB0);
    *(u64 *)(S + 0x58) = *(u64 *)(unit + 0xB8);
    __builtin_memset(S + 0x60, 0, 16);
    *(f32 *)(S + 0x70) = *(f32 *)(unit + 0x14);
    *(f32 *)(S + 0x74) = *(f32 *)(unit + 0x1C);
    *(u32 *)(S + 0x78) = 0;
    *(u32 *)(S + 0x7C) = 0;
    *(u32 *)(S + 0x80) = *(u32 *)v7;

    __builtin_memcpy(B, S, sizeof(S));
    (void)BtlCharApi_GetHeight(func_0020B3D0(*(s32 *)v7));
    Vec4_Set((void *)(B + 0x60), 0.0f, -1.0f, 0.0f, 1.0f);
    geyser = EftGeyser_Create((void *)B);

    slot = (u8 **)(unit + 0xAC0 + 4 * a1);
    *slot = (u8 *)geyser;
    func_0019D758((s32)geyser, 0);
    func_0019D7B0((s32)*slot, (s32)S);
    func_0019D6B8((s32)*slot, 4);
}
