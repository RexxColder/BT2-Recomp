#include "common.h"

extern u8 *D_00387B0C;

u8 *GfxWater_SetColor(s32 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4) {
    u8 *entry = D_00387B0C + arg0 * 20;
    *(u32 *)(entry + 0x10) = arg1 | (arg4 << 24) | (arg3 << 16) | (arg2 << 8);
    return entry;
}
