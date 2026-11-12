#include "common.h"

extern u8 *gEftCam __attribute__((section(".data")));

void func_00126E90(s32 arg0) {
    if (gEftCam[0xC] != 0) {
        gEftCam[0xD] = (u8)(arg0 & 0xFF);
    }
}
