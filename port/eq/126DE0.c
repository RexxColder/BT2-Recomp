#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
s32 DemoCam_SetAnim(s32 arg0);
void DemoCam_SetTime(f32 arg0);
void func_0025ABC8(void);
void func_0025AC90(s32 arg0);
extern u8 *gEftCam;
extern u8 *D_00387A40;

/* 0x00126DE0(p): the 12 bytes at p are copied to gEftCam; DemoCam_SetAnim(p[0]); when p[1] != -1, func_0025AC90
 * (*D_00387A40 + p[1] * 0x18580); DemoCam_SetTime(0.0f); func_0025ABC8(); gEftCam +0x10 = p[1], +0xC = 1 (byte),
 * +0xE = 0 (byte). */
void func_00126DE0(u8 *arg0) {
    s32 a1v;

    memcpy(gEftCam, arg0, 12);
    DemoCam_SetAnim(*(s32 *)arg0);
    if (*(s32 *)(arg0 + 4) != -1) {
        a1v = (s32)((u32)*(s32 *)(arg0 + 4) * 0x18580u);
        func_0025AC90(*(s32 *)D_00387A40 + a1v);
    }
    DemoCam_SetTime(0.0f);
    func_0025ABC8();
    *(s32 *)(gEftCam + 0x10) = *(s32 *)(arg0 + 4);
    gEftCam[0xC] = 1;
    gEftCam[0xE] = 0;
}
