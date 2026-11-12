#include "common.h"

#define SF(off) (*(f32 *)(sp + (off)))
#define SI(off) (*(s32 *)(sp + (off)))

extern u8 *D_003876A0;
extern f32 D_003842F8;
extern s32 *gEftSteam;

void *memset(void *, s32, u32);
s32 *BtlPool_Alloc(s32 arg0, s32 arg1);
s32 BtlPool_GetCurrent(void);
s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
void EftTexSet_Load32(s32 arg0, s32 arg1);
void *func_002768D8(s32 arg0);
void *func_00276A28(void);
void func_0013A438(u8 *arg0);

void func_0013A5B0(s32 arg0) {
    u8 sp[0x60];
    u8 *s1;
    u8 *s0;
    u8 *e;
    s32 s2;

    s1 = *(u8 **)(D_003876A0 + 4);
    gEftSteam = BtlPool_Alloc(BtlPool_GetCurrent(), 0x210);
    memset(gEftSteam, 0, 0x210);
    *gEftSteam = BtlTask_CreateChildList(arg0, 0xB, 0xC80);
    if ((*(s64 *)(D_003876A0 + 0x4D8) & ((s64)0x8000 << 47)) != 0) {
        s1 = *(u8 **)(D_003876A0 + 4) + 0x40;
    }
    EftTexSet_Load32((s32)((u8 *)gEftSteam + 8),
                     (s32)(s1 + ((*(u32 *)(s1 + 0x48) >> 2) * 4)));
    {
        u8 *cnt = func_002768D8(0xC);
        if (cnt != NULL) {
            s2 = 0;
            e = func_00276A28();
            if (cnt[1] != 0) {
                s0 = e;
                do {
                    s2 += 1;
                    memset(sp, 0, 0x60);
                    SF(0x00) = *(f32 *)(s0 + 0x0);
                    SF(0x04) = *(f32 *)(s0 + 0x4);
                    SF(0x08) = *(f32 *)(s0 + 0x8);
                    SF(0x0C) = 1.0f;
                    SI(0x10) = 0;
                    SF(0x14) = -1.0f;
                    SI(0x18) = 0;
                    SF(0x1C) = 1.0f;
                    SF(0x20) = (f32)s0[0x1A];
                    SF(0x24) = (f32)s0[0x1B];
                    SF(0x28) = (f32)s0[0x1C];
                    SF(0x2C) = (f32)s0[0x1D];
                    SF(0x30) = *(f32 *)(s0 + 0xC);
                    SF(0x34) = *(f32 *)(s0 + 0x10);
                    SF(0x38) = *(f32 *)(s0 + 0x14);
                    SI(0x3C) = *(u16 *)(s0 + 0x18);
                    SF(0x40) = 1.0f;
                    SF(0x44) = D_003842F8;
                    SF(0x48) = 1.0f;
                    SF(0x4C) = 0.5f;
                    SI(0x50) = 5;
                    func_0013A438(sp);
                    s0 += 0x30;
                } while (s2 < cnt[1]);
            }
        }
    }
}
