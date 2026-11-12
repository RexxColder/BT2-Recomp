#include "common.h"

extern u8 *D_00387AF8;
extern u8 *D_003876A0;

/* 0x00280638: if (D_003876A0 + 0x4D8 as s64) & 3 is set, record arg0 (stride 0xBC0 from D_00387AF8) gets its bytes
 * +0x61C..+0x61F = arg1, arg2, arg3, arg4 (the fifth argument is in t0). */
void func_00280638(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *p;

    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x3) != 0) {
        p = D_00387AF8 + arg0 * 0xBC0;
        p[0x61C] = (u8)arg1;
        p[0x61D] = (u8)arg2;
        p[0x61E] = (u8)arg3;
        p[0x61F] = (u8)arg4;
    }
}
