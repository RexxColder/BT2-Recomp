#include "common.h"

s32 func_0025C618(s32 arg0);
s32 func_003126C8(s32 arg0, s32 arg1);
extern u8 D_002C3630[] __attribute__((section(".data")));
extern s32 gOrbitCam;

void func_0025C6B8(void) {
    func_0025C618(gOrbitCam + 0x30);
    func_003126C8(gOrbitCam + 0x10, (s32) D_002C3630);
    func_003126C8(gOrbitCam, (s32) D_002C3630);
    *(f32 *) (gOrbitCam + 0x20) = 10.0f;
    *(f32 *) (gOrbitCam + 0x24) = 5.0f;
    *(f32 *) (gOrbitCam + 0x28) = 500.0f;
    *(f32 *) (gOrbitCam + 0x2C) = 500.0f;
}
