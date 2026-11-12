#include "common.h"

u8 *func_002B61E0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002BC550(s32 arg0);
void func_002CCE40(void);
extern s32 D_00345344 __attribute__((section(".data")));
extern s32 D_00346C00 __attribute__((section(".data")));
extern s32 D_00346C04 __attribute__((section(".data")));

void func_002BCCE0(void) {
    s32 temp_s1;
    s32 temp_v0_2;
    u8 *temp_v0;

    temp_s1 = D_00345344;
    D_00346C00 += 1;
    D_00346C04 += 1;
    if (temp_s1 == 1) {
        temp_v0 = func_002B61E0(1, (s32)&D_00346C00, (s32)&D_00346C04);
        temp_v0_2 = func_002BC550((s32)(temp_v0 + 0x5C));
        if (temp_v0_2 == temp_s1) {
            if (D_00345344 == temp_v0_2) {
                func_002CCE40();
            }
            *(s32 *)(temp_v0 + 0x5C) = 0;
        }
    }
}
