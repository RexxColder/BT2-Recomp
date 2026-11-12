#include "common.h"

extern u8 *D_00387AD8;
extern s32 D_00387AE4;

void func_001EF2E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *t0;
    s32 bflag;
    s64 v0;

    t0 = D_00387AD8;
    bflag = arg1 != 0;
    D_00387AD8 = t0 + 0x60;
    if (t0 != NULL) {
        *(s64 *)(t0 + 0x28) = bflag + 0x42;
        *(s64 *)(t0 + 0x58) = bflag + 0x4A;
        *(s64 *)(t0 + 0x0) = (s64)0xA0000005ULL;
        *(s64 *)(t0 + 0x10) = (s64)0x1000000000008004ULL;
        *(s64 *)(t0 + 0x18) = 0xE;
        *(s64 *)(t0 + 0x38) = 0x49;
        *(s64 *)(t0 + 0x48) = 0x3B;
        if (arg3 == 1 || arg3 == 0 || arg3 == 2) {
            if (arg3 == 1) {
                v0 = 0x48;
            } else if (arg3 == 0) {
                v0 = 0x44;
            } else {
                v0 = 0x42;
            }
            *(s64 *)(t0 + 0x20) = v0;
        }
        *(s64 *)(t0 + 0x30) = 0;
        *(s64 *)(t0 + 0x50) = 0;
        *(s64 *)(t0 + 0x40) = (s64)0x7F0000807FULL;
        {
            u8 *e;

            e = (u8 *)(D_00387AE4 + ((arg0 * 2) + arg2) * 8);
            *(s32 *)(*(s32 *)(e + 4) + 4) = (s32)t0;
            *(s32 *)(e + 4) = (s32)t0;
        }
    }
}
