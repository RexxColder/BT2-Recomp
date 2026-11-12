#include "common.h"

void func_0026EA88(void *arg0);
void func_0026EAE0(void *arg0, s32 arg1);
void func_0026EB78(void *arg0, void *arg1);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern u8 *D_00387DA0;
extern u8 D_00387DA8[];

void func_0029C550(s32 arg0) {
    s32 temp_v0;

    if (arg0 != 0) {
        temp_v0 = *(s32 *)(D_00387DA0 + 0x54);
        if (temp_v0 & 8) {
            return;
        }
        *(s32 *)(D_00387DA0 + 0x54) = temp_v0 | 8;
        *(s32 *)(D_00387DA0 + 0x54) = *(s32 *)(D_00387DA0 + 0x54) & ~4;
        func_0026EB78(D_00387DA0 + 8, D_00387DA8);
        func_00297FE0(0, 5, 0x40, 0x40, 1);
        return;
    }
    if (!(*(s32 *)(D_00387DA0 + 0x54) & 4)) {
        *(s32 *)(*(u8 **)(D_00387DA0 + 0x50) + 0x34) = 0;
        *(s32 *)(D_00387DA0 + 0x54) = 4;
        *(s32 *)(D_00387DA0 + 0x58) = *(s32 *)(D_00387DA0 + 0x60);
        func_0026EAE0(D_00387DA0 + 8, 0x3C);
        func_0026EA88(D_00387DA0 + 8);
        func_00297FE0(0, 4, 0x40, 0x40, 1);
    }
}
