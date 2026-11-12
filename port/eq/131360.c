#include "common.h"

s32 BtlPool_GetCurrent(s32 arg0);
s32 BtlPool_Alloc(s32 arg0, s32 arg1);
s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
s32 EftTexSet_Load32(s32 arg0, s32 arg1);
void Vec4_Set(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_00129C28(s32 arg0, s32 arg1);
void EftFlash_StartOwned(s32 arg0);
void *func_002768D8(s32 arg0);
void *func_002769B8(void);
void *memset(void *arg0, s32 arg1, s32 arg2);
extern u8 *D_003876A0;
extern u8 *gEftFlash;

void func_00131360(s32 arg0) {
    u8 sp[0x70];
    u8 *base;
    u8 *s0;
    u8 *hdr;
    u8 *p;
    s32 s2;
    s32 r;

    base = *(u8 **)(D_003876A0 + 4);
    gEftFlash = (u8 *)BtlPool_Alloc(BtlPool_GetCurrent(arg0), 0x210);
    memset((s32)gEftFlash, 0, 0x210);
    r = BtlTask_CreateChildList(arg0, 0xA, 0x100);
    *(s32 *)gEftFlash = r;
    if (*(s64 *)(D_003876A0 + 0x4D8) & ((s64)0x8000 << 47)) {
        base = *(u8 **)(D_003876A0 + 4) + 0x40;
    }
    EftTexSet_Load32((s32)(gEftFlash + 8),
                     (s32)(base + ((u32)*(s32 *)(base + 0x48) & ~3u)));
    hdr = (u8 *)func_002768D8(0xA);
    if (hdr != 0) {
        s2 = 0;
        p = (u8 *)func_002769B8();
        if (hdr[1] != 0) {
            s0 = p;
            do {
                s2 += 1;
                memset(sp, 0, 0x70);
                Vec4_Set((s32)(sp + 0x20), (f32)s0[0x1E], (f32)s0[0x1F],
                         (f32)s0[0x20], (f32)s0[0x21]);
                func_00129C28((s32)(sp + 0x30), (s32)(sp + 0x20));
                *(f32 *)(sp + 0x40) = *(f32 *)(s0 + 0xC);
                *(f32 *)(sp + 0x44) = *(f32 *)(s0 + 0x10);
                *(f32 *)(sp + 0x48) = 1.0f;
                *(f32 *)(sp + 0x4C) = 1.0f;
                *(f32 *)(sp + 0x50) = 2.0f;
                *(f32 *)(sp + 0x54) = *(f32 *)(s0 + 0x14);
                *(s32 *)(sp + 0x58) = *(u16 *)(s0 + 0x18);
                *(s32 *)(sp + 0x5C) = *(u16 *)(s0 + 0x1A);
                *(s32 *)(sp + 0x60) = *(u16 *)(s0 + 0x1C);
                *(f32 *)(sp + 0x0) = *(f32 *)(s0 + 0x0);
                *(f32 *)(sp + 0x4) = *(f32 *)(s0 + 0x4);
                *(f32 *)(sp + 0x8) = *(f32 *)(s0 + 0x8);
                *(f32 *)(sp + 0xC) = 1.0f;
                s0 += 0x30;
                func_00129C28((s32)(sp + 0x10), (s32)sp);
                *(f32 *)(sp + 0x14) = *(f32 *)(sp + 0x4) + *(f32 *)(sp + 0x44);
                EftFlash_StartOwned((s32)sp);
            } while (s2 < hdr[1]);
        }
    }
}
