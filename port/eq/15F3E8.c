#include "common.h"

s32 EftShot_TestBits(s32 arg0, s32 arg1);
void func_0015F2E0(s32 arg0, s32 arg1);
void func_0015F378(s32 arg0, s32 arg1);
void func_001EDBD8(s32 arg0, s32 arg1);
void func_001EDD40(s32 arg0, s32 arg1);
void Mtx_StoreIdentity(s32 arg0);
void func_00128C58(s32 arg0, s32 arg1, f32 farg0);
void Mtx_RotateX(s32 arg0, s32 arg1, f32 farg0);
void Mtx_RotateY(s32 arg0, s32 arg1, f32 farg0);
void Mtx_Translate(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
extern f32 D_00384724;
extern f32 D_00384728;
extern f32 D_0038472C;

void func_0015F3E8(s32 arg0) {
    u8 *self;
    u8 *P;
    u8 *Q;
    u8 *s1;
    u8 *s0;
    f32 *fp;
    f32 v;
    s32 s4;
    s32 v1;
    s32 k;

    self = (u8 *)arg0;
    P = (u8 *)*(s32 *)(self + 0x38);
    Q = (u8 *)*(s32 *)(P + 0xF0);
    if (EftShot_TestBits(*(s32 *)Q, 0x10) == 0) {
        if (EftShot_TestBits(*(s32 *)Q, 0x20) != 0) {
            *(s32 *)(P + 4) = *(s32 *)(P + 4) | 2;
        }
    } else {
        *(s32 *)(P + 4) = *(s32 *)(P + 4) | 9;
    }

    if ((*(s32 *)(P + 4) & 1) != 0) {
        s1 = P + 0xAF0;
        s4 = 0;
        do {
            v1 = *(s32 *)(s1 + 0x34);
            if ((v1 & 1) == 0) {
                func_0015F2E0((s32)self, (s32)s1);
                v1 = *(s32 *)(s1 + 0x34) | 1;
                *(s32 *)(s1 + 0x34) = v1;
            }
            if ((*(s32 *)(P + 4) & 8) != 0) {
                if ((v1 & 2) == 0) {
                    func_001EDBD8(*(s32 *)(s1 + 0x30), 1);
                    *(s32 *)(s1 + 0x34) = *(s32 *)(s1 + 0x34) | 2;
                    v1 = *(s32 *)(s1 + 0x34);
                }
            } else {
                if ((v1 & 2) != 0) {
                    func_001EDBD8(*(s32 *)(s1 + 0x30), 0);
                    *(s32 *)(s1 + 0x34) = *(s32 *)(s1 + 0x34) & ~2;
                    v1 = *(s32 *)(s1 + 0x34);
                }
            }
            if ((v1 & 2) != 0) {
                if ((*(s32 *)(P + 4) & 2) != 0) {
                    if ((v1 & 4) == 0) {
                        func_0015F378((s32)self, (s32)s1);
                        *(s32 *)(s1 + 0x34) = *(s32 *)(s1 + 0x34) | 4;
                    }
                }
                s0 = s1 + 0x50;
                Vec3_Add((s32)s0, (s32)s0, (s32)(s1 + 0x60));
                fp = (f32 *)s0;
                k = 2;
                do {
                    v = *fp;
                    if (D_00384724 < v) {
                        v = v - D_00384728;
                        *fp = v;
                    } else if (v < D_0038472C) {
                        v = v + D_00384728;
                        *fp = v;
                    }
                    k -= 1;
                    fp += 1;
                } while (k >= 0);
                s0 = s1 + 0x70;
                Mtx_StoreIdentity((s32)s0);
                func_00128C58((s32)s0, (s32)s0, *(f32 *)(s1 + 0x38));
                Mtx_RotateX((s32)s0, (s32)s0, *(f32 *)(s1 + 0x50));
                Mtx_RotateY((s32)s0, (s32)s0, *(f32 *)(s1 + 0x54));
                Mtx_Translate((s32)s0, (s32)s0, (s32)(P + 0xC0));
                func_001EDD40(*(s32 *)(s1 + 0x30), (s32)s0);
            }
            s4 -= 1;
            s1 += 0xB0;
        } while (s4 >= 0);
    }
}
