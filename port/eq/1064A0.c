#include "common.h"

s32 PauseMenu_GetMenu(s32 a0);
void BtlCur_SetByte18(s32 a0, s32 a1, s32 a2);
void BtlCur_SetByte1D(s32 a0, s32 a1, s32 a2);
void BtlCur_GetByte1D(s32 a0, s32 a1);
void func_00101EA8(s32 a0, s32 a1, s32 a2);
void func_00101F18(s32 a0, void *a1, void *a2);
extern s32 D_0033F860 __attribute__((section(".data")));
extern s32 gPauseMenuWhich;

s32 func_001064A0(void *arg0) {
    s32 frame[2];
    u8 *fb;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_v0;

    fb = (u8 *)frame;
    if (*(u8 *)((u8 *)arg0 + 0xD) != 0) {
        temp_v0 = PauseMenu_GetMenu(gPauseMenuWhich);
        BtlCur_SetByte18(temp_v0, 2, 0);
        BtlCur_SetByte18(temp_v0, 3, 0);
        BtlCur_SetByte18(temp_v0, 4, 0);
        BtlCur_SetByte18(temp_v0, 5, 0);
        BtlCur_SetByte18(temp_v0, 6, 0);
        BtlCur_SetByte18(temp_v0, 7, 0);
        BtlCur_SetByte1D(temp_v0, 2, 0);
        BtlCur_SetByte1D(temp_v0, 3, 0);
        BtlCur_SetByte1D(temp_v0, 4, 0);
        BtlCur_SetByte1D(temp_v0, 5, 0);
        BtlCur_SetByte1D(temp_v0, 6, 0);
        BtlCur_SetByte1D(temp_v0, 7, 0);
        func_00101F18(1, fb, fb + 4);
        if (fb[0] != 0) {
            var_v0 = *(s32 *)(fb + 4) + 2;
        } else {
            var_v0 = 1;
        }
        D_0033F860 = var_v0;
    }
    if (*(s32 *)(*(u8 **)arg0 + 0x1C) == 4) {
        temp_v0_2 = PauseMenu_GetMenu(gPauseMenuWhich);
        BtlCur_GetByte1D(temp_v0_2, 2);
        BtlCur_GetByte1D(temp_v0_2, 3);
        BtlCur_GetByte1D(temp_v0_2, 4);
        BtlCur_GetByte1D(temp_v0_2, 5);
        BtlCur_GetByte1D(temp_v0_2, 6);
        BtlCur_GetByte1D(temp_v0_2, 7);
        if (D_0033F860 != 1) {
            fb[0] = 1;
            *(s32 *)(fb + 4) = D_0033F860 - 2;
        } else {
            fb[0] = 0;
            *(s32 *)(fb + 4) = 0;
        }
        func_00101EA8(1, fb[0], *(s32 *)(fb + 4));
    }
    return 0;
}
