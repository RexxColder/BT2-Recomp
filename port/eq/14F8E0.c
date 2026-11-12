#include "common.h"

void func_0012A360(void *arg0, void *arg1, void *arg2, f32 farg0);
void func_00129C28(void *arg0, void *arg1);
s32 func_001CC978(u8 *arg0);
void func_001CC9E8(s32 arg0);
s32 func_001CCA38(s32 arg0);
void func_001CCAC8(s32 arg0, void *arg1);
void func_001CCB20(s32 arg0, s32 arg1);
void func_001CCB90(s32 arg0, f32 farg0);
void func_001CCBD8(s32 arg0, f32 farg0);
void func_001CCC20(s32 arg0, f32 farg0);
void func_001CCCC0(s32 arg0);
void func_001CCD10(s32 arg0, s32 arg1);
extern f32 D_0038462C;
extern f32 D_00384630;

/* 0x0014F8E0: effect-object driver. The 0x40-byte parameter block handed to func_001CC978 (asm: copy at sp+0x10) is
   {a6, obj[3], 0, a9 | vector from func_0012A360 | copy of a11 | a0+0x70, a2, a3, stale}; EftMod1CC_Init reads the pointer at +0x30. a0 = unit state, a1 = 0x1A-byte record (s16 at +0x18, bytes at +4, +7, +0x15),
   a4 = slot holding the object id, a5 = mode bits, a6 = a value copied into the parameter block, a7 = a
   parameter for func_0012A360, a9 / a10 = float scales, a11 = pointer to a 16-byte vector.
   Mode bit 1 creates the object when the slot is empty (func_001CC978, then setup calls); when the slot is
   empty after that, bit 8 is the only effect. Otherwise bit 8 scales a position (func_0012A360 / func_001CCAC8),
   bit 0x20 / 0x40 / 4 / 2 run the matching object calls, and bit 4 frees the slot. The asm leaves the last
   v0 as the return value; ctx.h says void, so this is void. */
void func_0014F8E0(u8 *a0, u8 *a1, s32 a2, s32 a3, s32 *a4, u32 a5, u32 a6, s32 a7,
                   f32 f12, f32 a9, f32 a10, s32 a11) {
    u8 v28[16];
    u8 blk[0x40];
    u8 *obj = a1;
    s32 *slot = a4;
    f32 sc;
    u64 w;

    (void)f12;

    if ((a5 & 1) != 0 && *slot == 0) {
        w = (u64)a6 | ((u64)obj[3] << 32);
        __builtin_memcpy(blk, &w, 8);
        *(s32 *)(blk + 0x8) = 0;
        *(f32 *)(blk + 0xC) = a9;
        __builtin_memset(blk + 0x10, 0, 16);
        __builtin_memset(blk + 0x20, 0, 16);
        *(u8 **)(blk + 0x30) = a0 + 0x70;
        *(s32 *)(blk + 0x34) = a2;
        *(s32 *)(blk + 0x38) = a3;
        *(s32 *)(blk + 0x3C) = 0;

        sc = ((f32)*(s16 *)(obj + 0x18) * D_0038462C) * a10;
        func_0012A360((void *)(blk + 0x10), (void *)a11, (void *)a7, sc);
        *(f32 *)(blk + 0x1C) = 1.0f;
        func_00129C28((void *)(blk + 0x20), (void *)a11);
        *slot = func_001CC978(blk);
        func_001CCBD8(*slot, (f32)obj[0x15]);
        func_001CCC20(*slot, (f32)obj[4]);
        if ((obj[7] & 0x20) != 0) {
            func_001CCCC0(*slot);
        }
        func_001CCD10(*slot, 1);
    }

    if (*slot == 0) {
        return;
    }

    if ((a5 & 8) != 0) {
        sc = ((f32)*(s16 *)(obj + 0x18) * D_00384630) * a10;
        func_0012A360((void *)v28, (void *)a11, (void *)a7, sc);
        *(f32 *)(v28 + 0xC) = 1.0f;
        func_001CCAC8(*slot, (void *)v28);
    }
    if ((a5 & 0x20) != 0) {
        func_001CCB90(*slot, a9);
    }
    if ((a5 & 0x40) != 0) {
        func_001CCB20(*slot, a11);
    }
    if ((a5 & 4) != 0) {
        (void)func_001CCA38(*slot);
        *slot = 0;
        return;
    }
    if ((a5 & 2) != 0) {
        func_001CC9E8(*slot);
    }
}
