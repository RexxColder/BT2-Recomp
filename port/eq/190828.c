#include "common.h"

extern f32 D_00384C30;
extern s32 D_003877BC;

void func_00190828(s32 arg0, f32 farg0) {
    u8 *temp;

    if (D_003877BC != 0 && arg0 != 0) {
        temp = (u8 *)*(s32 *)((u8 *)arg0 + 0x38);
        if (temp != 0 && (*(u16 *)(temp + 0x44) & 2)) {
            if (farg0 <= 0.0f) {
                farg0 = D_00384C30;
            }
            *(f32 *)(temp + 0x30) = farg0;
        }
    }
}
