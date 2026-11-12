#include "common.h"

void func_0025FE58(s32 arg0, s32 arg1);
extern s32 D_00387A40;

void func_00206FE0(s32 arg0, s32 arg1) {
    s32 temp_a2;
    s32 temp_s0;
    s32 temp_v0;

    temp_a2 = *(s32 *) (arg0 + 0x142C);
    if (temp_a2 < 0) {
        return;
    }
    if (!(temp_a2 < *(s32 *) (D_00387A40 + 0xC))) {
        return;
    }
    if (arg1 < 0x1B1) {
        return;
    }
    temp_s0 = *(s32 *) (D_00387A40 + 8) + temp_a2 * 0x1520;
    func_0025FE58(temp_s0, arg1);
    temp_v0 = *(s32 *) (temp_s0 + 0xBF8);
    if ((temp_v0 == 0) || (*(u16 *) (temp_v0 + 2) == 0)) {
        *(s32 *) (temp_s0 + 0xAF0) = *(s32 *) (temp_s0 + 0xAF0) & ~2;
    }
}
