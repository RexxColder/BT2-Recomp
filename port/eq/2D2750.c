#include "common.h"

s64 func_002D89B0(void);
s32 func_002D8AD8(void);
s64 func_002D8B00(void);
extern u8 *D_00346C20 __attribute__((section(".data")));
extern u8 D_00346C28[] __attribute__((section(".data")));
extern s64 D_00399D40 __attribute__((section(".data")));

s64 func_002D2750(void) {
    s32 sp[2];
    s32 (*temp_v0)(s32, void *, void *);

    if (func_002D8AD8() == 0) {
        D_00399D40 = func_002D8B00();
        return func_002D89B0();
    }
    if (D_00346C20 != NULL && *(s32 *)(D_00346C20 + 0x48) != 0) {
        temp_v0 = (s32 (*)(s32, void *, void *))*(void **)(D_00346C20 + 0x1004);
        if (temp_v0 != NULL) {
            temp_v0(*(s32 *)(D_00346C20 + 0x1018), sp, &sp[1]);
            D_00399D40 = (s64)sp[1];
            return sp[0];
        }
    }
    D_00399D40 = (s64)*(s32 *)(D_00346C28 + 0x1B8);
    return *(s32 *)(D_00346C28 + 0x1B0) * 0x3E8;
}
