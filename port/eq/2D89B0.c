#include "common.h"

extern s32 D_003475E0 __attribute__((section(".data")));
extern s32 D_003475E4 __attribute__((section(".data")));
extern u8 D_0037AE80[] __attribute__((section(".data")));
extern u8 D_00399D68[] __attribute__((section(".data")));
extern u8 D_00399D78[] __attribute__((section(".data")));
extern u8 *D_00399D88 __attribute__((section(".data")));
extern s32 D_00399D8C __attribute__((section(".data")));

s64 func_002D89B0(void) {
    s32 g2;
    s32 cnt;
    s64 res;
    u16 a2v;
    u8 *p;

    if (D_003475E0 <= 0) {
        return 0;
    }
    g2 = D_003475E4;
    if (g2 == -1) {
        return 0;
    }
    D_00399D8C = D_00399D8C + 1;
    cnt = D_00399D8C;
    if (cnt == 1) {
        *(s64 *)D_00399D78 = *(s64 *)D_00399D68;
        *(s64 *)(D_00399D78 + 8) = *(s64 *)(D_00399D68 + 8);
        D_00399D88 = D_00399D78;
        p = *(u8 **)(D_0037AE80 + g2 * 4);
        a2v = (u16)(*(s32 *)p & 0xFFFF);
        if (a2v < *(u16 *)(D_00399D68 + 8)) {
            *(s64 *)D_00399D68 = *(s64 *)D_00399D68 + 0x10000;
        }
        *(u16 *)(D_00399D68 + 8) = a2v;
        D_00399D88 = D_00399D68;
        res = (s64)a2v + *(s64 *)D_00399D68;
    } else {
        p = *(u8 **)(D_0037AE80 + g2 * 4);
        a2v = (u16)(*(s32 *)p & 0xFFFF);
        res = (s64)a2v + *(s64 *)D_00399D88;
        if (a2v < *(u16 *)(D_00399D88 + 8)) {
            res = res + 0x10000;
        }
    }
    D_00399D8C = D_00399D8C - 1;
    return res;
}
