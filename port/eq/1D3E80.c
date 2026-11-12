#include "common.h"

#define AT(T, p, off) (*(T *)((u8 *)(p) + (off)))

void Vec4_Set(u8 *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_00129C28(u8 *arg0, u8 *arg1);
u8 *func_001D3028(void);
s32 rand(void);

extern u8 D_00342ED0[] __attribute__((section(".data")));
extern u8 D_00342F40[] __attribute__((section(".data")));
extern f32 D_003854AC;
extern f32 D_003854B0;
extern f32 D_003854B4;
extern u8 *D_00387E9C;

void func_001D3E80(f32 farg0, u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 fr[0x30];
    u8 *s1;
    s32 i;
    f32 f21;

    for (i = 0; i < 16; i++) {
        fr[i] = arg0[i];
    }

    /* the first call also takes f15 = (float)arg3 (a3 is moved with mtc1 + cvt.s.w) */
    Vec4_Set(fr + 0x10, 128.0f, 128.0f, 128.0f, (f32)arg3);
    Vec4_Set(fr + 0x20, 128.0f, 128.0f, 128.0f, 0.0f);

    s1 = func_001D3028();
    if (s1 == NULL) {
        return;
    }

    AT(f32, s1, 0x20) = AT(f32, fr, 0);
    AT(f32, s1, 0x24) = AT(f32, fr, 4);
    AT(f32, s1, 0x28) = AT(f32, fr, 8);
    AT(f32, s1, 0x6C) = D_003854AC;
    AT(f32, s1, 0x74) = 8.0f;
    AT(f32, s1, 0x64) = 0.0f;
    AT(f32, s1, 0x68) = 0.0f;
    AT(f32, s1, 0x18) = 0.0f;
    AT(f32, s1, 0x14) = 0.0f;
    AT(f32, s1, 0x10) = 0.0f;
    f21 = 0.5f;
    AT(f32, s1, 0x70) = 0.5f;
    AT(f32, s1, 0x78) = (((f32)rand() / D_003854B0) * 360.0f);
    if (!(0.5f < ((f32)rand() / D_003854B0))) {
        f21 = -0.5f;
    }
    AT(f32, s1, 0x7C) = f21;
    AT(f32, s1, 0x80) = 1.0f;
    AT(f32, s1, 0x84) = D_003854B4;
    AT(s32, s1, 0x60) = 0;
    AT(s32, s1, 0x94) = arg2;

    if (arg2 < 0) {
        AT(u8, s1, 0x91) = 0;
        AT(u8, s1, 0x90) = 0xB;
        func_00129C28(s1 + 0x30, fr + 0x10);
        func_00129C28(s1 + 0x40, fr + 0x10);
        func_00129C28(s1 + 0x50, fr + 0x20);
        AT(u8, s1, 0x92) = 3;
    } else {
        AT(u8, s1, 0x91) = 1;
        AT(u8, s1, 0x90) = (u8)(AT(u8, s1, 0x94) + 1);
        func_00129C28(s1 + 0x30, D_00342F40 + (arg2 * 0x10));
        func_00129C28(s1 + 0x40, D_00342F40 + (AT(s32, s1, 0x94) * 0x10));
        func_00129C28(s1 + 0x50, D_00342ED0 + (AT(s32, s1, 0x94) * 0x10));
        AT(u8, s1, 0x92) = 3;
    }

    AT(f32, s1, 0x8C) = farg0;
    AT(u8, s1, 0x93) = (u8)arg1;
    AT(u8, s1, 0x99) = 1;
    AT(s32, s1, 0x88) = 0;
    AT(u8, s1, 0x98) = 0;
    AT(s32, D_00387E9C, 0x1424) = AT(s32, D_00387E9C, 0x1424) + 1;
}
