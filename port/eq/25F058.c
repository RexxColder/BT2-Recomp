#include "common.h"

u8 *func_00269A40(u8 *arg0, s32 arg1);
extern f32 D_00386E80;

void func_0025F058(u8 *arg0, f32 farg0) {
    u8 *v0;
    u8 *s0;
    u8 *p;

    v0 = arg0 + 0xBD0;
    if (!(D_00386E80 < farg0)) {
        *(s32 *)(v0 + 0x1C) = 0;
        *(f32 *)(v0 + 0x20) = 1.0f;
        return;
    }
    *(s32 *)(v0 + 0x1C) = 0x3F800000;
    *(f32 *)(v0 + 0x20) = 1.0f / (farg0 * 30.0f);
    s0 = *(u8 **)(arg0 + 0x48);
    while (1) {
        p = func_00269A40(arg0, *(u16 *)(s0 + 0xA));
        *(f32 *)(p + 0xA0) = *(f32 *)(p + 0x80);
        *(f32 *)(p + 0xBC) = *(f32 *)(p + 0x9C);
        *(f32 *)(p + 0xA4) = *(f32 *)(p + 0x84);
        *(f32 *)(p + 0xA8) = *(f32 *)(p + 0x88);
        *(f32 *)(p + 0xAC) = *(f32 *)(p + 0x8C);
        *(f32 *)(p + 0xB0) = *(f32 *)(p + 0x90);
        *(f32 *)(p + 0xB4) = *(f32 *)(p + 0x94);
        *(f32 *)(p + 0xB8) = *(f32 *)(p + 0x98);
        if (*(u16 *)(s0 + 6) != 0) {
            return;
        }
        s0 += *(s32 *)s0;
    }
}
