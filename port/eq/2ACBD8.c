#include "common.h"

s32 func_002AC668(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3);
extern u8 D_003B2600[] __attribute__((section(".data")));
extern s32 D_00344F30[] __attribute__((section(".data")));

/* 0x002ACBD8: advance the state record at D_003B2600 (+0 index, +4 counter, +0x54 flags, +0x58 source id).
   Table D_00344F34 has 16-byte rows whose first word is the counter limit for each index. If counter + 1
   matches the limit of the current row, the counter advances, flag 0x40000 is set and the 0x4C-byte record at
   +0x3C0 is copied to +0x8. Otherwise func_002AC668 gives a new index and counter; a non-zero result must
   match the new row's limit, or the call returns 1 with nothing changed. Both paths end by returning 1. */
s32 func_002ACBD8(void) {
    u8 *g = D_003B2600;
    u8 *tbl = (u8 *)D_00344F30 + 4;
    u8 *src = g + 0x3C0;
    u8 *dst = g + 0x08;
    s32 v20;
    s32 v21;
    s32 v22;
    s32 idx;
    s32 counter;

    idx = *(s32 *)g;
    counter = *(s32 *)(g + 0x4);

    if (counter + 1 == *(s32 *)(tbl + idx * 16)) {
        *(s32 *)(g + 0x4) = counter + 1;
        *(u32 *)(g + 0x54) |= 0x40000u;
        __builtin_memcpy(dst, src, 0x4C);
        return 1;
    }

    func_002AC668(*(s32 *)(g + 0x58), &v20, &v21, &v22);
    if (v22 != 0) {
        if (v21 + 1 != *(s32 *)(tbl + v20 * 16)) {
            return 1;
        }
    }
    *(s32 *)(g + 0x4) = v21;
    *(s32 *)g = v20;
    __builtin_memcpy(dst, src, 0x4C);
    return 1;
}
