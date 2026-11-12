#include "common.h"

extern s32 D_00387AD8;
extern s32 D_00387AE4;

void func_001EEF28(s32 arg0, s32 arg1, s8 arg2, s32 arg3) {
    s32 t0 = D_00387AD8;
    s32 a1;

    D_00387AD8 += 0x30;
    *(s64 *)(t0 + 0x0) = 0xA0000002LL;
    *(s64 *)(t0 + 0x10) = (s64)0x1000000000008001ULL;
    *(s64 *)(t0 + 0x18) = 0xE;
    *(s64 *)(t0 + 0x28) = (s64)arg2 + 0x14;
    *(s64 *)(t0 + 0x20) = (s64)((arg0 & 1) << 5);
    a1 = ((arg1 * 2) + arg3) * 8 + D_00387AE4;
    *(s32 *)(*(s32 *)(a1 + 4) + 4) = t0;
    *(s32 *)(a1 + 4) = t0;
}
