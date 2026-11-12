#include "common.h"

extern void *gOrbitCam;

void func_0025CB50(f32 arg0, f32 arg1, f32 arg2) {
    *(f32 *)((u8 *)gOrbitCam + 0x10) = arg0;
    *(f32 *)((u8 *)gOrbitCam + 0x14) = arg1;
    *(f32 *)((u8 *)gOrbitCam + 0x18) = arg2;
}
