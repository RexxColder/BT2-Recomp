#include "common.h"

void func_00129C28(s32 arg0, s32 arg1);
s32 rand(void);
f32 sinf(f32 farg0);
extern f32 D_0038452C;
extern f32 D_00384530;
extern u8 *gEftWeather;

void EftWeather_Update(void) {
    f32 f20;
    f32 f21;
    u8 *s1;

    if (gEftWeather != NULL) {
        f21 = D_00384530;
        f20 = ((f32)*(s32 *)(gEftWeather + 0x2A0) * D_0038452C) / 180.0f;
        func_00129C28((s32)(gEftWeather + 0x230), (s32)(gEftWeather + 0x220));
        s1 = gEftWeather;
        *(f32 *)(s1 + 0x230) = *(f32 *)(s1 + 0x230) + sinf(f20) * f21;
        s1 = gEftWeather;
        *(f32 *)(s1 + 0x238) = *(f32 *)(s1 + 0x238) + sinf(f20) * f21;
        s1 = gEftWeather;
        *(s32 *)(s1 + 0x2A0) = (*(s32 *)(s1 + 0x2A0) + (rand() & 3)) % 360;
    }
}
