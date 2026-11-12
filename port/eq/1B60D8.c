#include "common.h"

extern u8 D_0036EEE0[];
extern s32 gBtlCamView;
extern s32 gEftShotFx;

void sceVu0InversMatrix(s32 arg0, s32 arg1, s64 arg2);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
void func_00312490(s32 arg0, s32 arg1, s32 arg2);
void func_00312680(s32 arg0, s32 arg1, f32 farg0);
void func_00312FB0(s32 arg0, s32 arg1, f32 farg0);
void func_003126C8(s32 arg0, s32 arg1);
void sceVu0Normalize(s32 arg0, s32 arg1);
void sceVu0ApplyMatrix(s32 arg0, s32 arg1, s32 arg2);

void func_001B60D8(u8 *arg0, u8 *arg1) {
    u8 sp[0x100];
    u8 *v1;
    u8 *v2;
    u8 *v3;
    u8 *v4;
    u8 *v5;
    u8 *v6;
    u8 *v7;
    u8 *v8;
    u8 *v9;

    *(s64 *)(sp + 0x70) = *(s64 *)(D_0036EEE0 + 0);
    *(s64 *)(sp + 0x78) = *(s64 *)(D_0036EEE0 + 8);
    sceVu0InversMatrix((s32)(sp + 0x80), gBtlCamView, *(s64 *)(D_0036EEE0 + 8));

    v1 = sp + 0x10;
    v2 = sp + 0xB0;
    func_00312650((s32)v1, (s32)v2, (s32)arg1);
    sceVu0Normalize((s32)v1, (s32)v1);
    func_00312680((s32)v1, (s32)v1, *(f32 *)(arg1 + 0x20));
    func_00312638((s32)v1, (s32)v1, (s32)arg1);

    v3 = sp + 0x20;
    sceVu0ApplyMatrix((s32)v3, gEftShotFx + 0x10, (s32)(arg1 + 0x10));
    func_00312638((s32)v1, (s32)v1, (s32)v3);

    v4 = sp + 0x40;
    v5 = sp + 0x70;
    func_00312FB0((s32)v4, (s32)v5, *(f32 *)(arg1 + 0x24) * 0.5f);

    v6 = sp + 0x50;
    func_00312638((s32)v6, (s32)v1, (s32)v4);
    v7 = sp + 0x60;
    func_00312650((s32)v7, (s32)v1, (s32)v4);

    v8 = sp;
    func_003126C8((s32)v8, (s32)v2);

    v9 = sp + 0x30;
    func_00312650((s32)v9, (s32)v8, (s32)v6);
    sceVu0Normalize((s32)v9, (s32)v9);
    func_00312490((s32)v4, (s32)v5, (s32)v9);
    sceVu0Normalize((s32)v4, (s32)v4);
    func_00312680((s32)v4, (s32)v4, *(f32 *)(arg1 + 0x30) * 0.5f);

    func_00312638((s32)arg0, (s32)v6, (s32)v4);
    func_00312650((s32)(arg0 + 0x10), (s32)v6, (s32)v4);
    *(f32 *)(arg0 + 0x1C) = 1.0f;
    *(f32 *)(arg0 + 0x0C) = 1.0f;

    func_00312650((s32)v9, (s32)v8, (s32)v7);
    sceVu0Normalize((s32)v9, (s32)v9);
    func_00312490((s32)v4, (s32)v5, (s32)v9);
    sceVu0Normalize((s32)v4, (s32)v4);
    func_00312680((s32)v4, (s32)v4, *(f32 *)(arg1 + 0x30) * 0.5f);

    func_00312638((s32)(arg0 + 0x20), (s32)v7, (s32)v4);
    func_00312650((s32)(arg0 + 0x30), (s32)v7, (s32)v4);
    *(f32 *)(arg0 + 0x3C) = 1.0f;
    *(f32 *)(arg0 + 0x2C) = 1.0f;
}
