#include "common.h"

void func_002F3378(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002F3390(void);

/* 0x002F1880: func_002F3378(arg0, arg1, arg2, arg3, arg4) first. Then the object arg0 gets: word +8 = arg1, +0xC = arg2,
 * +0x2C = 0x200, +0x5C = 0xFFFFF, +0x30 = +0x14 = q = ceil(arg3 / 2048), byte +1 = 1, byte +2 = 0, +4 = arg4,
 * +0x10 = arg3, word +0x58 = 0. When arg4 is non-null, its virtual slot +0x24 is called as (arg4, 0) and (arg4, 1)
 * and the sum is stored at +0x18, +0x1C and +0x40. Then byte +0 = 1, byte +0x44 = 0, and func_002F3390() is tail
 * called (no arguments). */
void func_002F1880(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4) {
    s32 t;
    s32 q;
    s32 rem;
    s32 sum;

    func_002F3378((s32)arg0, arg1, arg2, arg3, (s32)arg4);
    t = (arg3 < 0) ? arg3 + 0x7FF : arg3;
    q = t >> 11;
    rem = arg3 - (q << 11);
    q += (rem > 0);
    *(s32 *)(arg0 + 0x08) = arg1;
    *(s32 *)(arg0 + 0x0C) = arg2;
    *(s32 *)(arg0 + 0x2C) = 0x200;
    *(s32 *)(arg0 + 0x5C) = 0xFFFFF;
    *(s32 *)(arg0 + 0x30) = q;
    arg0[1] = 1;
    arg0[2] = 0;
    *(s32 *)(arg0 + 0x04) = (s32)arg4;
    *(s32 *)(arg0 + 0x10) = arg3;
    *(s32 *)(arg0 + 0x14) = q;
    *(s32 *)(arg0 + 0x58) = 0;
    if (arg4 != NULL) {
        sum = (*(s32 (**)(u8 *, s32))(*(u8 **)arg4 + 0x24))(arg4, 0);
        sum += (*(s32 (**)(u8 *, s32))(*(u8 **)arg4 + 0x24))(arg4, 1);
        *(s32 *)(arg0 + 0x1C) = sum;
        *(s32 *)(arg0 + 0x40) = sum;
        *(s32 *)(arg0 + 0x18) = sum;
    }
    arg0[0] = 1;
    arg0[0x44] = 0;
    ((void (*)(void))func_002F3390)();
}
