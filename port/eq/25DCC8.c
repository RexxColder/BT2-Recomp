#include "common.h"

void func_0025D0A8(u8 *arg0);
void func_0025D100(s32 arg0);
s32 func_0025CD10(void);
void func_0025CD70(s32 arg0);
void func_0025CDA0(s32 arg0, s32 arg1);
void func_0025CE28(s32 arg0, s32 arg1);
void Res_RelocateOffsets(s32 arg0, s32 arg1, s32 arg2);
void func_00269F00(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3);
void func_003126C8(s32 arg0, s32 arg1);
void sceVu0UnitMatrix(s32 arg0);

extern u8 D_002C3630[] __attribute__((section(".data")));

void func_0025DCC8(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 *s1;
    u8 *s2;
    u8 *s4;
    s32 temp;
    f32 f0;
    f32 f1;

    s1 = arg0 + 0xAF0;
    s2 = arg0 + 0x1C;
    s4 = arg0 + 0x9A0;

    if (arg1 != NULL) {
        func_0025D0A8(arg0);
        *(s32 *)(arg0 + 0x1C) = (s32)arg1;
        *(s32 *)(s2 + 0x28) = (s32)arg1;
        temp = (s32)arg1 + *(s32 *)(arg1 + 0x4);
        *(s32 *)(s2 + 0x2C) = temp;
        func_00269F00(0, temp, *(s32 *)(s1 + 0xBC), *(s32 *)(s1 + 0xC0), 0x3D40, *(s32 *)(s1 + 0xCC), 0x7FFFFFFF, 0x7FFFFFFF);

        *(s32 *)s1 = (*(s32 *)arg1 & 0x01000000 ? 0x20000 : 0x10000) | 0x1E;
        func_0025D100((s32)arg0);

        f0 = *(f32 *)(arg1 + 0x30);
        if (f0 == 0.0f) {
            f0 = 18.0f;
        }
        *(f32 *)(s1 + 0xAC) = f0;

        f1 = *(f32 *)(arg1 + 0x34);
        if (f1 != 0.0f) {
            *(f32 *)(s1 + 0xB0) = f1;
        } else {
            *(f32 *)(s1 + 0xB0) = 120.0f;
        }

        f1 = *(f32 *)(arg1 + 0x38);
        if (f1 == 0.0f) {
            f1 = 40.0f;
        }
        *(f32 *)(s1 + 0xB4) = f1;

        f1 = *(f32 *)(arg1 + 0x3C);
        if (f1 == 0.0f) {
            f1 = 120.0f;
        }
        *(f32 *)(s1 + 0xB8) = f1;
    }

    if (arg2 != 0) {
        func_0025CD70(*(s32 *)(s1 + 0x4));
        *(s32 *)(s1 + 0x4) = func_0025CD10();
        *(s32 *)(s2 + 0x4) = arg2;
        Res_RelocateOffsets((s32)(s2 + 0x30), arg2, arg2);
        func_0025CE28((s32)arg0, *(s32 *)(s1 + 0x4));
        func_0025CDA0((s32)arg0, *(s32 *)(s1 + 0x4));
    }

    func_003126C8((s32)s4, (s32)D_002C3630);
    func_003126C8((s32)(s4 + 0x20), (s32)D_002C3630);
    func_003126C8((s32)(s4 + 0x10), (s32)D_002C3630);
    sceVu0UnitMatrix((s32)(s4 + 0x60));

    f0 = 1.0f;
    if (*(s32 *)arg0 != 0) {
        f0 = -1.0f;
    }
    *(f32 *)(s4 + 0x20) = f0;
    *(s32 *)(s4 + 0x24) = 0;
}
