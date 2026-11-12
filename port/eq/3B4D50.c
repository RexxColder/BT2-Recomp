#include "common.h"

s32 func_2B8328(u8 *a0);
void func_2B4FD0(u8 *a0, u8 *a1);
s32 func_2B58F0(u8 *a0);
s32 func_003B5350(u8 *a0, u8 *a1, u8 *a2);
void func_003B5620(u8 *a0, u8 *a1, u8 *a2, s32 a3);
void func_003B5A00(f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7,
                   u8 *a0, u8 *a1, u8 *a2, u8 *a3, u8 *t0, s32 t1, s32 t2, s32 t3,
                   s32 s9, s32 s10, s32 s11, s32 s12, u8 *s13);
void func_003B5FF8(f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7,
                   u8 *a0, u8 *a1, u8 *a2, u8 *a3, u8 *t0, u8 *t1, u8 *t2, u8 *t3,
                   s32 s9, s32 s10, s32 s11, u8 *s12);
void func_003B62C8(f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7,
                   u8 *a0, u8 *a1, u8 *a2, u8 *a3, u8 *t0, u8 *t1, u8 *t2, s32 t3,
                   s32 s9, s32 s10, s32 s11, u8 *s12);

/* 0x003B4D50: renderer step for the object P (a0). Two calls (func_2B8328 == 2) then a 16-byte-aligned 0x40 scratch
 * buffer with the packet quadword at buf + 0x30. The float block f12..f19 is P->0xE0/0xE4/0xF0/0xF4/0x100/0x104/
 * 0x110/0x114 scaled by 2^-10. P->0x1C0 picks func_003B5A00 (0), func_003B5FF8 (1) or func_003B62C8 (2).
 * Only the incoming t3 (p8) is passed through, on the path that calls func_003B62C8. */
void func_003B4D50(u8 *P, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6, s32 t3in) {
    u8 buf[0x40];
    s32 v;
    s32 q1;
    s64 q;
    s32 mode;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f4;
    f32 f5;
    f32 f6;
    f32 f7;
    f32 sc = 0x1.0p-10f;

    if (P == NULL) {
        return;
    }
    if (func_2B8328(*(u8 **)(P + 0xC0)) != 2) {
        return;
    }
    func_2B4FD0(*(u8 **)(P + 0xC0), P);
    if (*(u8 **)(P + 0x0) != NULL) {
        *(s32 *)(P + 0xD0) = func_003B5350(*(u8 **)(P + 0x0), *(u8 **)(P + 0xC), *(u8 **)(P + 0x10));
        func_2B58F0(*(u8 **)(P + 0xC0));
    }
    if (func_2B8328(*(u8 **)(P + 0xC0)) != 2) {
        return;
    }

    memset(buf, 0, 0x40);
    func_003B5620(*(u8 **)(P + 0xD0), *(u8 **)(P + 0xC), *(u8 **)(P + 0x10), *(s32 *)(P + 0x1BC));

    v = *(s32 *)(P + 0xC);
    q1 = (v < 0 ? v + 0x3F : v) >> 6;
    q = (s64)*(s32 *)(P + 0x1BC) | ((s64)q1 << 14) | ((u64)0xD500 << 19);
    *(s64 *)(buf + 0x30) = q;

    f0 = *(f32 *)(P + 0xE0) * sc;
    f1 = *(f32 *)(P + 0xE4) * sc;
    f2 = *(f32 *)(P + 0xF0) * sc;
    f3 = *(f32 *)(P + 0xF4) * sc;
    f4 = *(f32 *)(P + 0x100) * sc;
    f5 = *(f32 *)(P + 0x104) * sc;
    f6 = *(f32 *)(P + 0x110) * sc;
    f7 = *(f32 *)(P + 0x114) * sc;

    mode = *(s32 *)(P + 0x1C0);
    if (mode == 1) {
        func_003B5FF8(f0, f1, f2, f3, f4, f5, f6, f7,
                      P + 0x120, P + 0x130, P + 0x140, P + 0x150, P + 0x160, P + 0x170, P + 0x180, P + 0x190,
                      0, 0, 0, buf);
    } else if (mode < 2) {
        if (mode == 0) {
            func_003B5A00(f0, f1, f2, f3, f4, f5, f6, f7,
                          P + 0x120, P + 0x160, P + 0x170, P + 0x180, P + 0x190,
                          *(s32 *)(P + 0x1A0), *(s32 *)(P + 0x1A4), 0,
                          0x1000, 0, 0, 0, buf);
        }
    } else if (mode == 2) {
        func_003B62C8(f0, f1, f2, f3, f4, f5, f6, f7,
                      P + 0x120, P + 0x130, P + 0x140, P + 0x150, P + 0x160, P + 0x170, P + 0x180, t3in,
                      0, 0, 0, buf);
    }
}
