#include "common.h"

s32 BtlCharApi_IsInTechnique(s32 arg0);
void DemoCam_SetTime(f32 farg0);
void DemoCam_Stop(void);
f32 func_0020A2F8(s32 arg0);
f32 func_0025AAD0(void);
f32 func_0025AAF0(s32 arg0);
extern u8 *D_003876A0;
extern u8 *gEftCam;

void func_00126F08(void) {
    f32 f20;
    f32 f0;
    f32 f1;
    s32 temp_a0;

    f20 = 0.0f;
    if (gEftCam[0xC] != 0 && gEftCam[0xD] == 0 && !(*(s64 *)(D_003876A0 + 0x4D8) & 0x100)) {
        temp_a0 = *(s32 *)(gEftCam + 0x10);
        if (temp_a0 != -1) {
            if (BtlCharApi_IsInTechnique(temp_a0) != 0) {
                if (*(s32 *)(gEftCam + 8) == 0x61) {
                    f0 = func_0020A2F8(*(s32 *)(gEftCam + 0x10));
                    f1 = 1.0f;
                    f20 = f0 + f1;
                } else {
                    f0 = func_0020A2F8(*(s32 *)(gEftCam + 0x10));
                    f20 = f0 + f20;
                }
            }
        } else {
            f0 = func_0025AAF0(temp_a0);
            f1 = 2.0f;
            f20 = f0 + f1;
        }
        if (func_0025AAD0() < f20) {
            DemoCam_SetTime(func_0025AAD0());
            if (gEftCam[0xE] == 0) {
                DemoCam_Stop();
                gEftCam[0xC] = 0;
            }
        } else {
            DemoCam_SetTime(f20);
        }
    }
}
