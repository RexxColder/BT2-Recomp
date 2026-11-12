#include "common.h"

s32 func_003126C8(s32 arg0, s32 arg1);
s32 sceVu0CopyMatrix(s32 arg0, s32 arg1);

void Rigid_SetTransform(s32 arg0, s32 arg1, s32 arg2) {
    u8 *base;

    base = (u8 *)arg0;
    func_003126C8(arg0 + 0x40, arg1);
    sceVu0CopyMatrix(arg0 + 0x50, arg2);
    func_003126C8(arg0 + 0xF0, arg0 + 0x40);
    sceVu0CopyMatrix(arg0 + 0x100, arg0 + 0x50);
    *(s32 *)(base + 0x90) = 0;
    *(s32 *)(base + 0x140) = 0;
    *(f32 *)(base + 0xDC) = 1.0f;
    *(s32 *)(base + 0x94) = 0;
    *(s32 *)(base + 0x98) = 0;
    *(f32 *)(base + 0x9C) = 1.0f;
    *(s32 *)(base + 0xB0) = 0;
    *(s32 *)(base + 0xB4) = 0;
    *(s32 *)(base + 0xB8) = 0;
    *(f32 *)(base + 0xBC) = 1.0f;
    *(s32 *)(base + 0xC0) = 0;
    *(s32 *)(base + 0xC4) = 0;
    *(s32 *)(base + 0xC8) = 0;
    *(f32 *)(base + 0xCC) = 1.0f;
    *(s32 *)(base + 0xA0) = 0;
    *(s32 *)(base + 0xA4) = 0;
    *(s32 *)(base + 0xA8) = 0;
    *(f32 *)(base + 0xAC) = 1.0f;
    *(s32 *)(base + 0xD0) = 0;
    *(s32 *)(base + 0xD4) = 0;
    *(s32 *)(base + 0xD8) = 0;
}
