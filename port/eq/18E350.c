#include "common.h"

extern f32 D_00384C18;
extern s32 D_003877B8;

void func_0018E350(s32 arg0, f32 farg0) {
    u8 *temp;

    if (D_003877B8 != 0 && arg0 != 0) {
        temp = (u8 *)*(s32 *)((u8 *)arg0 + 0x38);
        if (temp != 0 && (*(u16 *)(temp + 0x56) & 2)) {
            if (farg0 <= 0.0f) {
                farg0 = D_00384C18;
            }
            *(f32 *)(temp + 0x30) = farg0;
        }
    }
}
