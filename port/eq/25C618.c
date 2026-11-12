#include "common.h"

void func_0025B688(s32 arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7, f32 st0, f32 st1);
extern f32 D_00386E1C;
extern f32 D_00386E20;
extern f32 D_00386E24;
extern f32 D_00386E28;
extern f32 D_00386E2C;
extern f32 D_00386E30;
extern f32 D_00386E34;

void func_0025C618(u8 *arg0) {
    f32 sp10[4];

    *(f32 *)(arg0 + 0x220) = D_00386E1C;
    sp10[1] = D_00386E20;
    sp10[2] = D_00386E24;
    sp10[3] = D_00386E28;
    sp10[0] = D_00386E20;
    func_0025B688((s32)arg0, (s32)sp10, D_00386E2C, 1.0f, D_00386E1C, 2048.0f, 2048.0f, 1.0f, D_00386E30, D_00386E34, 65536.0f, 1.0f); /* stack slots sp+0, sp+8 (0x47800000, 1.0f) */
    *(s32 *)(arg0 + 0x20C) = 0x1BF;
    *(s32 *)(arg0 + 0x204) = 0x1FF;
    *(s32 *)(arg0 + 0x200) = 0;
    *(s32 *)(arg0 + 0x208) = 0;
}
