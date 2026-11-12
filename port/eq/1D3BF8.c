#include "common.h"

extern u8 *D_00387E9C;
extern u8 D_00342F40[];
extern u8 D_00342ED0[];
extern f32 D_003854A4;
extern f32 D_003854A8;

s32 rand(void);
void Vec4_Set(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
u8 *func_001D3028(void);
void func_00129C28(void *arg0, void *arg1);

s32 func_001D3BF8(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1, f32 farg2) {
    s64 blk[2];
    f32 V0[4];
    f32 V1[4];
    u8 *s1;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f21;
    s32 cnt;

    blk[0] = *(s64 *)arg0;
    blk[1] = *(s64 *)((u8 *)arg0 + 8);

    Vec4_Set(V0, 128.0f, 128.0f, 128.0f, (f32)arg1);
    f21 = 0.0f;
    Vec4_Set(V1, 128.0f, 128.0f, 128.0f, f21);

    s1 = func_001D3028();
    if (s1 == NULL) {
        return 0;
    }

    f1 = farg0 + D_003854A4;
    *(f32 *)(s1 + 0x20) = *(f32 *)((u8 *)blk + 0);
    *(f32 *)(s1 + 0x24) = *(f32 *)((u8 *)blk + 4);
    *(f32 *)(s1 + 0x28) = *(f32 *)((u8 *)blk + 8);
    *(f32 *)(s1 + 0x6C) = f1;
    *(f32 *)(s1 + 0x74) = 3.0f;
    *(f32 *)(s1 + 0x70) = f21;
    *(f32 *)(s1 + 0x68) = f21;
    *(f32 *)(s1 + 0x18) = f21;
    *(f32 *)(s1 + 0x14) = f21;
    *(f32 *)(s1 + 0x10) = f21;
    *(f32 *)(s1 + 0x64) = f21;

    f0 = (f32)rand() / D_003854A8;
    f0 = f0 * 360.0f;
    *(f32 *)(s1 + 0x78) = f0;

    f1 = 0.5f;
    f0 = (f32)rand() / D_003854A8;
    f2 = (f1 < f0) ? 0.5f : -0.5f;
    *(f32 *)(s1 + 0x7C) = f2;

    f1 = farg1 * 30.0f;
    f0 = 1.0f;
    *(f32 *)(s1 + 0x80) = f0;
    *(s32 *)(s1 + 0x60) = 0;
    *(s32 *)(s1 + 0x94) = arg3;
    f0 = f0 / f1;
    *(f32 *)(s1 + 0x84) = f0;

    if (arg3 < 0) {
        *(u8 *)(s1 + 0x91) = 0;
        *(u8 *)(s1 + 0x90) = 0xB;
        func_00129C28(s1 + 0x30, V0);
        func_00129C28(s1 + 0x40, V0);
        func_00129C28(s1 + 0x50, V1);
    } else {
        *(u8 *)(s1 + 0x91) = 1;
        *(u8 *)(s1 + 0x90) = (u8)(*(u8 *)(s1 + 0x94) + 1);
        func_00129C28(s1 + 0x30, D_00342F40 + (*(s32 *)(s1 + 0x94)) * 16);
        func_00129C28(s1 + 0x40, D_00342F40 + (*(s32 *)(s1 + 0x94)) * 16);
        func_00129C28(s1 + 0x50, D_00342ED0 + (*(s32 *)(s1 + 0x94)) * 16);
    }

    *(f32 *)(s1 + 0x8C) = farg2;
    *(u8 *)(s1 + 0x93) = (u8)arg2;
    *(u8 *)(s1 + 0x92) = 2;
    *(u8 *)(s1 + 0x99) = 1;
    *(s32 *)(s1 + 0x88) = 0;
    *(u8 *)(s1 + 0x98) = 0;
    cnt = *(s32 *)(D_00387E9C + 0x1424) + 1;
    *(s32 *)(D_00387E9C + 0x1424) = cnt;
    return cnt;
}
