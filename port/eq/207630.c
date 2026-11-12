#include "common.h"
void *memset(void *arg0, s32 arg1, u32 arg2);
void *memcpy(void *arg0, const void *arg1, u32 arg2);

extern u8 *D_003876A0;
extern u8 D_003B0B00[] __attribute__((section(".data")));
extern u8 D_00387938[];
extern f32 D_00385954, D_00385958;

s32 BtlMember_IsHealthEmpty_2127F8(u8 *a0);
s32 func_00211310(u8 *a0, s32 a1, s32 a2);
s32 func_001214F8(s32 a0, u8 *a1);
s32 func_0028C520(s32 a0, s32 a1);
f32 Pad_StickToFloat(s32 a0, s32 a1);
f32 sqrtf(f32 x);

#define F(p, o) (*(f32 *)((p) + (o)))
#define W(p, o) (*(s32 *)((p) + (o)))
#define Q(p, o) (*(u64 *)((p) + (o)))

void func_00207630(u8 *a0, s32 a1) {
    u8 sp[8];
    s32 s0, s2, s4, v1, a1v, i;
    f32 f0, f1, f2, f3, f4;

    s4 = D_003876A0[W(a0, 0x1534) * 464 + 0x2A4] != 0;
    s2 = BtlMember_IsHealthEmpty_2127F8(a0) != 0;
    if (func_00211310(a0, 10, 0x40)) s2 = 1;
    memcpy(a0 + 0x24, a0, 0x20);
    W(a0, 0x44) = W(a0, 0x20);
    if (*(u64 *)(D_003876A0 + 0x4D8) & 0x200) s2 = 1;
    memset(a0, 0, 0x24);
    if (func_00211310(a0, 0, 0x100000)) {
        v1 = W(a0, 0x78);
    } else if (*(u64 *)(D_003876A0 + 0x4D8) & 0x3800) {
        v1 = W(a0, 0x78);
    } else {
        memcpy(sp, D_00387938, 4);
        s0 = 0;
        if (!s2) {
            if (s4) {
                s0 = func_001214F8(W(a0, 0x1534), sp);
            } else if (W(D_003B0B00, a1 * 384 + 0x108) != 0) {
                sp[0] = func_0028C520(a1, 0x40000);
                sp[1] = func_0028C520(a1, 0x80000);
                sp[2] = func_0028C520(a1, 0x10000);
                sp[3] = func_0028C520(a1, 0x20000);
                s0 = W(D_003B0B00, a1 * 384 + 0x12C);
            }
            if (*(u64 *)(D_003876A0 + 0x4D8) & 0x400) s0 &= W(a0, 0x54);
        }
        F(a0, 8) = Pad_StickToFloat(sp[0], 50);
        F(a0, 0xC) = Pad_StickToFloat(sp[1], 50);
        F(a0, 0x10) = Pad_StickToFloat(sp[2], 50);
        f0 = Pad_StickToFloat(sp[3], 50);
        W(a0, 0x20) = s0;
        F(a0, 0x14) = f0;
        v1 = W(a0, 0x78);
    }
    W(a0, 0) = 0;
    W(a0, 4) = 0;
    if (v1 & 0x1000000) {
        f0 = F(a0, 8);
        f1 = F(a0, 0xC);
        F(a0, 0) = f0;
        F(a0, 4) = f1;
    }
    if (v1 & 0x4000000) {
        a1v = W(a0, 0x20);
        if (a1v & 0x80) F(a0, 0) = -1.0f;
        if (a1v & 0x20) F(a0, 0) = 1.0f;
        if (a1v & 0x10) F(a0, 4) = -1.0f;
        if (a1v & 0x40) F(a0, 4) = 1.0f;
    }
    f1 = F(a0, 0);
    f0 = F(a0, 4);
    f2 = sqrtf(f1 * f1 + f0 * f0);
    F(a0, 0x18) = f2;
    if (1.0f < f2) {
        f0 = F(a0, 0) / f2;
        f1 = F(a0, 4) / f2;
        F(a0, 0x18) = 1.0f;
        F(a0, 0) = f0;
        F(a0, 4) = f1;
    }
    f2 = F(a0, 0x10);
    f3 = F(a0, 0x14);
    f1 = sqrtf(f2 * f2 + f3 * f3);
    F(a0, 0x1C) = f1;
    if (1.0f < f1) {
        f0 = f3 / f1;
        F(a0, 0x1C) = 1.0f;
        f1 = f2 / f1;
        F(a0, 0x14) = f0;
        f3 = f0;
        F(a0, 0x10) = f1;
        f2 = f1;
    }
    f0 = F(a0, 8);
    f4 = D_00385954;
    f1 = D_00385958;
    if (f0 < f4) W(a0, 0x20) |= 0x40000;
    if (f1 < f0) W(a0, 0x20) |= 0x80000;
    f0 = F(a0, 0xC);
    if (f0 < f4) W(a0, 0x20) |= 0x10000;
    if (f1 < f0) W(a0, 0x20) |= 0x20000;
    if (f2 < f4) W(a0, 0x20) |= 0x400000;
    if (f1 < f2) W(a0, 0x20) |= 0x800000;
    if (f3 < f4) W(a0, 0x20) |= 0x100000;
    if (f1 < f3) W(a0, 0x20) |= 0x200000;
    a1v = W(a0, 0x20);
    if (a1v & 0xF0000) { a1v |= 0x1000000; W(a0, 0x20) = a1v; }
    if (a1v & 0xF00000) { a1v |= 0x2000000; W(a0, 0x20) = a1v; }
    if (a1v & 0xF0) { a1v |= 0x4000000; W(a0, 0x20) = a1v; }
    v1 = W(a0, 0x44);
    W(a0, 0x48) = a1v;
    W(a0, 0x50) = v1 & ~a1v;
    W(a0, 0x4C) = a1v & ~v1;
    if (*(u64 *)(D_003876A0 + 0x4D8) & 0x3800) return;
    for (i = 0; i < 32; i++) {
        s32 m = 1 << i;
        s8 *p1 = (s8 *)(a0 + 0xDC + i);
        s8 *p2 = (s8 *)(a0 + 0xFC + i);
        s8 *p3 = (s8 *)(a0 + 0x11C + i);
        if (!(W(a0, 0x48) & m)) {
            *p1 = 0;
        } else if (*p1 < 100) {
            *p1 = *p1 + 1;
        }
        if (W(a0, 0x48) & m) {
            *p2 = 0;
        } else if (*p2 < 100) {
            *p2 = *p2 + 1;
        }
        if (W(a0, 0x4C) & m) {
            *p3 = 0;
        } else if (*p3 < 100) {
            *p3 = *p3 + 1;
        }
    }
}
