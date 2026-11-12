#include "common.h"

#define F32(p, off) (*(f32 *)((u8 *)(p) + (off)))

extern u8 *gBtlCamView;
extern u8 *D_00387A40;
extern f32 D_00386EA0;
extern f32 D_00386EA4;

void func_003126C8(u8 *a0, u8 *a1);
void func_00267C58(s64 a0, s32 a1);
void ObjGs_AddFrame2Alpha(s32 a0, s64 a1);
void ObjGs_AddZbufBoth(s32 a0, s32 a1);
void func_002668A8(u8 *a0, u8 *a1, f32 f12);
u8 *func_00269A40(u8 *a0, s32 a1);
void sceVu0InversMatrix(u8 *a0, u8 *a1);
void func_00312650(u8 *a0, u8 *a1, u8 *a2);
void sceVu0Normalize(u8 *a0, u8 *a1);
void func_00312FB0(f32 f12, u8 *a0, u8 *a1);
void func_00312638(u8 *a0, u8 *a1, u8 *a2);

s32 func_00264DA0(u8 *arg0, u8 *arg1) {
    u8 sp[0x70];
    s32 s2;
    s32 flags;
    u8 *s0;
    u8 *s1;
    f32 t;

    s2 = ((~*(s64 *)(arg0 + 0xAF0)) & 6) == 0 ? 0 : (s32)0xFF000000;
    flags = *(s32 *)arg1;

    if (flags & 0x10000) {
        func_003126C8(arg1 + 0x10, (u8 *)D_00387A40 + 0x38030);
        func_00267C58(s2, 0);
        goto tail_ff_62;
    }
    if ((flags & 0x20000) || (flags & 0x400000)) {
        F32(arg1, 0x10) = F32(gBtlCamView, 0x8);
        F32(arg1, 0x14) = F32(gBtlCamView, 0x18);
        F32(arg1, 0x1C) = 1.0f;
        F32(arg1, 0x18) = F32(gBtlCamView, 0x28);
        func_00267C58(s2, 0);
        goto tail_ff_62;
    }
    if (flags & 0x80000) {
        F32(arg1, 0x10) = -F32(gBtlCamView, 0x0) - F32(gBtlCamView, 0x8) * D_00386EA0;
        F32(arg1, 0x14) = -F32(gBtlCamView, 0x10) - F32(gBtlCamView, 0x18) * D_00386EA0;
        F32(arg1, 0x1C) = 1.0f;
        F32(arg1, 0x18) = -F32(gBtlCamView, 0x20) - F32(gBtlCamView, 0x28) * D_00386EA0;
        sceVu0Normalize(arg1 + 0x10, arg1 + 0x10);
        func_00267C58(s2, 0);
        goto tail_ff_48;
    }
    if (flags & 0x40000) {
        /* f12 is untouched before this jal but func_002668A8 ignores it (reads arg0+0xFC0): dead slot */
        func_002668A8(arg0, sp + 0x60, 0.0f);
        s1 = arg1 + 0x10;
        s0 = func_00269A40(arg0, 3);
        sceVu0InversMatrix(sp + 0x20, gBtlCamView);
        func_00312650(sp, sp + 0x50, s0 + 0x30);
        sceVu0Normalize(sp, sp);
        F32(sp, 0x0) = F32(sp, 0x0) + F32(gBtlCamView, 0x0) * D_00386EA4;
        F32(sp, 0x4) = F32(gBtlCamView, 0x10);
        F32(sp, 0x8) = F32(sp, 0x8) + F32(gBtlCamView, 0x20) * D_00386EA4;
        F32(sp, 0xC) = 1.0f;
        sceVu0Normalize(sp, sp);
        func_00312FB0(F32(sp, 0x60), sp, sp);
        t = 1.0f - F32(sp, 0x60);
        F32(sp, 0x10) = F32(D_00387A40, 0x38030) * t;
        F32(sp, 0x14) = F32(D_00387A40, 0x38034) * t;
        F32(sp, 0x1C) = 1.0f;
        F32(sp, 0x18) = F32(D_00387A40, 0x38038) * t;
        func_00312638(s1, sp, sp + 0x10);
        sceVu0Normalize(s1, s1);
        func_00267C58(s2, 0);
        goto tail_ff_62;
    }
    if (flags & 0x100000) {
        s2 = s2 | 0xFFFFFF;
        F32(arg1, 0x10) = F32(D_00387A40, 0x38030);
        F32(arg1, 0x14) = F32(D_00387A40, 0x38034);
        F32(arg1, 0x1C) = 1.0f;
        F32(arg1, 0x18) = F32(D_00387A40, 0x38038);
        func_00267C58(s2, 0);
        ObjGs_AddFrame2Alpha(-1, (s64)0x80 << 32 | 0x62);
        ObjGs_AddZbufBoth(0xE0, 0);
        return s2;
    }
    s2 = s2 | 0xFFFFFF;
    F32(arg1, 0x10) = F32(D_00387A40, 0x38030);
    F32(arg1, 0x14) = F32(D_00387A40, 0x38034);
    F32(arg1, 0x1C) = 1.0f;
    F32(arg1, 0x18) = F32(D_00387A40, 0x38038);
    func_00267C58(0xFFFFFF, 1);
    ObjGs_AddFrame2Alpha(-1, (s64)0x80 << 32 | 0x62);
    ObjGs_AddZbufBoth(0xE0, 1);
    return s2;

tail_ff_62:
    ObjGs_AddFrame2Alpha((s32)0xFF000000, (s64)0x80 << 32 | 0x62);
    ObjGs_AddZbufBoth(0xE0, 0);
    return s2;

tail_ff_48:
    ObjGs_AddFrame2Alpha((s32)0xFF000000, (s64)0x80 << 32 | 0x48);
    ObjGs_AddZbufBoth(0xE0, 0);
    return s2;
}
