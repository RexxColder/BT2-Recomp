#include "common.h"

void Mtx_StoreIdentity(s32 arg0);
void Vec3_Normalize(s32 arg0, s32 arg1);
void func_00128810(s32 arg0, s32 arg1);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
void func_00129C28(s32 arg0, s32 arg1);
s32 func_001EDB20(s32 arg0, s32 arg1);
void func_001EDC20(s32 arg0, s32 arg1);
void func_001EDD40(s32 arg0, s32 arg1);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
f32 func_00212970(void);
s32 rand(void);
extern f32 D_00384EF8;
extern f32 D_00384EFC;
extern f32 D_00384F00;
extern f32 D_00384F04;
extern u8 *D_0038784C;

void func_001AC178(u8 *arg0) {
    u8 sp[0x40];
    u8 *s0;
    u8 *s1;
    u8 *s2;
    f32 f0;
    f32 f1;
    f32 f20;
    f32 f21;
    f32 f23;
    f32 r;
    s32 v;

    f21 = D_00384EF8;
    s1 = *(u8 **)(arg0 + 0x38);
    f20 = D_00384EFC;
    s2 = s1 + 0x50;
    s0 = s1 + 0x70;
    func_00208DE8((s32)*(s16 *)(s1 + 0x12), (s32)(s1 + 0x40), (s32)*(s16 *)(s1 + 0x14));
    func_00208DE8((s32)*(s16 *)(s1 + 0x12), (s32)s2, (s32)*(s16 *)(s1 + 0x14));
    func_00208DE8((s32)*(s16 *)(s1 + 0x12), (s32)(s1 + 0x60), 0x11);
    f23 = D_00384F00;
    func_00129C28((s32)s0, (s32)s1);

    r = func_00212970();
    *(f32 *)(s1 + 0x70) = *(f32 *)(s1 + 0x70) + ((r * f21) + f20);
    r = func_00212970();
    f0 = r * D_00384F04;
    f0 = f0 + 0.0f;
    *(f32 *)(s1 + 0x74) = *(f32 *)(s1 + 0x74) - f0;
    r = func_00212970();
    *(f32 *)(s1 + 0x78) = *(f32 *)(s1 + 0x78) + ((r * f21) + f20);
    Vec3_Normalize((s32)s0, (s32)s0);

    *(s16 *)(s1 + 0xEA) = 0xF;
    *(s32 *)(s1 + 0xC8) = 3;
    *(f32 *)(s1 + 0xD0) = *(f32 *)(s1 + 0x28);
    *(f32 *)(s1 + 0xCC) = *(f32 *)(s1 + 0x20);
    *(s16 *)(s1 + 0xE6) = 0x12C;
    *(s32 *)(s1 + 0xC4) = (s32)*(s16 *)(s1 + 0x1C);
    *(f32 *)(s1 + 0xE0) = 0.5f;
    *(f32 *)(s1 + 0xD4) = 5.0f;

    f0 = (f32)rand();
    f0 = f0 / f23;
    f0 = f0 * 10.0f;
    f0 = f0 - 5.0f;
    f20 = f0 + 32.0f;
    *(f32 *)(s1 + 0xDC) = f20;

    f0 = (f32)rand();
    f0 = f0 / f23;
    if (f0 < 0.5f) {
        f1 = f20;
    } else {
        f1 = -f20;
    }
    *(f32 *)(s1 + 0xDC) = f1;
    func_00129BD0((s32)s0, (s32)s0, *(f32 *)(s1 + 0xCC));

    Mtx_StoreIdentity((s32)sp);
    v = func_001EDB20((s32)(s1 + 0xEC), *(s32 *)(D_0038784C + 0x50));
    *(s32 *)(s1 + 0x11C) = v;
    if (v != -1) {
        func_001EDC20(v, 0);
        func_00128810((s32)sp, (s32)s2);
        func_001EDD40(*(s32 *)(s1 + 0x11C), (s32)sp);
    }
}
