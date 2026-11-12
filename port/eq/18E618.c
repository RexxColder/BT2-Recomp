#include "common.h"

void func_0018E618(s32 arg0, s32 arg1) {
    u8 *dst;
    u8 *src;
    s32 i;
    s32 off;

    dst = (u8 *)arg0;
    src = (u8 *)arg1;
    memset((void *)arg0, 0, 0xB4);
    i = 0;
    do {
        off = i * 4;
        i += 1;
        *(s32 *)(dst + 4 + off) = *(s32 *)(src + 4 + off);
        *(s32 *)(dst + 0x10 + off) = *(s32 *)(src + 0x10 + off);
        *(s32 *)(dst + 0x1C + off) = *(s32 *)(src + 0x1C + off);
        *(s32 *)(dst + 0x28 + off) = *(s32 *)(src + 0x28 + off);
    } while (i < 3);
    *(s32 *)(dst + 0) = 1;
    *(f32 *)(dst + 0x34) = *(f32 *)(src + 0x34);
    *(f32 *)(dst + 0x38) = *(f32 *)(src + 0x38);
    *(f32 *)(dst + 0x3C) = *(f32 *)(src + 0x3C);
    *(f32 *)(dst + 0x40) = *(f32 *)(src + 0x40);
    *(f32 *)(dst + 0x44) = *(f32 *)(src + 0x44);
    *(f32 *)(dst + 0x48) = *(f32 *)(src + 0x48);
    *(f32 *)(dst + 0x4C) = *(f32 *)(src + 0x4C);
    *(f32 *)(dst + 0x50) = *(f32 *)(src + 0x50);
    *(f32 *)(dst + 0x54) = *(f32 *)(src + 0x54);
    *(f32 *)(dst + 0x58) = *(f32 *)(src + 0x58);
    *(f32 *)(dst + 0x5C) = *(f32 *)(src + 0x5C);
    *(f32 *)(dst + 0x60) = *(f32 *)(src + 0x60);
    *(f32 *)(dst + 0x64) = *(f32 *)(src + 0x64);
    *(f32 *)(dst + 0x6C) = 1.0f;
    *(s32 *)(dst + 0x68) = 0;
    *(f32 *)(dst + 0x70) = *(f32 *)(src + 0x70);
    *(f32 *)(dst + 0x74) = *(f32 *)(src + 0x74);
    *(f32 *)(dst + 0x78) = *(f32 *)(src + 0x78);
    *(f32 *)(dst + 0x7C) = *(f32 *)(src + 0x7C);
    *(f32 *)(dst + 0x80) = *(f32 *)(src + 0x80);
    *(f32 *)(dst + 0x84) = *(f32 *)(src + 0x84);
    *(f32 *)(dst + 0x88) = *(f32 *)(src + 0x88);
    *(f32 *)(dst + 0x8C) = *(f32 *)(src + 0x8C);
    *(f32 *)(dst + 0x90) = *(f32 *)(src + 0x90);
    *(f32 *)(dst + 0x94) = *(f32 *)(src + 0x94);
    *(s32 *)(dst + 0x9C) = *(s32 *)(src + 0x9C);
    *(s32 *)(dst + 0xA0) = *(s32 *)(src + 0xA0);
    *(s32 *)(dst + 0xA4) = *(s32 *)(src + 0xA4);
    *(u8 *)(dst + 0xA8) = *(u8 *)(src + 0xA8);
    *(u8 *)(dst + 0xA9) = *(u8 *)(src + 0xA9);
    *(u8 *)(dst + 0xAA) = *(u8 *)(src + 0xAA);
    *(s32 *)(dst + 0xAC) = *(s32 *)(src + 0xAC);
    *(s32 *)(dst + 0xB0) = *(s32 *)(src + 0xB0);
}
