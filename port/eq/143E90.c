#include "common.h"

extern s32 EftStage_IsDrawOn(void);
extern f32 EftStage_GetTintScale(void);
extern void func_00128EF0(void);
extern void func_00128F90(s32 arg0);
extern void func_00276828(void *a0);
extern void Vec3_Normalize(void *arg0, void *arg1);
extern void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
extern void Vec3_Sub(void *arg0, void *arg1, void *arg2);
extern f32 func_00129CD8(u8 *arg0, u8 *arg1);
extern void func_00129BD0(void *arg0, void *arg1, f32 farg0);
extern void Vec3_Add(void *arg0, void *arg1, void *arg2);
extern void func_00128F08(void);
extern s32 func_001F00A8(s32 a0, s32 a1, s32 a2, s32 a3, s64 t0, s64 t1, s32 t2, s32 t3,
                         s32 st0, s32 st1, s32 st2, s32 st3, u8 *st4, f32 farg0, f32 farg1, f32 farg2);
extern u8 *gBtlCamView;
extern f32 D_00384514;
extern s32 D_00387748;

void func_00143E90(u8 *arg0) {
    u8 sp[0x100];
    f32 *camDir = (f32 *)(sp + 0x40);
    f32 *base = (f32 *)(sp + 0x30);
    f32 *dirV = (f32 *)(sp + 0x80);
    f32 *col = (f32 *)(sp + 0x50);
    f32 *amb = (f32 *)(sp + 0x70);
    f32 *light = (f32 *)(sp + 0x60);
    u8 *st;
    u8 *flags;
    u8 *e;
    f32 tint;
    f32 life;
    f32 dot;
    f32 w;
    f32 r, g, b;
    s64 conv0, conv1;
    s32 maskA, maskB;
    s32 n;
    u16 cnt;
    u64 hdr;

    st = *(u8 **)(arg0 + 0x38);
    flags = *(u8 **)st + 0x20;
    if (EftStage_IsDrawOn() == 0) {
        return;
    }
    e = st + 0x70;
    tint = EftStage_GetTintScale();
    func_00128EF0();
    func_00128F90((s32)(gBtlCamView + 0x100));
    func_00276828(camDir);
    Vec3_Normalize(camDir, camDir);
    Vec4_Set(base, *(f32 *)(st + 0x10), *(f32 *)(st + 0x14) - 50.0f, *(f32 *)(st + 0x18), 1.0f);
    Vec4_Set(amb, *(f32 *)(st + 0x20), *(f32 *)(st + 0x24), *(f32 *)(st + 0x28), 0.0f);
    Vec4_Set(light, *(f32 *)(st + 0x30), *(f32 *)(st + 0x34), *(f32 *)(st + 0x38), 0.0f);
    hdr = *(u64 *)flags;
    maskB = 1 << ((hdr >> 30) & 0xF);
    maskA = 1 << ((hdr >> 26) & 0xF);
    for (n = 39; n >= 0; n--, e += 0x30) {
        cnt = *(u16 *)(e + 0x20);
        if (cnt == 0) {
            continue;
        }
        life = *(f32 *)(st + 0x44);
        if ((s32)cnt < 0x32) {
            life = (life * (f32)(s32)cnt) / (f32)D_00387748;
        }
        Vec3_Sub(dirV, e, base);
        dirV[1] = dirV[1] * D_00384514;
        Vec3_Normalize(dirV, dirV);
        dot = func_00129CD8((u8 *)dirV, (u8 *)camDir);
        func_00129BD0(col, light, dot);
        if (col[0] < 0.0f) col[0] = 0.0f;
        if (col[1] < 0.0f) col[1] = 0.0f;
        if (col[2] < 0.0f) col[2] = 0.0f;
        Vec3_Add(col, col, amb);
        if (255.0f < col[0]) col[0] = 255.0f;
        if (255.0f < col[1]) col[1] = 255.0f;
        if (255.0f < col[2]) col[2] = 255.0f;
        r = col[0];
        g = col[1];
        b = col[2];
        w = *(f32 *)(st + 0x40) * 128.0f;
        conv0 = (s32)w;
        if (2147483648.0f <= w) {
            conv0 = (s64)(s32)(w - 2147483648.0f) | (s64)(s32)0x80000000;
        }
        w = *(f32 *)(st + 0x40) * 128.0f;
        conv1 = (s32)w;
        if (2147483648.0f <= w) {
            conv1 = (s64)(s32)(w - 2147483648.0f) | (s64)(s32)0x80000000;
        }
        func_001F00A8((s32)(r * tint), (s32)(g * tint), (s32)(b * tint), (s32)life, conv0, conv1, 0, 0,
                      maskA, maskB, 0, 0, flags, *(f32 *)e, *(f32 *)(e + 4), *(f32 *)(e + 8));
    }
    func_00128F08();
}
