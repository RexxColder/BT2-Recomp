#include "common.h"

s64 GetTimerSystemTime(void);
void Res_RelocateOffsets(s32 arg0, s32 arg1, s32 arg2);
void func_0026EAE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0026EA88(s32 arg0);
void func_00325370(s64 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 *D_003876A4;
extern u8 D_0038B058[] __attribute__((section(".data")));

#define DB ((s32)D_0038B058)

void func_002987A0(s32 arg0, s32 arg1) {
    s32 a0;
    s32 a1;
    s32 v;
    s32 base;
    s32 i;
    s32 a1i;
    s32 a3;
    s32 p;

    a0 = arg0;
    a1 = arg1;
    if ((*(s32 *)(D_003876A4 + 0x18) & 2) == 0) {
        memset((void *)DB, 0, 0x94);
        v = *(s32 *)(D_003876A4 + 0x14);
        *(s32 *)(DB + 0x0C) = v;
        Res_RelocateOffsets(DB + 0x0C, v, v);
        a0 = *(s32 *)(DB + 0x0C);
        a1 = (s32)D_003876A4;
        *(s32 *)(DB + 0x10) = *(s32 *)(a0 + 0x10);
        *(s32 *)(DB + 0x14) = *(s32 *)(a0 + 0x10) + 0x40;
        *(s32 *)(DB + 0x18) = *(s32 *)(a0 + 0x10) + 0x80;
        *(s32 *)(DB + 0x1C) = *(s32 *)(a0 + 0x10) + 0x80;
        v = *(s32 *)(a1 + 0x08);
        *(s32 *)(DB + 0x20) = v + (((u32)*(s32 *)(v + 0x04) >> 2) << 2);
        *(s32 *)(a1 + 0x18) = *(s32 *)(a1 + 0x18) | 2;
    }

    v = GetTimerSystemTime();
    func_00325370((s64)v);

    *(u8 *)(DB + 0x00) = 0;
    *(u8 *)(DB + 0x01) = 0;
    *(f32 *)(DB + 0x90) = 6.0f;
    *(f32 *)(DB + 0x8C) = 6.0f;
    *(s32 *)(DB + 0x04) = 0;
    *(s32 *)(DB + 0x88) = 0;
    *(u8 *)(DB + 0x02) = 0;
    *(u8 *)(DB + 0x03) = 0;
    memset((void *)(DB + 0x24), 0, 0x2A);
    memset((void *)(DB + 0x50), 0, 0x38);
    *(f32 *)(DB + 0x78) = 225.0f;
    *(f32 *)(DB + 0x7C) = 192.0f;
    *(f32 *)(DB + 0x5C) = 225.0f;
    *(f32 *)(DB + 0x60) = 192.0f;

    i = 0;
    a3 = 6;
    do {
        a3 -= 1;
        *(s32 *)(*(s32 *)(DB + 0x20) + i + 0xA4) = 0;
        i += 0x38;
    } while (a3 >= 0);

    a1i = 0;
    a3 = 1;
    do {
        a3 -= 1;
        *(s32 *)(a1i + *(s32 *)(DB + 0x20) + 0x238) = 0xC0;
        p = a1i + *(s32 *)(DB + 0x20) + 0x230;
        *(s32 *)(p + 0x10) = *(s32 *)(p + 0x08) + 0x40;
        *(s32 *)(a1i + *(s32 *)(DB + 0x20) + 0x234) = 0xE1;
        p = a1i + *(s32 *)(DB + 0x20) + 0x230;
        *(s32 *)(p + 0x0C) = *(s32 *)(p + 0x04) + 0x40;
        *(s32 *)(a1i + *(s32 *)(DB + 0x20) + 0x248) = 0;
        p = a1i + *(s32 *)(DB + 0x20) + 0x230;
        *(s32 *)(p + 0x20) = *(s32 *)(p + 0x18) + 0x40;
        *(s32 *)(a1i + *(s32 *)(DB + 0x20) + 0x244) = 0;
        p = a1i + *(s32 *)(DB + 0x20) + 0x230;
        *(s32 *)(p + 0x1C) = *(s32 *)(p + 0x14) + 0x40;
        *(s32 *)(a1i + *(s32 *)(DB + 0x20) + 0x254) = 2;
        *(s32 *)(a1i + *(s32 *)(DB + 0x20) + 0x264) = 0x80;
        a1i += 0x38;
    } while (a3 >= 0);

    base = *(s32 *)(DB + 0x20);
    *(s32 *)(base + 0x268) = 0;
    v = *(s32 *)(D_003876A4 + 0x0C);
    *(s32 *)(DB + 0x08) = v;
    *(s32 *)(v + 0x04) = DB + 0x10;
    func_0026EAE0(*(s32 *)(DB + 0x08), 0x1E, DB, a3);
    func_0026EA88(*(s32 *)(DB + 0x08));
}
