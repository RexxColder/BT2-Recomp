#include "common.h"

s32 func_002F9280(s32 arg0, s32 arg1);
void func_002D8C60(s32 arg0, s32 arg1);
extern s32 D_003475E0 __attribute__((section(".data")));
extern s32 D_003475E4 __attribute__((section(".data")));
extern s32 D_003475E8 __attribute__((section(".data")));
extern u8 D_0037AE70[] __attribute__((section(".data")));
extern u8 D_0037AE80[] __attribute__((section(".data")));
extern u8 D_0037AE90[] __attribute__((section(".data")));
extern u8 D_0037AE98[] __attribute__((section(".data")));
extern u8 D_00399D68[] __attribute__((section(".data")));
extern u8 D_00399D78[] __attribute__((section(".data")));
extern u8 *D_00399D88 __attribute__((section(".data")));
extern s32 D_00399D8C __attribute__((section(".data")));

void func_002D87E8(s32 arg0) {
    s32 sp[2];
    s32 s0;
    s32 a1;
    s32 v;
    s32 *pa;
    s32 *pe;

    v = func_002F9280((s32)D_0037AE90, (s32)sp);
    s0 = arg0;
    if (v == 0) {
        s0 = sp[0];
    }
    D_003475E0 += 1;
    if (!(D_003475E0 >= 2 && D_003475E4 == s0)) {
        D_003475E4 = s0;
        if (s0 == -1) {
            func_002D8C60(1, sp[0]);
            return;
        }
        v = func_002F9280((s32)D_0037AE98, (s32)sp);
        func_002D8C60((v == 0) ? (s32)(u32)sp[0] : 0x8CA00, 0);
        a1 = s0 << 2;
        pa = *(s32 **)(D_0037AE70 + a1);
        v = *pa;
        D_003475E8 = v;
        if ((v & 0xC7) != 0x82) {
            pe = *(s32 **)(D_0037AE80 + a1);
            *pe = 0;
            *pa = 0x82;
        }
        pe = *(s32 **)(D_0037AE80 + a1);
        *(s16 *)(D_00399D68 + 8) = (s16)*pe;
        *(s64 *)(D_00399D68 + 0) = 0;
        *(s64 *)(D_00399D78 + 0) = *(s64 *)(D_00399D68 + 0);
        *(s64 *)(D_00399D78 + 8) = *(s64 *)(D_00399D68 + 8);
        D_00399D88 = D_00399D68;
        D_00399D8C = 0;
    }
}
