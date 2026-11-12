#include "common.h"

extern u8 *gBtlCamView;

extern void Vec3_Add(void *a0, void *a1, void *a2);
extern void Vec3_Sub(void *a0, void *a1, void *a2);
extern void Vec3_Cross(void *a0, void *a1, void *a2);
extern void Vec3_Normalize(void *a0, void *a1);
extern void Vec4_Set(void *a0, f32 f12, f32 f13, f32 f14, f32 f15);
extern void func_00129BD0(void *a0, void *a1, f32 f12);
extern void func_00129C28(void *a0, void *a1);
extern void func_00129A50(void *a0, void *a1, void *a2, s32 a3);
extern s32 func_00129720(void *a0, void *a1, void *a2, s32 a3);
extern void func_001296A0(void *a0, void *a1, void *a2, void *a3, s32 t0);
extern void func_0012DA70();
extern void *func_0012B9B0();

#define FRP ((u8 *)frame)
#define FA(off) ((void *)(FRP + (off)))
#define FW(off) (*(s32 *)(FRP + (off)))
#define FF(off) (*(f32 *)(FRP + (off)))

void func_001BB3D0(void *arg0, s32 arg1, void *arg2, s32 arg3) {
    s64 frame[0x400 / 8];
    u8 *fp = (u8 *)arg0;
    u8 *obj;
    u8 *s0;
    u8 *s2;
    u8 *s5;
    u8 *s7;
    u8 *p0;
    u8 *a2v;
    u8 *a1v;
    void *sp404;
    s32 s1;
    s32 s3;
    s32 m;

    sp404 = func_0012B9B0(arg0, arg1, arg2, arg3);
    func_00129C28(FA(0x70), gBtlCamView + 0x1F0);
    for (s1 = 0; s1 < 4; s1++) {
        FF(0x98 + 16 * s1) = 1.0f;
        FF(0x9C + 16 * s1) = 1.0f;
        Vec4_Set(FA(0x30 + 16 * s1), 0.0f, 0.0f, 0.0f, 1.0f);
    }

    obj = *(u8 **)arg0;
    while (obj != NULL) {
        Vec3_Sub(FA(0x80), obj + 0x80, FA(0x70));
        Vec3_Cross(FA(0x80), obj + 0x90, FA(0x80));
        Vec3_Normalize(FA(0x80), FA(0x80));
        func_00129BD0(FA(0xD0), FA(0x80), *(f32 *)(obj + 0x3C));
        Vec3_Add(FA(0x30), obj + 0x80, FA(0xD0));
        Vec3_Sub(FA(0x40), obj + 0x80, FA(0xD0));
        if (((u8 *)arg2)[5] != 0) {
            func_00129BD0(FA(0xE0), obj + 0x90, *(f32 *)(obj + 0x34) * 0.5f);
            Vec3_Add(FA(0x50), FA(0x30), FA(0xE0));
            Vec3_Add(FA(0x60), FA(0x40), FA(0xE0));
            Vec3_Sub(FA(0x30), FA(0x30), FA(0xE0));
            Vec3_Sub(FA(0x40), FA(0x40), FA(0xE0));
        } else {
            func_00129BD0(FA(0xE0), obj + 0x90, *(f32 *)(obj + 0x34));
            Vec3_Add(FA(0x50), FA(0x30), FA(0xE0));
            Vec3_Add(FA(0x60), FA(0x40), FA(0xE0));
        }

        for (s1 = 0; s1 < 4; s1++) {
            FF(0x90 + 16 * s1) = (f32)(s1 % 2) * *(f32 *)(fp + 0x70) + *(f32 *)(obj + 0xD0);
            FF(0x94 + 16 * s1) = (f32)(s1 / 2) * *(f32 *)(fp + 0x74) + *(f32 *)(obj + 0xD8);
        }

        func_00129C28(FA(0x210), obj + 0xA0);
        func_00129C28(FA(0x220), obj + 0xA0);
        s5 = FA(0x250);
        func_00129C28(FA(0x230), obj + 0xA0);
        s3 = 3;
        s1 = 4;
        func_00129C28(FA(0x240), obj + 0xA0);
        func_001296A0(FA(0x250), FA(0x30), FA(0x90), FA(0x210), 3);

        s2 = (u8 *)sp404;
        do {
            s3 = func_00129720(FA(0x250), FA(0x250), s2, s3);
            s1--;
            s2 += 16;
        } while (s1 >= 0);

        if (s3 != 0) {
            s2 = FA(0x180);
            func_00129A50(FA(0xF0), FA(0x180), FA(0x250), s3);
            s1 = 2;
            if (s1 < s3) {
                s5 = FA(0xF0);
                s0 = FA(0x2B0);
                s7 = FA(0x270);
                do {
                    m = s1;
                    p0 = FRP + 0x180 + 16 * m;
                    a2v = s5 + 16 * m;
                    a1v = a2v - 16;
                    func_0012DA70(s5, a1v, a2v, s7, s0 - 16, s0 + 0x20, FA(0x180), p0 - 16, p0,
                                  0, 0, obj[5], FW(0xF8) >> 8, *(s64 *)(fp + 0x280));
                    s0 += 0x30;
                    s1 = m + 1;
                } while (s1 < s3);
            }
        }

        func_001296A0(FA(0x250), FA(0x40), FA(0xA0), FA(0x220), 3);
        s3 = 3;
        s1 = 4;
        s0 = (u8 *)sp404;
        s2 = FA(0x250);
        do {
            s3 = func_00129720(s2, s2, s0, s3);
            s1--;
            s0 += 16;
        } while (s1 >= 0);

        if (s3 != 0) {
            s2 = FA(0x180);
            func_00129A50(FA(0xF0), FA(0x180), FA(0x250), s3);
            s1 = 2;
            if (s1 < s3) {
                s5 = FA(0xF0);
                s0 = FA(0x2B0);
                s7 = FA(0x270);
                do {
                    m = s1;
                    p0 = FRP + 0x180 + 16 * m;
                    a2v = s5 + 16 * m;
                    a1v = a2v - 16;
                    func_0012DA70(s5, a1v, a2v, s7, s0 - 16, s0 + 0x20, FA(0x180), p0 - 16, p0,
                                  0, 0, obj[5], FW(0xF8) >> 8, *(s64 *)(fp + 0x280));
                    s0 += 0x30;
                    s1 = m + 1;
                } while (s1 < s3);
            }
        }

        obj = *(u8 **)(obj + 0x120);
    }
}
