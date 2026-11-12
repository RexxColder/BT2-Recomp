#include "common.h"

extern u8 *gEftWeather;

void func_00146D60(s32 arg0) {
    if (gEftWeather != NULL) {
        *(u8 *)(gEftWeather + 0x2B0) = (u8)(arg0 & 0xFF);
    }
}
