#include "common.h"

s32 func_0015B6C0(s32 arg0, s32 arg1, s32 *arg2);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void func_00208F18(s32 arg0, void *arg1, s32 arg2);
void func_00312650(void *arg0, void *arg1, void *arg2);
void sceVu0Normalize(void *arg0, void *arg1);
void func_003126C8(void *arg0, f32 *arg1);
void func_00129C28(void *arg0, void *arg1);
void func_00129BD0(void *arg1, void *arg2, f32 farg0);
extern f32 D_003846CC;

void func_0015AFE0(u8 *arg0) {
    u8 fr[0x60];
    u8 *s2;
    s32 *s3;
    s32 v0;
    f32 f4;

    s2 = *(u8 **)(arg0 + 0x38);
    s3 = *(s32 **)(s2 + 0xA0);
    v0 = func_0015B6C0(*s3, 4, s3);
    *(s32 *)(s2 + 8) = v0;
    func_00208DE8(*s3, s2 + 0x40, v0);
    func_00208DE8(*s3, fr, 0x14);
    func_00208DE8(*s3, fr + 0x10, 0x30);
    func_00312650(fr + 0x20, fr + 0x10, fr);
    sceVu0Normalize(fr + 0x20, fr + 0x20);
    *(f32 *)(fr + 0x2C) = 1.0f;
    func_00208F18(*s3, fr + 0x30, 0x31);
    *(f32 *)(fr + 0x2C) = 1.0f;
    *(f32 *)(fr + 0x24) = D_003846CC - *(f32 *)(fr + 0x54);
    *(f32 *)(fr + 0x20) = -*(f32 *)(fr + 0x50);
    *(f32 *)(fr + 0x28) = -*(f32 *)(fr + 0x58);
    func_003126C8(s2 + 0x20, (f32 *)(fr + 0x20));

    f4 = *(f32 *)(fr + 0x20) * 70.0f;
    *(f32 *)(fr + 0x20) = f4;
    *(f32 *)(fr + 0x24) = *(f32 *)(fr + 0x24) * 70.0f;
    *(f32 *)(fr + 0x28) = *(f32 *)(fr + 0x28) * 70.0f;
    *(f32 *)(s2 + 0x40) = *(f32 *)(fr + 0x10) + f4;
    *(f32 *)(s2 + 0x44) = *(f32 *)(fr + 0x14) + *(f32 *)(fr + 0x24);
    *(f32 *)(s2 + 0x48) = *(f32 *)(fr + 0x18) + *(f32 *)(fr + 0x28);

    func_00129C28(s2 + 0x60, s2 + 0x40);
    func_00129C28(s2 + 0x70, s2 + 0x60);
    func_00129C28(s2 + 0x80, s2 + 0x70);
    func_00129BD0(s2 + 0x90, s2 + 0x20, *(f32 *)(s2 + 0x18));
    *(s32 *)s2 = *(s32 *)s2 | 0x100;
}
