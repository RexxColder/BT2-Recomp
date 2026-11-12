#include "common.h"

void BtlCur_SetByte18(s32 arg0, s32 arg1, s32 arg2);
s32 PauseMenu_GetMenu(s32 arg0);
extern s32 D_0033F640 __attribute__((section(".data")));
extern s32 gPauseMenuWhich;

s32 func_001062B0(u8 *arg0) {
    s32 menu;

    if (arg0[0xD] != 0) {
        menu = PauseMenu_GetMenu(gPauseMenuWhich);
        BtlCur_SetByte18(menu, 1, 0);
        BtlCur_SetByte18(menu, 0, 0);
        D_0033F640 = 2;
    }
    return 0;
}
