#include "common.h"

extern u8 *gEftWeather;

u8 *func_00146CC0(f32 *arg0) {
    if (gEftWeather != 0) {
        arg0[0] = *(f32 *)(gEftWeather + 0x220);
        arg0[1] = *(f32 *)(gEftWeather + 0x224);
        arg0[3] = 1.0f;
        arg0[2] = *(f32 *)(gEftWeather + 0x228);
    }
    return gEftWeather;
}
