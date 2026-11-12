#include "common.h"

void func_00267550(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_00387A40;

void func_00207208(s32 arg0, s32 arg1) {
    s32 temp_v1;

    temp_v1 = *(s32 *)(arg0 + 0x142C);
    if (temp_v1 >= 0) {
        if (temp_v1 < *(s32 *)(D_00387A40 + 0xC)) {
            func_00267550(*(s32 *)(D_00387A40 + 8) + (temp_v1 * 0x1520), 2, arg1, D_00387A40);
        }
    }
}
