#include "common.h"

s32 BtlPool_GetCurrent(s32 arg0);
s32 BtlPool_Alloc(s32 arg0, s32 arg1);
s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
s32 EftTexSet_Load32(s32 arg0, s32 arg1);
s32 func_001437A8(s32 arg0);
void *func_002768D8(s32 arg0);
void *func_002769F0(void);
s32 memset(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_003876A0;
extern u8 *gEftSmokeMgr;

void func_001438C8(s32 arg0) {
    u8 sp[0x50];
    u8 *s0;
    u8 *hdr;
    u8 *p;
    s32 s2;
    s32 r;

    s0 = *(u8 **)(D_003876A0 + 4);
    gEftSmokeMgr = (u8 *)BtlPool_Alloc(BtlPool_GetCurrent(arg0), 0x210);
    memset((s32)gEftSmokeMgr, 0, 0x210);
    if (*(s64 *)(D_003876A0 + 0x4D8) & ((s64)0x8000 << 47)) {
        s0 = *(u8 **)(D_003876A0 + 4) + 0x40;
    }
    EftTexSet_Load32((s32)(gEftSmokeMgr + 8),
                     (s32)(s0 + ((u32)*(s32 *)(s0 + 0x48) & ~3u)));
    r = BtlTask_CreateChildList(arg0, 0x11, 0x7F0);
    *(s32 *)gEftSmokeMgr = r;

    hdr = (u8 *)func_002768D8(0xB);
    if (hdr != 0) {
        s2 = 0;
        p = (u8 *)func_002769F0();
        if (hdr[1] != 0) {
            s0 = p;
            do {
                s2 += 1;
                memset((s32)sp, 0, 0x50);
                *(f32 *)(sp + 0x0) = *(f32 *)(s0 + 0x0);
                *(f32 *)(sp + 0x4) = *(f32 *)(s0 + 0x4);
                *(f32 *)(sp + 0x8) = *(f32 *)(s0 + 0x8);
                *(f32 *)(sp + 0xC) = 1.0f;
                *(f32 *)(sp + 0x10) = (f32)s0[0x1C];
                *(f32 *)(sp + 0x14) = (f32)s0[0x1D];
                *(f32 *)(sp + 0x18) = (f32)s0[0x1E];
                *(f32 *)(sp + 0x1C) = (f32)s0[0x1F];
                *(f32 *)(sp + 0x20) = (f32)s0[0x20];
                *(f32 *)(sp + 0x24) = (f32)s0[0x21];
                *(f32 *)(sp + 0x28) = (f32)s0[0x22];
                *(f32 *)(sp + 0x2C) = (f32)s0[0x23];
                *(f32 *)(sp + 0x30) = *(f32 *)(s0 + 0x10);
                *(f32 *)(sp + 0x34) = (f32)s0[0x1F];
                *(f32 *)(sp + 0x38) = *(f32 *)(s0 + 0x14);
                *(f32 *)(sp + 0x3C) = *(f32 *)(s0 + 0xC);
                *(s32 *)(sp + 0x40) = *(u16 *)(s0 + 0x18);
                *(s32 *)(sp + 0x44) = 0x1E;
                *(s32 *)(sp + 0x48) = *(u16 *)(s0 + 0x1A);
                s0 += 0x30;
                func_001437A8((s32)sp);
            } while (s2 < hdr[1]);
        }
    }
}
