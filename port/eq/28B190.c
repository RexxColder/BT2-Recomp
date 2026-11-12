#include "common.h"

/* 0x0028B190: bump allocator on gDmaCur (0x00387EAC). Rounds a0 down to 8 bytes,
   advances gDmaCur by it and returns the old gDmaCur. */
extern s32 D_00387EAC;

u8 *func_0028B190(s32 a0) {
    u8 *old;
    u32 n;

    old = (u8 *)D_00387EAC;
    n = ((u32)a0 >> 3) << 3;
    D_00387EAC = (s32)(old + n);
    return old;
}
