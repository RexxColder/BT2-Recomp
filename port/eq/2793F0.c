#include "common.h"

void GfxClut_InitPacket(s32 arg0, s32 arg1);
void StgPanBlur_BuildClut(s32 arg0);
extern u8 *D_003876A0;

void func_002793F0(s32 arg0, s32 arg1) {
    u8 *base;

    base = (u8 *)arg0;
    memset((void *)arg0, 0, 0x700);
    GfxClut_InitPacket(arg0, arg1 & 0xFFFF);
    StgPanBlur_BuildClut(*(s32 *)(base + 0x490));
    *(s32 *)(base + 0x550) = 0;
    *(f32 *)(base + 0x650) = 101.0f;
    *(f32 *)(base + 0x540) = 101.0f;
    *(s32 *)(base + 0x660) = 1;
    if (*(s64 *)(D_003876A0 + 0x4D8) & 2) {
        *(s32 *)(base + 0x670) = 0x1C0;
        *(s8 *)(base + 0x6E0) = 1;
        *(s32 *)(base + 0x66C) = 0x100;
        *(s32 *)(base + 0x554) = 0;
        *(s32 *)(base + 0x558) = 0;
        *(s32 *)(base + 0x55C) = 0x100;
        *(s32 *)(base + 0x560) = 0x1C0;
        *(s32 *)(base + 0x664) = 0x100;
    } else {
        *(s32 *)(base + 0x670) = 0x1C0;
        *(s32 *)(base + 0x66C) = 0x200;
        *(s8 *)(base + 0x6E0) = 0;
        *(s32 *)(base + 0x554) = 0;
        *(s32 *)(base + 0x558) = 0;
        *(s32 *)(base + 0x55C) = 0x200;
        *(s32 *)(base + 0x560) = 0x1C0;
        *(s32 *)(base + 0x664) = 0;
    }
    *(s32 *)(base + 0x668) = 0;
}
