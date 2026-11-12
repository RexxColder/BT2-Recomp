#include "m2c_macros.h"

extern void *gEftWeather;

void func_00145B20(void *arg0) {
    M2C_FIELD(gEftWeather, f32 *, 0x2AC) = (f32) M2C_FIELD(arg0, f32 *, 0x10);
    M2C_FIELD(gEftWeather, s32 *, 0x2A4) = (s32) M2C_FIELD(arg0, u8 *, 2);
    M2C_FIELD(gEftWeather, f32 *, 0x220) = (f32) M2C_FIELD(arg0, f32 *, 4);
    M2C_FIELD(gEftWeather, f32 *, 0x224) = (f32) M2C_FIELD(arg0, f32 *, 8);
    M2C_FIELD(gEftWeather, f32 *, 0x228) = (f32) M2C_FIELD(arg0, f32 *, 0xC);
    M2C_FIELD(gEftWeather, s32 *, 0x2A8) = (s32) M2C_FIELD(arg0, u8 *, 1);
}
