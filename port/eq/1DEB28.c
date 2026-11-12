#include "common.h"

extern u8 D_0036F210[] __attribute__((section(".data")));
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

s32 BtlCharApi_IsHidden(s32 a0);
void func_001DF2F8(u8 *a0);
u8 *func_001DF378(s32 a0);
void func_003126C8(u8 *a0, u8 *a1);
void Vu0Screen_StoreMtx(u8 *a0);
void func_0012A108(u8 *a0, u8 *a1, u8 *a2, u8 *a3, u8 *t0, s32 t1);
s32 func_001DF410(u8 *a0);
void *memcpy(void *arg0, const void *arg1, u32 arg2);

#define F(p, o) (*(f32 *)((p) + (o)))
#define W(p, o) (*(s32 *)((p) + (o)))

static u8 cvt_byte(s32 i, f32 f21) {
    f32 f0 = (f32)i * f21;
    s32 v;
    if (2147483648.0f <= f0) v = (s32)(f0 - 2147483648.0f) | 0x80000000;
    else v = (s32)f0;
    return (u8)v;
}

static void put_tex(u8 *pk, u32 off, u8 *src) {
    u64 x;
    *(u16 *)(pk + off) = *(u16 *)(src + 0);
    *(u16 *)(pk + off + 2) = *(u16 *)(src + 4);
    x = *(u64 *)(pk + off);
    x = (x & 0xFF000000FFFFFFFFULL) | ((u64)((u32)W(src, 8) & 0xFFFFFF) << 32);
    *(u64 *)(pk + off) = x;
    pk[off + 7] = 0xFF;
}

void func_001DEB28(u8 *a0) {
    u8 sp[0x130];
    u8 *s1, *s5, *a1p, *s4, *s2, *s3, *pk, *q;
    s32 s7, s0, s4i, s2i, s3i, v53, s6, v, t0;
    f32 f21;
    s32 v1;

    s1 = *(u8 **)(a0 + 0x38) + 0x10;
    memcpy(sp, D_0036F210, 0x30);
    s7 = W(s1, 0x1290);
    v53 = (s7 + 0x7F) & 0x7F;
    s4i = (s7 + 0x7D) & 0x7F;
    s2i = (s7 + 0x7E) & 0x7F;
    s3i = (s7 + 0x7C) & 0x7F;
    s0 = W(s1, 0x128C);
    if (BtlCharApi_IsHidden(W(s1, 0x1280))) return;
    if (s7 == s0) return;
    if (v53 == s0 || s2i == s0 || s4i == s0 || s3i == s0) return;
    func_001DF2F8(sp + 0x100);
    s5 = func_001DF378(W(s1, 0x1280));
    if (!s5) return;
    W(sp, 0x100) = (s32)F(s5, 0x20);
    W(sp, 0x104) = (s32)F(s5, 0x24);
    W(sp, 0x108) = (s32)F(s5, 0x28);
    v = (s32)F(s5, 0x2C);
    f21 = (f32)v / 255.0f;
    W(sp, 0x10C) = v;
    for (;;) {
        if (s0 == s7) return;
        s0 = (s0 + 1) & 0x7F;
        if (s0 == v53) return;
        a1p = s1 + s0 * 4 + 0x1080;
        if (!W(a1p, 0)) continue;
        W(sp, 0x124) = ((s0 + 1) & 0x7F) << 4;
        s2 = s1 + (s0 << 4);
        W(sp, 0x128) = (s32)(s1 + (((s0 + 1) & 0x7F) * 4 + 0x1080));
        s4 = a1p;
        s3 = s1 + (((s0 + 1) & 0x7F) << 4);
        for (s6 = 0; s6 < 2; s6++) {
            if (s6 & 1) {
                func_003126C8(sp + 0x30, s2);
                func_003126C8(sp + 0x40, s2 + 0x800);
                func_003126C8(sp + 0x50, s1 + W(sp, 0x124));
                F(sp, 0) = 1.0f;
                W(sp, 4) = 0;
                W(sp, 0x10) = 0;
                W(sp, 0x14) = 0;
                F(sp, 0x20) = 1.0f;
                W(sp, 0x24) = 0;
                W(sp, 0x110) = 0;
                W(sp, 0x114) = W(s4, 0);
                W(sp, 0x118) = 0;
            } else {
                func_003126C8(sp + 0x30, s2 + 0x800);
                func_003126C8(sp + 0x40, s3);
                func_003126C8(sp + 0x50, s3 + 0x800);
                W(sp, 0) = 0;
                W(sp, 4) = 0;
                F(sp, 0x10) = 1.0f;
                W(sp, 0x14) = 0;
                W(sp, 0x20) = 0;
                W(sp, 0x24) = 0;
                W(sp, 0x110) = W(s4, 0);
                W(sp, 0x114) = 0;
                W(sp, 0x118) = W(*(u8 **)(sp + 0x128), 0);
            }
            Vu0Screen_StoreMtx(sp + 0xC0);
            func_0012A108(sp + 0x60, sp + 0x90, sp + 0xC0, sp + 0x30, sp, 3);
            if (func_001DF410(sp + 0x60)) continue;
            if (func_001DF410(sp + 0x70)) continue;
            if (func_001DF410(sp + 0x80)) continue;
            pk = D_00387AD8;
            D_00387AD8 = pk + 0x60;
            t0 = W(s5, 0x30);
            *(u64 *)(pk + 0x20) = 0x4B;
            *(u64 *)(pk + 0x00) = 0xA0000005ULL;
            *(u64 *)(pk + 0x10) = 0x8400000000008001ULL;
            *(u64 *)(pk + 0x18) = 0xF4141410ULL;
            pk[0x28] = sp[0x100]; pk[0x29] = sp[0x104]; pk[0x2A] = sp[0x108];
            pk[0x2B] = cvt_byte(W(sp, 0x110), f21);
            F(pk, 0x2C) = 1.0f;
            pk[0x38] = sp[0x100]; pk[0x39] = sp[0x104]; pk[0x3A] = sp[0x108];
            pk[0x3B] = cvt_byte(W(sp, 0x114), f21);
            F(pk, 0x3C) = 1.0f;
            pk[0x48] = sp[0x100]; pk[0x49] = sp[0x104]; pk[0x4A] = sp[0x108];
            pk[0x4B] = cvt_byte(W(sp, 0x118), f21);
            F(pk, 0x4C) = 1.0f;
            put_tex(pk, 0x30, sp + 0x60);
            put_tex(pk, 0x40, sp + 0x70);
            put_tex(pk, 0x50, sp + 0x80);
            v1 = W(sp, 0x68) >> 8;
            if (v1 >= 0) {
                if (v1 < 0x1000) q = D_00387AE0 + (v1 * 2 + t0) * 8;
                else q = D_00387AE0 + t0 * 8 + 0xFFF0;
            } else {
                q = D_00387AE0 + t0 * 8;
            }
            W(*(u8 **)(q + 4), 4) = (s32)pk;
            W(q, 4) = (s32)pk;
        }
    }
}
