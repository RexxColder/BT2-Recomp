#include "common.h"

/* 0x0028D0F8: box (min xyz at +0,+4,+8; max xyz at +0xC,+0x10,+0x14) -> half size in a1 (xyz, w = 1.0f). */
void func_0028D0F8(void *a0, void *a1) {
    u8 *b;
    u8 *o;

    b = (u8 *)a0;
    o = (u8 *)a1;
    *(f32 *)(o + 0x0) = (*(f32 *)(b + 0xC) - *(f32 *)(b + 0x0)) * 0.5f;
    *(f32 *)(o + 0x4) = (*(f32 *)(b + 0x10) - *(f32 *)(b + 0x4)) * 0.5f;
    *(f32 *)(o + 0x8) = (*(f32 *)(b + 0x14) - *(f32 *)(b + 0x8)) * 0.5f;
    *(f32 *)(o + 0xC) = 1.0f;
}
