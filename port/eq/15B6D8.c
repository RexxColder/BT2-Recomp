#include "common.h"

extern s32 func_001F42D8(s32 arg0);
extern void func_00208798(s32 arg0, void *arg1);
extern void func_001D28E0(void *arg0);
extern void func_0015BC70(void *arg0, void *arg1, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
extern void func_001CF938(void *arg0, s32 arg1, f32 f12, f32 f13, f32 f14);
extern void func_001CFBC0(void *arg0, s32 arg1, f32 f12, f32 f13, f32 f14, f32 f15);
extern void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
extern void func_00129C28(void *arg0, void *arg1);
extern void func_00129BD0(void *arg0, void *arg1, f32 f12);
extern void Vec3_Add(void *arg0, void *arg1, void *arg2);
extern void Vec3_Sub(void *arg0, void *arg1, void *arg2);
extern void Vec3_Normalize(void *arg0, void *arg1);
extern s32 rand(void);
extern s64 D_0036E290[2] __attribute__((section(".data")));
extern f32 D_003846D0;
extern f32 D_003846D4;
extern f32 D_003846D8;
extern f32 D_003846DC;
extern f32 D_003846E0;
extern f32 D_003846E4;
extern f32 D_003846E8;

void func_0015B6D8(void *arg0) {
    f32 vec[4];
    f32 p10[4];
    f32 p20[4];
    s64 p30[2];
    f32 p40[4];
    f32 p50[4];
    f32 p60[4];
    u8 *s3;
    s32 *s6;
    s32 s5;
    s32 sw;
    u32 v;
    f32 f20;
    f32 r1;
    f32 r2;
    f32 r3;

    s3 = *(u8 **)((u8 *)arg0 + 0x38);
    s6 = *(s32 **)(s3 + 0xA0);
    p30[0] = D_0036E290[0];
    p30[1] = D_0036E290[1];
    s5 = func_001F42D8(*s6);
    *(u32 *)(s3 + 0x14) = *(u32 *)(s3 + 0x14) + 1;
    func_00208798(s5, p20);
    vec[0] = *(f32 *)(s3 + 0x70);
    vec[1] = p20[1] - 10.0f;
    vec[2] = *(f32 *)(s3 + 0x78);
    vec[3] = 1.0f;
    func_001D28E0(p30);

    v = *(u32 *)(s3 + 0x14);
    if (v < 0x17C && (v & 3) == 0) {
        func_0015BC70(arg0, vec, 6.0f, 50.0f, 0.5f, 1.0f, 1.0f);
        r1 = (f32)rand() / D_003846D0;
        f20 = r1 + 3.0f;
        r2 = (f32)rand() / D_003846D0;
        func_001CF938(vec, 8, 2.0f, f20, r2 * 8.0f + 12.0f);
        v = *(u32 *)(s3 + 0x14);
    }

    if ((u32)(v - 0x168) < 0x6E) {
        if ((v & 3) == 0) {
            r1 = (f32)rand() / D_003846D4;
            f20 = r1 + 8.0f;
            r2 = (f32)rand() / D_003846D4;
            func_001CF938(vec, 8, D_003846D8, f20, r2 * 6.0f + 10.0f);
        }
        vec[1] = vec[1] - 5.0f;
        if (!(*(u32 *)(s3 + 0x14) & 1)) {
            func_0015BC70(arg0, vec, 4.0f, 60.0f, 0.5f, 1.0f, D_003846DC);
        }
        func_0015BC70(arg0, vec, 6.5f, 85.0f, 1.0f, 1.0f, D_003846E0);
        v = *(u32 *)(s3 + 0x14);
    }

    if (!((s32)v < 0x5C8) && ((v & 3) == 0)) {
        /* block C: v >= 0x5C8 and 4-aligned */
        func_00129C28(p10, vec);
        p10[1] = p10[1] - 25.0f;
        r1 = (f32)rand() / D_003846E4;
        f20 = r1 + 20.0f;
        r2 = (f32)rand() / D_003846E4;
        func_001CFBC0(p10, 0x20, 2.5f, f20, r2 * 8.0f + 25.0f, 2.0f);
        func_0015BC70(arg0, p10, 20.0f, 140.0f, 0.5f, 2.0f, 1.0f);
    }

    sw = *(s32 *)(s3 + 0x10);
    if (sw == 1) {
        /* case 1 */
        func_00208DE8(s5, p50, 0x11);
        func_00208DE8(*s6, p60, 0x11);
        Vec3_Sub(p40, p60, p50);
        Vec3_Normalize(p40, p40);
        func_00129BD0(p40, p40, 70.0f);
        Vec3_Add(p50, p50, p40);
        func_00129C28(s3 + 0x70, p50);
        if (*(s32 *)(s3 + 0x14) == 0x5C7) {
            func_00129C28(s3 + 0x60, s3 + 0x70);
        }
        if (*(s32 *)(s3 + 0x14) >= 0x5C8) {
            r1 = (f32)rand() / D_003846E8;
            *(f32 *)(s3 + 0x70) = *(f32 *)(s3 + 0x60) + (r1 - 0.5f);
            *(f32 *)(s3 + 0x74) = *(f32 *)(s3 + 0x64) - 30.0f;
            r2 = (f32)rand() / D_003846E8;
            *(f32 *)(s3 + 0x78) = *(f32 *)(s3 + 0x68) + (r2 - 0.5f);
        }
    } else if (sw == 0) {
        /* case 0 */
        func_00129C28(s3 + 0x80, s3 + 0x70);
        Vec3_Add(s3 + 0x70, s3 + 0x70, s3 + 0x90);
        if (*(s32 *)(s3 + 0x14) >= 0x136) {
            func_00208DE8(s5, p50, 0x11);
            func_00208DE8(*s6, p60, 0x11);
            Vec3_Sub(p40, p60, p50);
            Vec3_Normalize(p40, p40);
            func_00129BD0(p40, p40, 70.0f);
            Vec3_Add(p50, p50, p40);
            func_00129C28(s3 + 0x70, p50);
            *(s32 *)(s3 + 0x10) = 1;
        }
    }
}
