#include "common.h"

extern f32 D_00384634;

void func_00129C28(s32 arg0, s32 arg1);
s32 EftChain_Create(s32 arg0);
void func_001A4A58(s32 arg0, f32 farg0);
void func_001A4A90(s32 arg0, f32 farg0);
void func_001A4B20(s32 arg0, s32 arg1);
void func_001A4920(s32 arg0, s32 arg1);
void func_001A4A20(s32 arg0, f32 farg0);
void func_001A4968(s32 arg0, s32 arg1);
s32 func_001A48C0(s32 arg0);
s32 func_001A4888(s32 arg0);
void func_0012A360(s32 arg0, s32 arg1, s32 arg2, f32 farg0);

/* Creates a chain object in *out when flags bit 0 is set and *out is empty, then runs
   the requested update steps (bits 3..1) on it. */
s32 func_0014FD40(u8 *self, u8 *src, u32 a2, u32 a3, s32 *out, s32 flags, s32 a7, s32 a8,
                  f32 unused_f12, f32 fb, f32 fc, s32 a11) {
    u8 fr[0x90];
    f32 scale;

    if ((flags & 1) != 0 && *out == 0) {
        __builtin_memset(fr + 0x60, 0, 0x10);
        *(s32 *)(fr + 0x50) = a7;
        *(f32 *)(fr + 0x54) = fc;
        __builtin_memset(fr + 0x70, 0, 0x10);
        *(s32 *)(fr + 0x80) = (s32)src[3];
        *(s32 *)(fr + 0x84) = (s32)self + 0x2E8;
        *(s32 *)(fr + 0x88) = (s32)a2;
        *(s32 *)(fr + 0x8C) = (s32)a3;
        __builtin_memcpy(fr + 0x10, fr + 0x50, 0x10);
        __builtin_memcpy(fr + 0x20, fr + 0x60, 0x10);
        __builtin_memcpy(fr + 0x30, fr + 0x70, 0x10);
        __builtin_memcpy(fr + 0x40, fr + 0x80, 0x10);

        func_00129C28((s32)(fr + 0x20), a8);
        func_00129C28((s32)(fr + 0x30), a11);
        *out = EftChain_Create((s32)(fr + 0x10));

        func_001A4A58(*out, (f32)src[0x15]);
        func_001A4A90(*out, (f32)src[4]);
        func_001A4B20(*out, 1);
    }

    if (*out == 0) {
        return flags & 8;
    }

    if ((flags & 8) != 0) {
        scale = (f32)(s16)*(s16 *)(src + 0x18) * D_00384634 * fb + 1.0f;
        func_0012A360((s32)fr, a11, a8, scale);
        *(f32 *)(fr + 0xC) = 1.0f;
        func_001A4920(*out, (s32)fr);
    }
    if ((flags & 0x20) != 0) {
        func_001A4A20(*out, fc);
    }
    if ((flags & 0x40) != 0) {
        func_001A4968(*out, a11);
    }
    if ((flags & 4) != 0) {
        s32 result = func_001A48C0(*out);
        *out = 0;
        return result;
    }
    if ((flags & 2) != 0) {
        return func_001A4888(*out);
    }
    return 0;
}
