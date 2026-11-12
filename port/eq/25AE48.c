#include "common.h"

void DemoCam_SetAnim(s32 arg0, u8 *arg1);
void DemoCam_SetTime(f32 arg0);
void func_0025ABF0(void);
void func_0025AC90(u8 *arg0);
extern u8 *D_00387A40;

void func_0025AE48(s32 arg0) {
    u8 *base = *(u8 **)D_00387A40;
    u8 *s0 = base + (s32)((u32)arg0 * 0x18580U);
    s32 v0 = *(s32 *)(s0 + 0x930);

    if (v0 != 0) {
        DemoCam_SetAnim(v0, D_00387A40);
        func_0025AC90(s0);
        DemoCam_SetTime(0.0f);
        func_0025ABF0();
    }
}
