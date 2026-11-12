#include "common.h"

extern u8 D_0036DE80[];
u8 *func_001F3758(u8 *arg0);
void func_002088F0(u8 *a0, u8 *a1);
void Mtx_StoreIdentity(u8 *m);
void Mtx_RotateY(f32 angle, u8 *dst, u8 *src);
void Vec3_Sub(u8 *out, u8 *a, u8 *b);
void func_00129C50(u8 *out, u8 *mtx, u8 *v);
void Vec3_Normalize(u8 *out, u8 *v);
u8 *EftGeyser_Create(u8 *params);
void func_0019D720(u8 *geyser);
void func_0019D6B8(u8 *geyser, s32 arg1);

/* 0x00149AE8: (task, idx) builds the parameter block of one geyser part (S = task+0x38, own = owner object's data)
 * and creates it into S+0xAC0[idx]; the last part (idx == S+0x14 - 1) additionally gets func_0019D720. The frame is
 * one buffer: template copy at sp+0, params at sp+0x20 (0x90 bytes, copied from a temp built at sp+0xB0), a matrix at
 * sp+0xC0 (overlapping the temp, as in the original) and a direction vector at sp+0x80 (inside the params). */
void func_00149AE8(u8 *task, s32 idx) {
    u8 sp[0x140];
    u8 *own = *(u8 **)(func_001F3758(task) + 0x38);
    u8 *S = *(u8 **)(task + 0x38);
    u8 *geyser;
    f32 c128;

    __builtin_memcpy(sp, D_0036DE80, 0x18);
    *(u32 *)(sp + 0x18) = *(u32 *)(D_0036DE80 + 0x18);
    c128 = 128.0f;
    *(s32 *)(sp + 0xB0) = *(s32 *)(own + 0x1E80);
    *(s32 *)(sp + 0xB4) = 0;
    *(s32 *)(sp + 0xB8) = *(s32 *)(S + 0xC0);
    *(u8 **)(sp + 0xBC) = own;
    *(u8 **)(sp + 0xC0) = S + 0x870;
    __builtin_memcpy(sp + 0xC4, sp, 0x18);
    *(u32 *)(sp + 0xDC) = *(u32 *)(sp + 0x18);
    *(f32 *)(sp + 0xE0) = c128;
    *(f32 *)(sp + 0xEC) = c128;
    *(f32 *)(sp + 0xE4) = c128;
    *(f32 *)(sp + 0xE8) = c128;
    *(u64 *)(sp + 0xF0) = *(u64 *)(S + 0x90);
    *(u64 *)(sp + 0xF8) = *(u64 *)(S + 0x98);
    *(u64 *)(sp + 0x100) = *(u64 *)(S + 0xB0);
    *(u64 *)(sp + 0x108) = *(u64 *)(S + 0xB8);
    __builtin_memset(sp + 0x110, 0, 16);
    *(f32 *)(sp + 0x120) = *(f32 *)(S + 0x18);
    *(s32 *)(sp + 0x128) = 0;
    *(f32 *)(sp + 0x124) = *(f32 *)(S + 0x20);
    *(s32 *)(sp + 0x12C) = 0;
    *(s32 *)(sp + 0x130) = **(s32 **)(S + 0xC0);
    __builtin_memcpy(sp + 0x20, sp + 0xB0, 0x90);
    Mtx_StoreIdentity(sp + 0xC0);
    func_002088F0(**(u8 ***)(S + 0xC0), sp + 0xB0);
    Mtx_RotateY(-*(f32 *)(sp + 0xB4), sp + 0xC0, sp + 0xC0);
    Vec3_Sub(sp + 0x80, S + 0x60, S + 0x70);
    func_00129C50(sp + 0x80, sp + 0xC0, sp + 0x80);
    Vec3_Normalize(sp + 0x80, sp + 0x80);
    geyser = EftGeyser_Create(sp + 0x20);
    *(u8 **)(S + 0xAC0 + idx * 4) = geyser;
    if (idx == *(s32 *)(S + 0x14) - 1) {
        func_0019D720(geyser);
    }
    func_0019D6B8(*(u8 **)(S + 0xAC0 + idx * 4), 4);
}
