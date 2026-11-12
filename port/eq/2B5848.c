#include "common.h"

#define FLD(T, p, o) (*(T *)((u8 *)(p) + (o)))

void func_002B5848(void *arg0, void *arg1) {
    s16 temp_a2;

    temp_a2 = FLD(s16, arg0, 0xC);
    FLD(s32, arg1, 0) = FLD(s32, arg0, 8);
    FLD(s32, arg1, 0x14) = temp_a2;
    FLD(s32, arg1, 4) = FLD(s32, arg0, 0);
    FLD(s32, arg1, 0xC) = FLD(s16, arg0, 0xE);
    FLD(s32, arg1, 0x10) = temp_a2;
    FLD(s32, arg1, 8) = FLD(s32, arg0, 4);
}
