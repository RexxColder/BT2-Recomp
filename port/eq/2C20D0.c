#include "common.h"

void func_002C20D0(s32 arg0, s32 arg1) {
    u8 temp_v0;
    u8 temp_a2;
    u8 temp_a3;

    temp_v0 = *(u8 *) (arg1 + 3);
    temp_a2 = *(u8 *) (arg1 + 2);
    temp_a3 = *(u8 *) (arg1 + 1);
    *(s8 *) (arg0 + 0xA) = (s8) (temp_v0 & 3);
    *(s8 *) (arg0 + 0) = (s8) ((temp_a3 >> 1) & 3);
    *(s8 *) (arg0 + 1) = (s8) (temp_a3 & 1);
    *(s8 *) (arg0 + 2) = (s8) (temp_a2 >> 4);
    *(s8 *) (arg0 + 3) = (s8) ((temp_a2 >> 2) & 3);
    *(s8 *) (arg0 + 4) = (s8) ((temp_a2 >> 1) & 1);
    *(s8 *) (arg0 + 5) = (s8) (temp_a2 & 1);
    *(s8 *) (arg0 + 6) = (s8) (temp_v0 >> 6);
    *(s8 *) (arg0 + 7) = (s8) ((temp_v0 >> 4) & 3);
    *(s8 *) (arg0 + 8) = (s8) ((temp_v0 >> 3) & 1);
    *(s8 *) (arg0 + 9) = (s8) ((temp_v0 >> 2) & 1);
}
