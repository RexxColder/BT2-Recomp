#include "common.h"

extern s32 gBtlCamView;
s32 EftShot_TestBits(s32 arg0, s32 arg1);
s32 func_0020B3D0(s32 arg0);
void Mtx_InverseRT(u8 *arg0, s32 arg1);
void func_001DBF28(u8 *arg0, s64 arg1, s64 arg2, s64 arg3, s64 arg4);

void func_0016B9A0(u8 *arg0) {
    s64 fr64[0x14];
    u8 *fr;
    u8 *s0;
    u8 *s2;
    u8 *rec;
    s32 s1;
    s64 a1;
    s64 a2;
    s64 a3;
    s64 t0;
    s64 v0;
    s64 v1;

    fr = (u8 *)fr64;
    s0 = *(u8 **)(arg0 + 0x38);
    s2 = *(u8 **)(s0 + 0xB0);
    s1 = func_0020B3D0(*(s32 *)s2);
    if (*(s32 *)*(u8 **)(s2 + 0x20) == 0x132) {
        Mtx_InverseRT(fr, gBtlCamView);
        if (EftShot_TestBits(s1, 0x10) != 0) {
            *(f32 *)(fr + 0x70) = *(f32 *)(fr + 0x30);
            *(f32 *)(fr + 0x74) = *(f32 *)(fr + 0x34);
            *(f32 *)(fr + 0x78) = *(f32 *)(fr + 0x38);
            *(f32 *)(fr + 0x7C) = 1.0f;
            *(s32 *)(fr + 0x8C) = 1;
            *(s32 *)(fr + 0x80) = *(s32 *)s2;
            *(s32 *)(fr + 0x88) = 1;
            *(s32 *)(fr + 0x84) = 0;
            *(s32 *)(fr + 0x90) = 0;
            t0 = *(s64 *)(fr + 0x70);
            a3 = *(s64 *)(fr + 0x78);
            v1 = *(s64 *)(fr + 0x80);
            a2 = *(s64 *)(fr + 0x88);
            v0 = *(s64 *)(fr + 0x90);
            a1 = *(s64 *)(fr + 0x98);
            *(s64 *)(fr + 0x50) = v1;
            *(s64 *)(fr + 0x60) = v0;
            *(s64 *)(fr + 0x40) = t0;
            *(s64 *)(fr + 0x48) = a3;
            *(s64 *)(fr + 0x58) = a2;
            *(s64 *)(fr + 0x68) = a1;
            *(s32 *)(fr + 0x60) = 0x30;
            *(s32 *)(fr + 0x54) = 0x2C;
            func_001DBF28(fr + 0x40, a1, a2, a3, t0);
        }
    }
    rec = fr + 0x40;
    if (EftShot_TestBits(s1, 0x40) != 0) {
        *(f32 *)(fr + 0x70) = *(f32 *)(s0 + 0x50);
        *(f32 *)(fr + 0x74) = *(f32 *)(s0 + 0x54);
        *(f32 *)(fr + 0x78) = *(f32 *)(s0 + 0x58);
        *(f32 *)(fr + 0x7C) = 1.0f;
        *(s32 *)(fr + 0x8C) = 1;
        *(s32 *)(fr + 0x80) = *(s32 *)s2;
        *(s32 *)(fr + 0x88) = 1;
        *(s32 *)(fr + 0x84) = 0x47;
        *(s32 *)(fr + 0x90) = 0;
        t0 = *(s64 *)(fr + 0x98);
        a3 = *(s64 *)(fr + 0x70);
        v1 = *(s64 *)(fr + 0x78);
        v0 = *(s64 *)(fr + 0x90);
        a1 = *(s64 *)(fr + 0x80);
        a2 = *(s64 *)(fr + 0x88);
        *(s64 *)(fr + 0x60) = v0;
        *(s64 *)(fr + 0x48) = v1;
        *(s64 *)(fr + 0x40) = a3;
        *(s64 *)(fr + 0x50) = a1;
        *(s64 *)(fr + 0x58) = a2;
        *(s64 *)(fr + 0x68) = t0;
        *(s32 *)(fr + 0x60) = 0;
        func_001DBF28(rec, a1, a2, a3, t0);
        *(s32 *)(fr + 0x60) = 3;
        ((void (*)(u8 *))func_001DBF28)(rec);
        *(s32 *)(fr + 0x60) = 0xA;
        ((void (*)(u8 *))func_001DBF28)(rec);
        *(s32 *)(fr + 0x60) = 0xE;
        ((void (*)(u8 *))func_001DBF28)(rec);
        if (*(s32 *)*(u8 **)(s2 + 0x20) == 0x159) {
            *(s32 *)(fr + 0x54) = 0x4A;
        }
        *(s32 *)(fr + 0x60) = 0x15;
        ((void (*)(u8 *))func_001DBF28)(rec);
    }
}
