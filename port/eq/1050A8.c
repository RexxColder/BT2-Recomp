#include "common.h"

s32 func_00100CB8(s32 arg0);
void func_0025A400(void);
void func_0025C740(void);
void func_0025E2D0(s32 arg0);
void func_00261B18(void);
void func_00280CD8(void);
s32 func_0028BAA8(s32 arg0);
void func_002A85B0(void);
void func_002A85D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 *D_003876A0;
extern u8 *D_003876B0;

void func_001050A8(void) {
    s64 *flags;

    flags = (s64 *)(D_003876A0 + 0x4D8);
    *flags = *flags & ~0x8000;
    *flags = *flags & ~0x100;
    *flags = *flags & ~0x800;
    *flags = *flags & ~0x1000;
    *flags = *flags & ~0x2000;
    *flags = *flags & ~0x200;
    *flags = *flags & ~0x400;
    *flags = *flags & ~1;
    *flags = *flags & ~2;
    func_002A85D0((s32)D_003876A0, -0x101, -0x801, -0x1001);
    func_002A85B0();
    func_00261B18();
    func_0025A400();
    func_0025E2D0(2);
    func_00280CD8();
    func_0025C740();
    D_003876B0 = (u8 *)(s32)func_0028BAA8(0x40);
    memset(D_003876B0, 0, 0x40);
    *(s32 *)(D_003876B0 + 8) = func_0028BAA8(0xE9800);
    memset(*(u8 **)(D_003876B0 + 8), 0, 0xE9800);
    *(s32 *)(D_003876B0 + 0x3C) = func_00100CB8(0x3C2D);
}
