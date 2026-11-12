#include "common.h"

void sceVu0ApplyMatrix(s32 arg0, s32 arg1, s32 arg2);
void func_003125D0(f32 farg0, s32 arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern s64 D_0036D9D0[] __attribute__((section(".data")));

void func_0012B280(void *arg0, void *arg1, f32 farg0) {
    s64 fr64[24];
    u8 *fr = (u8 *)fr64;
    f32 f8;
    f32 f9;
    s32 i;

    for (i = 0; i < 8; i++) {
        *(s64 *)(fr + i * 8) = D_0036D9D0[i];
    }
    memset(fr + 0x80, 0, 0x10);
    for (i = 0; i < 12; i++) {
        *(f32 *)(fr + 0x90 + i * 4) = *(f32 *)((u8 *)arg1 + i * 4);
    }
    f8 = farg0 * farg0;
    f9 = f8 * farg0;
    *(s64 *)(fr + 0x40) = *(s64 *)(fr + 0x80);
    *(s64 *)(fr + 0x48) = *(s64 *)(fr + 0x88);
    *(s64 *)(fr + 0x50) = *(s64 *)(fr + 0x90);
    *(s64 *)(fr + 0x58) = *(s64 *)(fr + 0x98);
    *(s64 *)(fr + 0x60) = *(s64 *)(fr + 0xA0);
    *(s64 *)(fr + 0x68) = *(s64 *)(fr + 0xA8);
    *(s64 *)(fr + 0x70) = *(s64 *)(fr + 0xB0);
    *(s64 *)(fr + 0x78) = *(s64 *)(fr + 0xB8);
    *(f32 *)(fr + 0x80) = f9;
    *(f32 *)(fr + 0x84) = f8;
    *(f32 *)(fr + 0x88) = farg0;
    *(f32 *)(fr + 0x8C) = 1.0f;
    sceVu0ApplyMatrix((s32)(fr + 0x80), (s32)fr, (s32)(fr + 0x80));
    sceVu0ApplyMatrix((s32)(fr + 0x80), (s32)(fr + 0x40), (s32)(fr + 0x80));
    func_003125D0(2.0f, (s32)arg0, (s32)(fr + 0x80));
    *(f32 *)((u8 *)arg0 + 0xC) = 1.0f;
}
