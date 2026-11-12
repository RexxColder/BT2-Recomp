#include "common.h"

void func_0025B688(s32 a0, void *a1, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19, f32 st0, f32 st1);
extern f32 D_00386DC8;
extern f32 D_00386DCC;
extern f32 D_00386DD0;
extern f32 D_00386DD4;
extern f32 D_00386DD8;
extern f32 D_00386DE0;
extern f32 D_00386DE4;
extern f32 D_00386DE8;
extern f32 D_00386DEC;
extern f32 D_00386DF0;
extern f32 D_00386DF4;
extern f32 D_00386DF8;
extern f32 D_00386DFC;
extern f32 D_00386E00;
extern f32 D_00386E04;
extern f32 D_00386E08;
extern f32 D_00386DDC;

void func_0025BB38(u8 *arg0, s32 arg1) {
    f32 sp10[4];

    *(f32 *)(arg0 + 0x220) = D_00386DC8;
    if (*(s32 *)(arg0 + 0x258) == 0) {
        sp10[0] = D_00386DCC;
        sp10[1] = D_00386DCC;
        sp10[2] = D_00386DD0;
        sp10[3] = D_00386DD4;
        func_0025B688((s32)arg0, (void *)sp10, D_00386DD8, 1.0f, D_00386DC8, 2048.0f, 2048.0f,
                      1.0f, D_00386DDC, D_00386DE0, 65536.0f, 1.0f);
        *(s32 *)(arg0 + 0x20C) = 0x1BF;
        *(s32 *)(arg0 + 0x204) = 0x1FF;
        *(s32 *)(arg0 + 0x200) = 0;
    } else {
        sp10[0] = D_00386DE4;
        sp10[1] = D_00386DE8;
        sp10[2] = D_00386DEC;
        sp10[3] = D_00386DF0;
        if ((arg1 & 0xFF) == 1) {
            func_0025B688((s32)arg0, (void *)sp10, D_00386DF4, 1.0f, D_00386DC8, 1920.0f, 2048.0f,
                          1.0f, D_00386DF8, D_00386DFC, 65536.0f, 1.0f);
            *(s32 *)(arg0 + 0x20C) = 0x1BF;
            *(s32 *)(arg0 + 0x204) = 0xFE;
            *(s32 *)(arg0 + 0x200) = 0;
        } else {
            func_0025B688((s32)arg0, (void *)sp10, D_00386E00, 1.0f, D_00386DC8, 2176.0f, 2048.0f,
                          1.0f, D_00386E04, D_00386E08, 65536.0f, 1.0f);
            *(s32 *)(arg0 + 0x200) = 0x101;
            *(s32 *)(arg0 + 0x20C) = 0x1BF;
            *(s32 *)(arg0 + 0x204) = 0x1FF;
        }
    }
    *(s32 *)(arg0 + 0x208) = 0;
}
