#include "common.h"

extern u8 *D_003877D0;
extern f32 D_00384C80;
extern f32 D_00384C84;

f32 BtlCharApi_GetHeight(s32 arg0);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_00129C28(void *arg0, void *arg1);
s32 EftPtcl3_Create(void *arg0);
void EftPtcl3_SetType(s32 arg0, s32 arg1);
s32 func_0018BA90(void *arg0);
void func_0018C0B0(s32 arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);

s32 Mem_LoadHalf(s32 arg0, s32 arg1) {
    u8 sp[0x1A0] = {0};
    u8 *v3;
    u8 *s0;
    u8 *s1;
    u8 *s3;
    u8 *s4;
    u8 *s5;
    f32 temp_f0;
    s32 a1v;
    s32 ptcl;
    s32 i;

    v3 = D_003877D0 + arg0 * 0x50;
    a1v = *(s32 *)(v3 + 8);
    s0 = (a1v == 0) ? v3 : NULL;
    if (s0 == NULL) {
        return 0;
    }
    *(s32 *)(s0 + 0) = arg0;
    *(s32 *)(s0 + 4) = arg1;
    *(s32 *)(s0 + 8) = *(s32 *)(s0 + 8) | 1;
    temp_f0 = BtlCharApi_GetHeight(arg0) / D_00384C80;
    *(f32 *)(s0 + 0x10) = temp_f0;
    if (temp_f0 < D_00384C84) {
        *(f32 *)(s0 + 0x10) = D_00384C84;
    }
    *(s32 *)(s0 + 0xC) = 3;
    s4 = s0 + 0x20;
    s5 = s0 + 0x30;
    func_00208DE8(arg0, s4, 3);
    Vec4_Set(s5, 0.0f, -1.0f, 0.0f, 1.0f);
    s3 = D_003877D0 + arg1 * 0x240;
    s1 = s3 + 0xA0;
    if (arg1 != 0) {
        return 1;
    }

    *(f32 *)(sp + 0x50) = 0.0f;
    *(f32 *)(sp + 0x54) = *(f32 *)(s0 + 0x10);
    memset(sp + 0x60, 0, 0x10);
    memset(sp + 0x70, 0, 0x10);
    *(s32 *)(sp + 0x84) = (s32)(s3 + 0xA8);
    *(s32 *)(sp + 0x80) = 0;
    *(s32 *)(sp + 0x88) = *(s32 *)(s1 + 0x118);
    *(s32 *)(sp + 0x8C) = *(s32 *)(s1 + 0x11C);
    *(s32 *)(sp + 0x90) = *(s32 *)(s0 + 0);
    for (i = 0; i < 0x50; i++) {
        sp[i] = sp[0x50 + i];
    }
    func_00129C28(sp + 0x10, s4);
    func_00129C28(sp + 0x20, s5);

    ptcl = EftPtcl3_Create(sp);
    *(s32 *)(s0 + 0x40) = ptcl;
    EftPtcl3_SetType(ptcl, 2);

    *(s32 *)(sp + 0x100) = *(s32 *)(s1 + 0x238);
    *(s32 *)(sp + 0x104) = *(s32 *)(s1 + 0x23C);
    *(s32 *)(sp + 0x108) = (s32)(s1 + 0x128);
    memset(sp + 0x110, 0, 0x10);
    memset(sp + 0x120, 0, 0x10);
    memset(sp + 0x130, 0, 0x10);
    memset(sp + 0x140, 0, 0x10);
    *(f32 *)(sp + 0x150) = *(f32 *)(s0 + 0x10);
    *(s32 *)(sp + 0x154) = 0;
    *(s32 *)(sp + 0x158) = 0;
    *(s32 *)(sp + 0x15C) = *(s32 *)(s0 + 0);
    for (i = 0; i < 0x60; i++) {
        sp[0xA0 + i] = sp[0x100 + i];
    }
    func_00129C28(sp + 0xB0, s4);
    func_00129C28(sp + 0xC0, s4);
    func_00129C28(sp + 0xD0, s4);
    func_00129C28(sp + 0xE0, s5);

    ptcl = func_0018BA90(sp + 0xA0);
    *(s32 *)(s0 + 0x44) = ptcl;
    func_0018C0B0(ptcl, 2);
    return 1;
}
