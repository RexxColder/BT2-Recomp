#include "common.h"

void Mtx_StoreIdentity(s32 arg0);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
f32 func_00129E08(s32 arg0);
void func_00185C68(s32 arg0, s32 arg1, s32 arg2);
void func_00186040(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1, f32 farg2);
void *memset(void *arg0, s32 arg1, s32 arg2);
extern s32 D_003877B0;

void func_001878A0(u8 *arg0, u8 *arg1) {
    u8 frame[0x50];
    u8 *s0;
    u8 *s1;
    u8 *s2;
    s32 v0;
    s32 v1;
    s32 v;
    s32 a0;
    s32 t;
    f32 q;

    *(s64 *)(frame + 0x0) = *(s64 *)(arg1 + 0x0);
    *(s64 *)(frame + 0x8) = *(s64 *)(arg1 + 0x8);
    memset(frame + 0x10, 0, 0x40);
    if (D_003877B0 == 0) {
        return;
    }
    if (arg0 == 0) {
        return;
    }
    s1 = *(u8 **)(arg0 + 0x38);
    if (s1 == 0) {
        return;
    }
    if (!(*(s32 *)(s1 + 0x19C) & 2)) {
        return;
    }
    s2 = *(u8 **)(s1 + 0x30);
    if (*(f32 *)(frame + 0xC) != 1.0f) {
        *(f32 *)(frame + 0xC) = 1.0f;
    }
    Mtx_StoreIdentity((s32)(frame + 0x10));
    v1 = *(s32 *)(s2 + 0xA4);
    if (v1 & 2) {
        s0 = *(u8 **)(s1 + 0x1A4);
        *(s64 *)(s1 + 0x40) = *(s64 *)(frame + 0x0);
        *(s64 *)(s1 + 0x48) = *(s64 *)(frame + 0x8);
        if (s0 != 0) {
            v = *(s32 *)(s2 + 0xA4) & 8;
            for (;;) {
                if (v != 0) {
                    func_00186040((s32)s0, (s32)(frame + 0x10), (s32)(s1 + 0x40),
                                  *(f32 *)(s1 + 0x80), *(f32 *)(s2 + 0x34),
                                  *(f32 *)(s2 + 0x38));
                }
                s0 = *(u8 **)(s0 + 0xC0);
                if (s0 == 0) {
                    break;
                }
                v = *(s32 *)(s2 + 0xA4) & 8;
            }
        }
    }
    v0 = *(s32 *)(s2 + 0xA4) & 1;
    s0 = s1 + 0x70;
    if (v0 == 0) {
        return;
    }
    *(s64 *)(s1 + 0x60) = *(s64 *)(frame + 0x0);
    *(s64 *)(s1 + 0x68) = *(s64 *)(frame + 0x8);
    Vec3_Sub((s32)s0, (s32)(s1 + 0x60), (s32)(s1 + 0x50));
    *(f32 *)(s1 + 0x88) = func_00129E08((s32)s0);
    Vec3_Normalize((s32)s0, (s32)s0);
    q = *(f32 *)(s1 + 0x88) / *(f32 *)(s2 + 0x94);
    if (!(q < 1.0f)) {
        s0 = *(u8 **)(s1 + 0x1A4);
        if (s0 == 0) {
            return;
        }
        /* cvt.w.s: truncates toward zero */
        t = (s32)q;
        v1 = t;
        a0 = 0;
        if (v1 > 0) {
            s0 = *(u8 **)(s0 + 0xC0);
            for (;;) {
                if (s0 == 0) {
                    return;
                }
                a0 += 1;
                if (!(a0 < v1)) {
                    break;
                }
                s0 = *(u8 **)(s0 + 0xC0);
            }
        }
        if (s0 == 0) {
            return;
        }
        *(u16 *)(s0 + 0xBE) = 0;
        for (;;) {
            func_00185C68((s32)(s1 + 0x1A4), (s32)(s1 + 0x1A8), (s32)s0);
            s0 = *(u8 **)(s0 + 0xC0);
            if (s0 == 0) {
                break;
            }
            *(u16 *)(s0 + 0xBE) = 0;
        }
    }
}
