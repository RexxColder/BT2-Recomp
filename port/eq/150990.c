#include "common.h"

extern void *memset(void *dst, s32 c, u32 n);
extern void *memcpy(void *dst, const void *src, u32 n);
extern f32 D_00384648;
extern f32 D_0038464C;

s32 EftPtcl3_Create(s32 arg0);
void EftPtcl3_SetStartDelay(s32 arg0, f32 farg0);
void EftPtcl3_SetStopDelay(s32 arg0, f32 farg0);
void EftPtcl3_SetFront(s32 arg0);
void EftPtcl3_SetFlag80(s32 arg0, s32 arg1);
void EftPtcl3_SetType(s32 arg0, s32 arg1);
void EftPtcl3_SetPolys(s32 arg0, s32 arg1);
void EftPtcl3_SetPos(s32 arg0, void *arg1);
void EftPtcl3_Warp(s32 arg0, void *arg1);
void EftPtcl3_SetSize(s32 arg0, f32 farg0);
void EftPtcl3_SetDir(s32 arg0, s32 arg1);
void EftPtcl3_Kill(s32 arg0);
void EftPtcl3_Stop(s32 arg0);
s32 func_001F4588(void);
void func_0012A360(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
void func_00129C28(s32 arg0, s32 arg1);

/* 0x00150990 (particle emitter update): desc holds emitter parameters (halfword scale at +0x18, start/stop delay bytes
 * at +0x15 and +4, flag bytes at +3 and +7). flags bit 0 creates the particle when *outp is empty (creation parameter
 * block at frame+0x10 is built from farg0/farg1, src+8, arg2, arg3, arg6 and the position from func_0012A360). With a
 * live particle, bit 3 refreshes its position, bit 0x10 warps instead of SetPos, bit 0x20 sets size (farg1), bit 0x40
 * sets dir (arg8), bit 0x4 kills and clears *outp, bit 0x2 stops. Returns flags & 8 when no particle. */
s32 func_00150990(u8 *desc, u8 *src, s32 arg2, s32 arg3, s32 *outp, s32 flags, s32 arg6, s32 arg7,
                  f32 farg0, f32 farg1, f32 farg2, s32 arg8) {
    u8 frame[0xB0];
    f32 scale;

    if ((flags & 1) != 0 && *outp == 0) {
        *(f32 *)(frame + 0x60) = farg0;
        *(f32 *)(frame + 0x64) = farg1;
        memset(frame + 0x70, 0, 0x10);
        memset(frame + 0x80, 0, 0x10);
        *(s32 *)(frame + 0x90) = desc[3];
        *(s32 *)(frame + 0x94) = (s32)(src + 8);
        *(s32 *)(frame + 0x98) = arg2;
        *(s32 *)(frame + 0x9C) = arg3;
        *(s32 *)(frame + 0xA0) = arg6;
        memcpy(frame + 0x10, frame + 0x60, 0x50);

        scale = (f32)*(s16 *)(desc + 0x18) * D_00384648 * farg2;
        func_0012A360((s32)(frame + 0x20), arg8, arg7, scale);
        *(f32 *)(frame + 0x2C) = 1.0f;
        func_00129C28((s32)(frame + 0x30), arg8);

        *outp = EftPtcl3_Create((s32)(frame + 0x10));
        EftPtcl3_SetStartDelay(*outp, (f32)desc[0x15]);
        EftPtcl3_SetStopDelay(*outp, (f32)desc[4]);
        if ((desc[7] & 0x20) != 0) {
            EftPtcl3_SetFront(*outp);
        }
        if ((flags & 0x80) != 0) {
            EftPtcl3_SetFlag80(*outp, 1);
        }
        EftPtcl3_SetType(*outp, 1);
        if (func_001F4588() != 0) {
            EftPtcl3_SetPolys(*outp, 1);
        }
    }

    if (*outp == 0) {
        return flags & 8;
    }

    if ((flags & 8) != 0) {
        scale = (f32)*(s16 *)(desc + 0x18) * D_0038464C * farg2;
        func_0012A360((s32)frame, arg8, arg7, scale);
        *(f32 *)(frame + 0xC) = 1.0f;
        if ((flags & 0x10) != 0) {
            EftPtcl3_Warp(*outp, frame);
        } else {
            EftPtcl3_SetPos(*outp, frame);
        }
    }

    if ((flags & 0x20) != 0) {
        EftPtcl3_SetSize(*outp, farg1);
    }
    if ((flags & 0x40) != 0) {
        EftPtcl3_SetDir(*outp, arg8);
    }
    if ((flags & 4) != 0) {
        EftPtcl3_Kill(*outp);
        *outp = 0;
        return 0;
    }
    if ((flags & 2) != 0) {
        EftPtcl3_Stop(*outp);
    }
    return 0;
}
