#include "common.h"

extern void *gOrbitCam;

void func_0025CB70(f32 arg0, f32 arg1, f32 arg2) {
    *(f32 *)((u8 *)gOrbitCam + 0) = arg0;
    *(f32 *)((u8 *)gOrbitCam + 4) = arg1;
    *(f32 *)((u8 *)gOrbitCam + 8) = arg2;
}
