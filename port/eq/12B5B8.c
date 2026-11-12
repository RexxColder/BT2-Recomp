#include "common.h"

void *memcpy(void *d, const void *s, u32 n);
void sceVu0ApplyMatrix(u8 *out, u8 *mtx, u8 *in);
void func_003126C8(u8 *a0, u8 *a1);
extern u8 D_0036DA50[] __attribute__((section(".data")));

void func_0012B5B8(u8 *arg0, u8 *arg1, f32 farg0) {
    s32 fr[56];
    u8 *sp = (u8 *)fr;
    f32 f8;
    f32 f9;

    f8 = farg0 * farg0;
    f9 = f8 * farg0;
    memcpy(sp, D_0036DA50, 0x40);
    memcpy(sp + 0x80, arg1, 0x20);
    memcpy(sp + 0xA0, arg1 + 0x20, 0x20);
    memcpy(sp + 0x40, sp + 0x80, 0x40);
    *(f32 *)(sp + 0x80) = f9;
    *(f32 *)(sp + 0x84) = f8;
    *(f32 *)(sp + 0x88) = farg0;
    *(f32 *)(sp + 0x8C) = 1.0f;
    sceVu0ApplyMatrix(sp + 0x80, sp, sp + 0x80);
    sceVu0ApplyMatrix(sp + 0x80, sp + 0x40, sp + 0x80);
    func_003126C8(arg0, sp + 0x80);
    *(f32 *)(arg0 + 0xC) = 1.0f;
}
