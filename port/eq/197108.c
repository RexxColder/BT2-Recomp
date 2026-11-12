#include "common.h"

extern f32 D_00384CC0;
extern u8 *gEftGlow;
extern u8 *gEftGlowCfg;

void func_00129BD0(void *arg0, void *arg1, f32 farg0);
void func_00129C28(void *arg0, void *arg1);
void func_0012B280(f32 farg0, void *arg1, void *arg2);
void Vec3_Normalize(void *arg0, void *arg1);
f32 cosf(f32 arg0);
f32 sinf(f32 arg0);

void func_00197108(void) {
    u8 sp[0x200] __attribute__((aligned(16)));
    f32 *v120;
    f32 *s4p;
    u8 *s4;
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 v0;
    f32 t;
    f32 f12b;

    s3 = 0;
    do {
        v0 = s3 << 4;
        s3 += 1;
        func_00129BD0(sp + v0, gEftGlowCfg + v0 + 0x1C0, *(f32 *)(gEftGlowCfg + 0x1A4));
    } while (s3 < 0xD);

    func_00129C28(sp + 0xD0, sp);
    s3 = 0;
    func_00129C28(sp + 0xE0, sp + 0x10);
    func_00129C28(sp + 0xF0, sp + 0x20);
    func_00129C28(sp + 0x100, sp + 0x30);
    s4 = sp + 0x40;
    do {
        s1 = 0;
        s0 = s3 << 5;
        do {
            t = (f32)s1;
            s1 += 1;
            func_0012B280(t * 0.5f, sp + 0x110, sp + 0xD0);
            func_00129C28(gEftGlow + s0 + 0x20, sp + 0x110);
            s0 += 0x10;
        } while (s1 < 2);
        func_00129C28(sp + 0xD0, sp + 0xE0);
        s3 += 1;
        func_00129C28(sp + 0xE0, sp + 0xF0);
        func_00129C28(sp + 0xF0, sp + 0x100);
        func_00129C28(sp + 0x100, s4);
        s4 += 0x10;
    } while (s3 < 0xA);

    v120 = (f32 *)(sp + 0x120);
    s3 = 0;
    do {
        t = (f32)s3;
        s3 += 1;
        v120[s3 - 1] = (t * 0.5f) / 6.0f;
    } while (s3 < 6);

    s3 = 6;
    do {
        v0 = s3 - 6;
        s3 += 1;
        v120[s3 - 1] = (((f32)v0 * 0.5f) / 14.0f) + 0.5f;
    } while (s3 < 0x14);

    s4p = v120;
    s3 = 0;
    do {
        s2 = s3 << 4;
        s1 = s2 + 0x160;
        s3 += 1;
        *(s32 *)(gEftGlow + s1) = 0;
        *(f32 *)(gEftGlow + 4 + s1) = -cosf(((20.0f + (*s4p * 95.0f)) / 180.0f) * D_00384CC0);
        f12b = *s4p;
        s4p += 1;
        *(f32 *)(gEftGlow + 8 + s1) = sinf(((20.0f + (f12b * 95.0f)) / 180.0f) * D_00384CC0);
        *(f32 *)(gEftGlow + s1 + 0xC) = 1.0f;
        Vec3_Normalize(gEftGlow + s1, gEftGlow + s1);
    } while (s3 < 0x14);
}
