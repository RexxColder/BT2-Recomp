#include "common.h"

void Vec3_Add(u8 *arg0, u8 *arg1, u8 *arg2);
void func_00129BD0(u8 *arg0, u8 *arg1, f32 farg0);
void func_00129C28(u8 *arg0, u8 *arg1);
void func_00181758(u8 *arg0);
void func_001E7070(u8 *arg0);
void func_00208DE8(s32 arg0, u8 *arg1, s32 arg2);

void func_0019FDC8(u8 *arg0, s32 *arg1) {
    u8 sp[0x30];
    u8 *s2;
    u8 *s3;
    u8 *tp;
    s32 s4;
    s32 temp;

    s4 = 1;
    s3 = *(u8 **)(arg0 + 0x38);
    memset(sp, 0, 0x10);
    *(f32 *)(sp + 0xC) = 1.0f;
    memset(sp + 0x10, 0, 0x10);
    *(f32 *)(sp + 0x1C) = 1.0f;
    memset(sp + 0x20, 0, 0x10);
    *(f32 *)(sp + 0x2C) = 1.0f;
    memset(s3, 0, 0x50);
    temp = *arg1;
    s2 = s3 + 0x2C;
    *(s32 *)(s3 + 0x00) = temp;
    *(f32 *)(s3 + 0x20) = 90.0f;
    *(f32 *)(s3 + 0x24) = 1.0f;
    func_00208DE8(temp, sp + 0x10, 0x17);
    func_00208DE8(*(s32 *)(s3 + 0x00), sp, 0x25);
    Vec3_Add(sp + 0x20, sp + 0x10, sp);
    func_00129BD0(sp + 0x20, sp + 0x20, 0.5f);
    func_00129C28(s3 + 0x10, sp + 0x20);
    *(f32 *)(s3 + 0x1C) = 1.0f;
    do {
        tp = s2;
        s2 += 4;
        s4 -= 1;
        func_001E7070(tp);
    } while (s4 >= 0);
    func_00181758(s3 + 0x38);
}
