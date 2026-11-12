#include "common.h"

#define F32AT(p, off) (*(f32 *)((u8 *)(p) + (off)))

f32 sceVu0InnerProduct(s32 arg0, s32 arg1);
void sceVu0Normalize(s32 arg0, s32 arg1);
void sceVu0UnitMatrix(s32 arg0);
void func_00312490(s32 arg0, s32 arg1, s32 arg2);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void func_00312680(s32 arg0, s32 arg1, f32 farg0);
extern u8 *gBtlCamView;

void func_00141DD0(s32 arg0, s32 arg1, s32 arg2) {
    u8 sp[0x50];
    u8 *cam;
    u8 *s0;
    u8 *m;
    f32 t;
    f32 f20;

    cam = gBtlCamView;
    s0 = (u8 *)arg1;
    F32AT(sp, 0x40) = F32AT(cam, 0x8);
    F32AT(sp, 0x44) = F32AT(cam, 0x18);
    F32AT(sp, 0x48) = F32AT(cam, 0x28);
    F32AT(sp, 0x4C) = 1.0f;
    t = sceVu0InnerProduct((s32)(sp + 0x40), arg1);
    if (t < 0.0f) {
        f20 = (-t) * 0.5f;
        F32AT(sp, 0x0) = -F32AT(sp, 0x40);
        F32AT(sp, 0x4) = -F32AT(sp, 0x44);
        F32AT(sp, 0x8) = -F32AT(sp, 0x48);
        F32AT(sp, 0xC) = 1.0f;
    } else {
        f20 = t * 0.5f;
        F32AT(sp, 0x0) = F32AT(sp, 0x40);
        F32AT(sp, 0x4) = F32AT(sp, 0x44);
        F32AT(sp, 0x8) = F32AT(sp, 0x48);
        F32AT(sp, 0xC) = 1.0f;
    }
    func_00312650((s32)sp, arg1, (s32)sp);
    sceVu0Normalize((s32)sp, (s32)sp);
    func_00312680((s32)sp, (s32)sp, f20);

    F32AT(sp, 0x30) = F32AT(s0, 0x0) + F32AT(sp, 0x0);
    F32AT(sp, 0x34) = F32AT(s0, 0x4) + F32AT(sp, 0x4);
    F32AT(sp, 0x38) = F32AT(s0, 0x8) + F32AT(sp, 0x8);
    F32AT(sp, 0x3C) = 1.0f;
    sceVu0Normalize((s32)(sp + 0x30), (s32)(sp + 0x30));
    func_00312490((s32)(sp + 0x10), (s32)(sp + 0x40), (s32)(sp + 0x30));
    sceVu0Normalize((s32)(sp + 0x10), (s32)(sp + 0x10));
    func_00312490((s32)(sp + 0x20), (s32)(sp + 0x10), (s32)(sp + 0x30));
    sceVu0Normalize((s32)(sp + 0x20), (s32)(sp + 0x20));

    sceVu0UnitMatrix(arg0);
    m = (u8 *)arg0;
    F32AT(m, 0x0) = F32AT(sp, 0x10);
    F32AT(m, 0x10) = F32AT(sp, 0x20);
    F32AT(m, 0x20) = F32AT(sp, 0x30);
    F32AT(m, 0x4) = F32AT(sp, 0x14);
    F32AT(m, 0x14) = F32AT(sp, 0x24);
    F32AT(m, 0x24) = F32AT(sp, 0x34);
    F32AT(m, 0x8) = F32AT(sp, 0x18);
    F32AT(m, 0x18) = F32AT(sp, 0x28);
    F32AT(m, 0x28) = F32AT(sp, 0x38);
    F32AT(m, 0x30) = F32AT((u8 *)arg2, 0x0);
    F32AT(m, 0x34) = F32AT((u8 *)arg2, 0x4);
    F32AT(m, 0x38) = F32AT((u8 *)arg2, 0x8);
}
