#include "common.h"

extern u8 D_0036E380[];

extern u8 *func_001F3758(void *a0);
extern void func_002088F0(s32 a0, u8 *a1);
extern void Mtx_StoreIdentity(u8 *m);
extern void Mtx_RotateY(u8 *dst, u8 *src, f32 ang);
extern void Vec3_Sub(u8 *dst, u8 *a, u8 *b);
extern void Mtx_MulVec4(u8 *dst, u8 *m, u8 *v);
extern void Vec3_Normalize(u8 *dst, u8 *src);
extern s32 EftGeyser_Create(u8 *cfg);
extern void func_0019D720(s32 a0);
extern void func_0019D6B8(s32 a0, s32 a1);
extern void *memset();

/* Spawns geyser effect number `idx` for the object `obj`: builds a 0x84-byte config block on the stack,
   creates the geyser and stores the handle at obj->data + 0xAC0 + idx*4. */
void func_0015E800(u8 *obj, s32 idx) {
    u8 sp[0x170];
    u8 *cam = func_001F3758(obj);
    u8 *d = *(u8 **)(obj + 0x38);
    u8 *camData = *(u8 **)(cam + 0x38);
    u8 *slot;
    s32 handle;
    s32 i;
    f32 tmp[8];
    u8 *src;
    u8 *dst;

    __builtin_memcpy(tmp, D_0036E380, 0x1C);

    *(s32 *)(sp + 0xB0) = *(s32 *)(camData + 0x1E80);
    *(s32 *)(sp + 0xB4) = 0;
    *(s32 *)(sp + 0xB8) = *(s32 *)(d + 0xC0);
    *(u8 **)(sp + 0xBC) = camData;
    *(u8 **)(sp + 0xC0) = d + 0x870;
    __builtin_memcpy(sp + 0xC4, tmp, 0x1C);
    *(f32 *)(sp + 0xE0) = 128.0f;
    *(f32 *)(sp + 0xEC) = 128.0f;
    *(f32 *)(sp + 0xE4) = 128.0f;
    *(f32 *)(sp + 0xE8) = 128.0f;
    *(u64 *)(sp + 0xF0) = *(u64 *)(d + 0x90);
    *(u64 *)(sp + 0xF8) = *(u64 *)(d + 0x98);
    *(u64 *)(sp + 0x100) = *(u64 *)(d + 0xB0);
    *(u64 *)(sp + 0x108) = *(u64 *)(d + 0xB8);
    __builtin_memset(sp + 0x110, 0, 0x10);
    *(f32 *)(sp + 0x120) = *(f32 *)(d + 0x18);
    *(f32 *)(sp + 0x124) = *(f32 *)(d + 0x20);
    *(s32 *)(sp + 0x128) = 0;
    *(s32 *)(sp + 0x12C) = 0;
    *(s32 *)(sp + 0x130) = **(s32 **)(d + 0xC0);

    __builtin_memcpy(sp + 0x20, sp + 0xB0, 0x90);

    Mtx_StoreIdentity(sp + 0xC0);
    func_002088F0(**(s32 **)(d + 0xC0), sp + 0xB0);
    Mtx_RotateY(sp + 0xC0, sp + 0xC0, -*(f32 *)(sp + 0xB4));
    Vec3_Sub(sp + 0x80, d + 0x60, d + 0x70);
    Mtx_MulVec4(sp + 0x80, sp + 0xC0, sp + 0x80);
    Vec3_Normalize(sp + 0x80, sp + 0x80);
    handle = EftGeyser_Create(sp + 0x20);
    slot = d + 0xAC0 + idx * 4;
    *(s32 *)slot = handle;
    if (idx == *(s32 *)(d + 0x14) - 1) {
        func_0019D720(handle);
    }
    func_0019D6B8(*(s32 *)slot, 4);
}
