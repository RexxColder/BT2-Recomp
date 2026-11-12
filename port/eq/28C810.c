#include "common.h"

extern s32 D_00387EB8;
extern s32 D_00387EC0;
extern s32 D_00387F2C;

void func_0028C810(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a3;
    s32 temp_t0;
    s32 temp_v0_2;

    temp_a3 = (s32)&D_00387EB8 + arg0 * 4;
    temp_t0 = (s32)&D_00387EC0 + arg0 * 4;
    if ((arg0 != 0 || (*(s32 *)(D_00387F2C + 0x1008) & 2) == 0) &&
        (arg0 != 1 || (*(s32 *)(D_00387F2C + 0x1008) & 4) == 0)) {
        temp_v0_2 = *(s32 *)temp_a3 + arg1;
        *(s32 *)temp_t0 = *(s32 *)temp_t0 | (arg2 != 0);
        *(s32 *)temp_a3 = temp_v0_2;
        if (temp_v0_2 >= 0x80) {
            *(s32 *)temp_a3 = 0x7F;
        }
    }
}
