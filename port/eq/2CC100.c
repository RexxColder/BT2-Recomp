#include "common.h"

void func_002C2FF0(s32 arg0, s32 arg1);
extern s32 D_00399D30 __attribute__((section(".data")));
extern u8 D_00399D38[8] __attribute__((section(".data")));

/* 0x002CC100(arg0 unused, src, obj): D_00399D30 = 1; the 8 bytes at src are copied to D_00399D38 and to
 * obj->0x1FC0 + 0x11F8; then func_002C2FF0(obj, 0xFF000F40). Returns 1. */
s32 func_002CC100(s32 arg0, u8 *arg1, u8 *arg2) {
    u8 *dst;
    s32 k;

    D_00399D30 = 1;
    for (k = 0; k < 8; k++) {
        D_00399D38[k] = arg1[k];
    }
    dst = (u8 *)*(s32 *)(arg2 + 0x1FC0) + 0x11F8;
    for (k = 0; k < 8; k++) {
        dst[k] = arg1[k];
    }
    func_002C2FF0((s32)arg2, 0xFF000F40);
    return 1;
}
