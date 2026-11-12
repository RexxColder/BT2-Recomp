#include "common.h"

extern f32 D_003874B0;
extern f32 D_003874B4;
extern f32 D_003874B8;
extern f32 D_003874BC;
extern f32 D_003874C0;
extern f32 D_003874C4;
extern f32 D_003874C8;
extern f32 D_003874CC;
extern f32 D_003874D0;
extern f32 D_003874D4;
extern f32 D_003874D8;

f32 cosf(f32 farg0);
f32 sinf(f32 farg0);
void func_002AF728(s32 arg0, s32 arg1, s32 arg2);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void func_00312680(f32 farg0, s32 arg0, s32 arg1);
void func_003126C8(s32 arg0, s32 arg1);

void func_002AF948(u8 *arg0) {
    u8 sp[0x50];
    u8 *s1;
    f32 f12;
    f32 f0;
    f32 f1;
    f32 f3;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 t;
    f32 c1;
    f32 s1v;
    f32 s2v;
    f32 c2;
    f32 c3;

    s1 = arg0 + 0x40;
    f21 = *(f32 *)((u8 *)(*(s32 *)arg0) + 0xFAC);
    if (*(u8 *)(s1 + 0x3C) != 0) {
        *(u8 *)(s1 + 0x3C) = 0;
        *(f32 *)(s1 + 0x38) = 1.0f;
    }
    if (*(u8 *)(s1 + 0x3D) == 0) {
        func_003126C8((s32)s1, (s32)(arg0 + 0xD0));
    }
    f12 = *(f32 *)(s1 + 0x34);
    if (f12 < D_003874B0) {
        *(f32 *)(s1 + 0x34) = D_003874B0;
        f12 = D_003874B0;
    }
    if (D_003874B4 < f12) {
        *(f32 *)(s1 + 0x34) = D_003874B4;
        f12 = D_003874B4;
    }
    f22 = D_003874B8;

    *(f32 *)(sp + 0x00) = *(f32 *)(s1 + 0x00);
    *(f32 *)(sp + 0x08) = *(f32 *)(s1 + 0x08);
    *(f32 *)(sp + 0x10) = -f12;
    *(f32 *)(sp + 0x14) = *(f32 *)(s1 + 0x30);
    *(s32 *)(sp + 0x18) = 0;
    *(f32 *)(sp + 0x04) = *(f32 *)(s1 + 0x04) - (f21 * f22);
    c1 = cosf(f12);
    f23 = D_003874BC;
    s1v = sinf(*(f32 *)(s1 + 0x30));
    *(f32 *)(sp + 0x20) = c1 * s1v;
    s2v = sinf(*(f32 *)(s1 + 0x34));
    *(f32 *)(sp + 0x24) = s2v;
    c2 = cosf(*(f32 *)(s1 + 0x34));
    c3 = cosf(*(f32 *)(s1 + 0x30));
    f20 = c2 * c3;
    *(f32 *)(sp + 0x28) = f20;
    func_00312680(f21 * 1.5f, (s32)(sp + 0x20), (s32)(sp + 0x20));
    func_00312650((s32)sp, (s32)sp, (s32)(sp + 0x20));
    func_00312650((s32)(sp + 0x30), (s32)sp, (s32)(arg0 + 0x50));
    func_00312650((s32)(sp + 0x40), (s32)(sp + 0x10), (s32)(arg0 + 0x60));

    t = *(f32 *)(sp + 0x44);
    if (t < f23) {
        t = t + D_003874C0;
        *(f32 *)(sp + 0x44) = t;
    }
    f20 = D_003874C4;
    if (f20 < t) {
        t = t - D_003874C8;
        *(f32 *)(sp + 0x44) = t;
    }

    f12 = *(f32 *)(s1 + 0x38);
    func_00312680(f12, (s32)(sp + 0x30), (s32)(sp + 0x30));
    f12 = *(f32 *)(s1 + 0x38);
    func_00312680(f12, (s32)(sp + 0x40), (s32)(sp + 0x40));
    func_00312638((s32)(arg0 + 0x50), (s32)(arg0 + 0x50), (s32)(sp + 0x30));
    func_00312638((s32)(arg0 + 0x60), (s32)(arg0 + 0x60), (s32)(sp + 0x40));

    f1 = *(f32 *)(s1 + 0x24);
    if (f1 < f23) {
        f0 = f1 + D_003874CC;
        *(f32 *)(s1 + 0x24) = f0;
        f1 = f0;
    }
    if (f20 < f1) {
        *(f32 *)(s1 + 0x24) = f1 - D_003874D0;
    }
    func_002AF728((s32)arg0, (s32)(arg0 + 0x50), (s32)(arg0 + 0x60));

    f0 = 1.0f;
    *(f32 *)(s1 + 0x1C) = f0;
    f3 = *(f32 *)(s1 + 0x38);
    f1 = (f22 - f3) * D_003874D4;
    *(s32 *)(s1 + 0x2C) = 0;
    if (D_003874D8 < f1) {
        f1 = D_003874D8;
    }
    f1 = f3 + f1;
    if (f1 < f22) {
        *(f32 *)(s1 + 0x38) = f1;
    } else {
        *(f32 *)(s1 + 0x38) = f22;
    }
}
