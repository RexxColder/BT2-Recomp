#include "common.h"

extern s32 D_003877B4;

void func_0018BE48(s32 arg0, s32 arg1) {
    s64 sp0;
    s64 sp8;
    u8 *temp_a0;
    f32 *f;

    sp8 = *(s64 *)((u8 *)arg1 + 8);
    sp0 = *(s64 *)((u8 *)arg1 + 0);
    if (D_003877B4 != 0 && arg0 != 0) {
        temp_a0 = *(u8 **)((u8 *)arg0 + 0x38);
        if (temp_a0 != 0) {
            f = (f32 *)((u8 *)&sp8 + 4);
            if (*f != 1.0f) {
                *f = 1.0f;
            }
            if (*(s32 *)(temp_a0 + 0x1D8) & 2) {
                *(s64 *)(temp_a0 + 0x60) = sp0;
                *(s64 *)(temp_a0 + 0x68) = sp8;
            }
        }
    }
}
