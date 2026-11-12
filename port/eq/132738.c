#include "common.h"

#define FLD_F32(p, off) (*(f32 *)((u8 *)(p) + (off)))

void *memset(void *arg0, s32 arg1, s32 arg2);
s32 func_002768D8(s32 arg0);
u8 *func_00276A28(void);
s32 func_0013A438(s32 arg0);
f32 EftSteam_SetPaused(s32 arg0, s32 arg1);
extern f32 D_00384220;
extern f32 D_00384224;
extern f32 D_00384228;

f32 EftGeyser_StartSteam(s32 arg0) {
    u8 sp[0xC0];
    u8 *s0;
    u8 *p;
    s32 ret;
    s32 r;
    s32 i;
    f32 f0;
    f32 t;

    s0 = (u8 *)*(s32 *)((u8 *)arg0 + 0x38);
    FLD_F32(sp, 0x60) = FLD_F32(s0, 0x70);
    FLD_F32(sp, 0x64) = FLD_F32(s0, 0x74);
    FLD_F32(sp, 0x68) = FLD_F32(s0, 0x78);
    FLD_F32(sp, 0x6C) = 1.0f;
    memset(sp + 0x70, 0, 0x10);
    FLD_F32(sp, 0x7C) = 1.0f;
    FLD_F32(sp, 0x80) = 128.0f;
    FLD_F32(sp, 0x84) = 128.0f;
    FLD_F32(sp, 0x88) = 128.0f;
    FLD_F32(sp, 0x8C) = 128.0f;
    FLD_F32(sp, 0x90) = 8.0f;
    FLD_F32(sp, 0x94) = D_00384220;
    FLD_F32(sp, 0x98) = D_00384224;
    *(s32 *)(sp + 0x9C) = 0x19;
    FLD_F32(sp, 0xA0) = 15.0f;
    FLD_F32(sp, 0xA4) = 0.5f;
    FLD_F32(sp, 0xA8) = 2.0f;
    FLD_F32(sp, 0xAC) = 0.5f;
    *(s32 *)(sp + 0xB0) = 5;

    /* copy sp[0x60..0xBF] to sp[0..0x5F] (raw bits) */
    for (i = 0; i < 0x60; i++) {
        sp[i] = sp[0x60 + i];
    }

    ret = func_002768D8(0xC);
    f0 = 128.0f;
    if (ret != 0) {
        p = func_00276A28();
        FLD_F32(sp, 0x20) = (f32)p[0x1A];
        FLD_F32(sp, 0x24) = (f32)p[0x1B];
        FLD_F32(sp, 0x28) = (f32)p[0x1C];
        FLD_F32(sp, 0x2C) = (f32)p[0x1D];
        FLD_F32(sp, 0x30) = FLD_F32(s0, 0xB4) / 150.0f + 8.0f;
        FLD_F32(sp, 0x38) = (FLD_F32(s0, 0xB0) / 10.0f) * D_00384228;
        t = FLD_F32(s0, 0xB4) / 150.0f + 25.0f;
        /* cvt.w.s truncates toward zero (saturating); stored as the integer bits */
        r = (s32)t;
        *(s32 *)(sp + 0x3C) = r;
        f0 = FLD_F32(s0, 0xB4) / 150.0f + 25.0f;
        if (*(s32 *)(s0 + 0xF0) == 0) {
            ret = func_0013A438((s32)sp);
            *(s32 *)(s0 + 0xF0) = ret;
            f0 = EftSteam_SetPaused(ret, 1);
        }
    }
    return f0;
}
