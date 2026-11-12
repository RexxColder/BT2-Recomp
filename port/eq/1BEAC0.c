#include "common.h"

extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

void func_00129C28(void *a0, void *a1);
void func_00129D40(void *a0, void *a1);
void func_00129BD0(void *a0, void *a1, f32 farg0);
void Vec3_Sub(void *a0, void *a1, void *a2);
void Vec3_Add(void *a0, void *a1, void *a2);
void Vec3_Cross(void *a0, void *a1, void *a2);
void Vec3_Normalize(void *a0, void *a1);
void Vec4_Set(void *a0, void *a1, void *a2, f32 f12, f32 f13, f32 f14, f32 f15);
s32 func_001294B0(void *a0, void *a1, s32 a2, s32 a3);

void func_001BEAC0(void *arg0, void *arg1, void *arg2) {
    u8 sp[0x1C0] __attribute__((aligned(8)));
    u8 *s4;
    u8 *s0;
    u8 *o;
    u8 *v0p;
    u8 *v1;
    u8 *q;
    s32 i;
    s32 k;
    s32 sum;
    s32 a1v;
    s32 a0b;
    u64 s7 = 0xFF000000FFFFFFFFULL;

    func_00129C28(sp + 0x40, gBtlCamView + 0x1F0);

    for (i = 0; i < 4; i++) {
        *(f32 *)(sp + 0x60 + i * 16) = (f32)(i % 2);
        *(f32 *)(sp + 0x64 + i * 16) = (f32)(i / 2);
        *(f32 *)(sp + 0x68 + i * 16) = 1.0f;
        *(s32 *)(sp + 0x6C + i * 16) = 0;
        Vec4_Set(sp + i * 16, sp + 0x6C + i * 16, sp + 0x60 + i * 16, 0.0f, 0.0f, 0.0f, 1.0f);
    }

    func_00129D40(sp + 0x140, (u8 *)arg2 + 0x70);

    s4 = *(u8 **)((u8 *)arg2 + 0xE8);
    if (s4 == NULL) {
        return;
    }

    do {
        if (*(u8 **)(s4 + 0xF0) != NULL) {
            Vec3_Sub(sp + 0x50, s4 + 0x50, sp + 0x40);
            Vec3_Cross(sp + 0x50, s4 + 0x60, sp + 0x50);
            Vec3_Normalize(sp + 0x50, sp + 0x50);
            func_00129BD0(sp + 0xE0, sp + 0x50, *(f32 *)(s4 + 0x20));
            Vec3_Add(sp, s4 + 0x50, sp + 0xE0);
            Vec3_Sub(sp + 0x10, s4 + 0x50, sp + 0xE0);
            func_00129BD0(sp + 0xF0, s4 + 0x60, *(f32 *)(s4 + 0x28));
            Vec3_Add(sp + 0x20, sp, sp + 0xF0);
            Vec3_Add(sp + 0x30, sp + 0x10, sp + 0xF0);

            if (func_001294B0(sp + 0x100, sp, 4, 1) != 0) {
                s0 = D_00387AD8;
                D_00387AD8 = s0 + 0x90;
                if (s0 == NULL) {
                    return;
                }
                o = s0;

                *(s64 *)(o + 0x20) = 0x5C;
                *(s64 *)(o + 0x00) = (s64)0xA0000008ULL;
                *(s64 *)(o + 0x10) = (s64)0xE400000000008001ULL;
                *(s64 *)(o + 0x18) = (s64)0x0042142142142160ULL;

                for (i = 0; i < 4; i++) {
                    func_00129BD0(sp + 0xA0 + i * 16, sp + 0x60 + i * 16, 1.0f / (f32)*(s32 *)(sp + 0x10C + i * 16));
                }

                sum = *(s32 *)(sp + 0x108) + *(s32 *)(sp + 0x138) +
                      (*(s32 *)(sp + 0x128) + *(s32 *)(sp + 0x118));
                a1v = sum >> 10;

                if (*(s32 *)((u8 *)arg0 + 0x60) & 0x10) {
                    k = 3;
                    q = sp + 0x138;
                    do {
                        k -= 1;
                        *(s32 *)q = 0xFFFFFF;
                        q -= 0x10;
                    } while (k >= 0);
                }

                *(u8 *)(o + 0x30) = sp[0x140];
                *(u8 *)(o + 0x31) = sp[0x144];
                *(u8 *)(o + 0x32) = sp[0x148];
                *(u8 *)(o + 0x33) = sp[0x14C];
                *(f32 *)(o + 0x34) = *(f32 *)(sp + 0xA8);
                *(u8 *)(o + 0x48) = sp[0x140];
                *(u8 *)(o + 0x49) = sp[0x144];
                *(u8 *)(o + 0x4A) = sp[0x148];
                *(u8 *)(o + 0x4B) = sp[0x14C];
                *(f32 *)(o + 0x4C) = *(f32 *)(sp + 0xB8);
                *(u8 *)(o + 0x60) = sp[0x140];
                *(u8 *)(o + 0x61) = sp[0x144];
                *(u8 *)(o + 0x62) = sp[0x148];
                *(u8 *)(o + 0x63) = sp[0x14C];
                *(f32 *)(o + 0x64) = *(f32 *)(sp + 0xC8);
                *(u8 *)(o + 0x78) = sp[0x140];
                *(u8 *)(o + 0x79) = sp[0x144];
                *(u8 *)(o + 0x7A) = sp[0x148];
                *(u8 *)(o + 0x7B) = sp[0x14C];
                *(f32 *)(o + 0x7C) = *(f32 *)(sp + 0xD8);

                *(f32 *)(o + 0x38) = *(f32 *)(sp + 0xA0);
                *(f32 *)(o + 0x3C) = *(f32 *)(sp + 0xA4);
                *(f32 *)(o + 0x50) = *(f32 *)(sp + 0xB0);
                *(f32 *)(o + 0x54) = *(f32 *)(sp + 0xB4);
                *(f32 *)(o + 0x68) = *(f32 *)(sp + 0xC0);
                *(f32 *)(o + 0x6C) = *(f32 *)(sp + 0xC4);
                *(f32 *)(o + 0x80) = *(f32 *)(sp + 0xD0);
                *(f32 *)(o + 0x84) = *(f32 *)(sp + 0xD4);

                /* packed 16-bit x/y plus 24-bit colour word per group */
                *(u16 *)(o + 0x40) = *(u16 *)(sp + 0x100);
                *(u16 *)(o + 0x42) = *(u16 *)(sp + 0x104);
                *(s64 *)(o + 0x40) = (*(s64 *)(o + 0x40) & (s64)s7) |
                                     ((s64)((u64)*(u32 *)(sp + 0x108) & 0xFFFFFF) << 32);
                *(u8 *)(o + 0x47) = 0xFF;

                *(u16 *)(o + 0x58) = *(u16 *)(sp + 0x110);
                *(u16 *)(o + 0x5A) = *(u16 *)(sp + 0x114);
                *(s64 *)(o + 0x58) = (*(s64 *)(o + 0x58) & (s64)s7) |
                                     ((s64)((u64)*(u32 *)(sp + 0x118) & 0xFFFFFF) << 32);
                *(u8 *)(o + 0x5F) = 0xFF;

                *(u16 *)(o + 0x70) = *(u16 *)(sp + 0x120);
                *(u16 *)(o + 0x72) = *(u16 *)(sp + 0x124);
                *(s64 *)(o + 0x70) = (*(s64 *)(o + 0x70) & (s64)s7) |
                                     ((s64)((u64)*(u32 *)(sp + 0x128) & 0xFFFFFF) << 32);
                *(u8 *)(o + 0x77) = 0xFF;

                *(u16 *)(o + 0x88) = *(u16 *)(sp + 0x130);
                *(u16 *)(o + 0x8A) = *(u16 *)(sp + 0x134);
                *(s64 *)(o + 0x88) = (*(s64 *)(o + 0x88) & (s64)s7) |
                                     ((s64)((u64)*(u32 *)(sp + 0x138) & 0xFFFFFF) << 32);
                *(u8 *)(o + 0x8F) = 0xFF;

                *(s64 *)(o + 0x28) = *(s64 *)(*(u8 **)((u8 *)arg1 + 0x34) +
                                              *(s32 *)((u8 *)arg1 + 0x30) * 16);

                a0b = s4[5];
                if (a1v < 0) {
                    v1 = D_00387AE0 + a0b * 8;
                } else if (a1v < 0x1000) {
                    v1 = D_00387AE0 + (a1v * 2 + a0b) * 8;
                } else {
                    v1 = D_00387AE0 + a0b * 8 + 0xFFF0;
                }
                v0p = *(u8 **)(v1 + 4);
                *(u8 **)(v0p + 4) = o;
                *(u8 **)(v1 + 4) = o;
            }
        }
        s4 = *(u8 **)(s4 + 0xF0);
    } while (s4 != NULL);
}
