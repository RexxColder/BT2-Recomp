#include "common.h"

void func_00249510(s32 arg0, s32 arg1);
s32 func_0026EB60(u8 *arg0);
void func_0026EB78(u8 *arg0, u8 *arg1);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0);
extern u8 D_00376370[] __attribute__((section(".data")));
extern u8 *D_003879F8;
extern s32 D_003B0C34 __attribute__((section(".data")));

void func_002581F0(void) {
    s32 temp_v1;

    if ((func_0026EB60(D_003879F8 + 0x18) != 0) && (D_003B0C34 & 0x4000)) {
        temp_v1 = *(s32 *)(D_003879F8 + 0xA4);
        if (temp_v1 & 0x180) {
            *(s32 *)(D_003879F8 + 0xBC) = *(s32 *)(D_003879F8 + 0xC0);
            *(s32 *)(D_003879F8 + 0xC4) = *(s32 *)(D_003879F8 + 0xC8);
            *(s32 *)(D_003879F8 + 0xA4) = *(s32 *)(D_003879F8 + 0xA4) & ~0x180;
        } else if (temp_v1 & 0x200) {
            *(s32 *)(D_003879F8 + 0xA4) = temp_v1 | 1;
            *(s32 *)(D_003879F8 + 0xA4) = *(s32 *)(D_003879F8 + 0xA4) | 2;
            *(s32 *)(D_003879F8 + 0xAC) = 0xF;
        } else {
            *(s32 *)(D_003879F8 + 0xA4) = temp_v1 | 0x200;
            func_0026EB78(D_003879F8 + 0x18, D_00376370);
            if (*(s32 *)(D_003879F8 + 0xA4) & 0x7C) {
                func_00249510(8, -0x50);
            }
        }
        func_00297FE0(0, 1, 0x40, 0x40, 1);
    }
}
