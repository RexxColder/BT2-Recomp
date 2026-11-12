#include "common.h"

extern u8 *D_003876A0;
extern u8 D_0033F920[];
extern u8 D_0033F9D8[];
extern u8 D_0033FB68[];
extern u8 D_0033FC40[];
extern u8 D_0033FD18[];
extern u8 D_0033FF80[];
extern u8 D_0033FDB0[];
extern u8 D_0033FE68[];
extern u8 D_0033FAB0[];

/* 0x001061B8 (PauseMenu_GetMenu): arg0 == 0 -> menu table by obj+0xB8 (0..8, else NULL); arg0 == 1 -> D_0033FAB0
 * when obj+0xB8 == 0; anything else NULL. */
u8 *PauseMenu_GetMenu(s32 arg0) {
    u32 a1;
    u32 v;

    a1 = 0;
    if (arg0 == 0) {
        v = *(u32 *)(D_003876A0 + 0xB8);
        if (v < 9) {
            switch (v) {
            case 0:
            case 6:
                a1 = (u32)D_0033F920;
                break;
            case 1:
                a1 = (u32)D_0033F9D8;
                break;
            case 2:
                a1 = (u32)D_0033FB68;
                break;
            case 3:
                a1 = (u32)D_0033FC40;
                break;
            case 4:
                a1 = (u32)D_0033FD18;
                break;
            case 5:
                a1 = (u32)D_0033FF80;
                break;
            case 7:
                a1 = (u32)D_0033FDB0;
                break;
            case 8:
                a1 = (u32)D_0033FE68;
                break;
            }
        }
    } else if (arg0 == 1) {
        if (*(s32 *)(D_003876A0 + 0xB8) == 0) {
            a1 = (u32)D_0033FAB0;
        }
    }
    return (u8 *)a1;
}
