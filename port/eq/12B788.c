#include "common.h"

void sceVu0ApplyMatrix(s32 arg0, s32 arg1, s32 arg2);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void func_00312680(s32 arg0, s32 arg1, f32 farg0);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
void func_003126C8(s32 arg0, s32 arg1);
extern u8 D_0036DA90[] __attribute__((section(".data")));

void func_0012B788(s32 arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    u8 sp[0xC0];
    u8 *s0;
    u8 *s5;
    u8 *s6;
    u8 *s7;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    u8 *fp;
    u8 *s0b;
    f32 t1;
    f32 t2;
    f32 t3;
    f32 t4;
    f32 t5;
    f32 f0v;
    f32 f13v;
    f32 f3v;
    f32 f2v;
    s32 i;

    s0 = (u8 *)arg1;
    s5 = s0 + 0x10;
    s6 = s0 + 0x20;
    s7 = (u8 *)arg0;
    s4 = sp + 0x60;
    s3 = sp + 0x70;
    s1 = sp + 0x80;
    s2 = sp + 0x90;
    fp = sp + 0xA0;
    s0b = sp + 0xB0;

    for (i = 0; i < 8; i++) {
        *(s64 *)(sp + i * 8) = *(s64 *)(D_0036DA90 + i * 8);
    }

    t1 = 1.0f - farg1;
    t2 = 1.0f - farg2;
    t3 = farg2 + 1.0f;
    t4 = 1.0f - farg3;
    t5 = farg3 + 1.0f;
    f0v = t1 * t2;
    f13v = t1 * t3;
    f3v = f0v * t5;
    f2v = f13v * t4;
    f13v = f13v * t5;
    f0v = f0v * t4;
    f3v = f3v * 0.5f;
    f2v = f2v * 0.5f;
    f13v = f13v * 0.5f;
    f0v = f0v * 0.5f;

    *(f32 *)(sp + 0x40) = farg0 * farg0 * farg0;
    *(f32 *)(sp + 0x44) = farg0 * farg0;
    *(f32 *)(sp + 0x48) = farg0;
    *(f32 *)(sp + 0x4C) = 1.0f;
    *(f32 *)(sp + 0x50) = f13v;
    *(f32 *)(sp + 0x54) = f0v;
    *(f32 *)(sp + 0x58) = f3v;
    *(f32 *)(sp + 0x5C) = f2v;

    sceVu0ApplyMatrix((s32)fp, (s32)sp, (s32)(sp + 0x40));
    func_00312650((s32)s4, (s32)s5, (s32)s0);
    func_00312650((s32)s3, (s32)s6, (s32)s5);
    func_00312650((s32)s1, (s32)s6, (s32)s5);
    func_00312650((s32)s2, (s32)(s0 + 0x30), (s32)s6);
    func_00312680((s32)s0b, (s32)s4, *(f32 *)(sp + 0x50));
    func_00312680((s32)s1, (s32)s3, *(f32 *)(sp + 0x54));
    func_00312638((s32)s1, (s32)s1, (s32)s0b);
    func_00312680((s32)s0b, (s32)s3, *(f32 *)(sp + 0x58));
    func_00312680((s32)s2, (s32)s2, *(f32 *)(sp + 0x5C));
    func_00312638((s32)s2, (s32)s2, (s32)s0b);
    func_003126C8((s32)s4, (s32)s5);
    func_003126C8((s32)s3, (s32)s6);
    sceVu0ApplyMatrix((s32)s7, (s32)s4, (s32)fp);
    *(f32 *)(s7 + 0xC) = 1.0f;
}
