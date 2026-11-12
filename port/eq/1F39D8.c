#include "common.h"

extern s32 gEftVram;

u64 EftVram_AddClut(s32 arg0) { /* the asm returns lwu: zero-extended 64-bit */
    s32 idx;
    u32 temp_v0;

    idx = *(s32 *) (gEftVram + 0x800);
    *(s32 *) (gEftVram + idx * 4) = arg0;
    *(s32 *) (gEftVram + idx * 4 + 0x200) = 0;
    *(u32 *) (gEftVram + idx * 4 + 0x400) = *(u32 *) (gEftVram + 0x808);
    *(s32 *) (gEftVram + idx * 4 + 0x600) = 2;
    temp_v0 = *(u32 *) (gEftVram + 0x808);
    *(u32 *) (gEftVram + 0x808) = *(u32 *) (gEftVram + 0x808) + *(u32 *) (*(s32 *) (arg0 + 8) + 0x14);
    *(s32 *) (gEftVram + 0x800) = *(s32 *) (gEftVram + 0x800) + 1;
    return (u64)temp_v0;
}
