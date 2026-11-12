#include "common.h"

#define W32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define S16(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define F32(p, off) (*(f32 *)((u8 *)(p) + (off)))

extern u8 *gEftGeyserMgr;
extern u8 D_0036E990[];
extern f32 D_00384D70;

void *memset(void *s, s32 c, u32 n);
void *memcpy(void *d, const void *s, u32 n);
s32 func_00208DE8(s32 a0, u8 *a1, s32 a2);
s32 func_00129C28(u8 *a0, u8 *a1);
s32 Vec4_Set(u8 *a0, f32 f12, f32 f13, f32 f14, f32 f15);
s32 Vec3_Normalize(u8 *a0, u8 *a1);
s32 EftGeyser_Create(u8 *a0, s32 a1);

s32 func_0019D4A8(u8 *obj) {
    u8 sp[0x160];
    s32 i;

    memcpy(sp, D_0036E990, 0x1C);
    memset(sp + 0xB0, 0, 0x90);
    *(u8 **)(sp + 0xB0) = gEftGeyserMgr + 0x10;
    *(u8 **)(sp + 0xB4) = obj;
    memcpy(sp + 0xC4, sp, 0x1C);
    F32(sp, 0xEC) = 128.0f;
    F32(sp, 0x124) = 1.0f;
    F32(sp, 0xE0) = 128.0f;
    F32(sp, 0xE4) = 128.0f;
    F32(sp, 0xE8) = 128.0f;
    F32(sp, 0x120) = 1.0f;

    /* four 0x20-byte rows: sp+0xB0.. -> sp+0x20.. */
    for (i = 0; i < 4; i++) {
        memcpy(sp + 0x20 + i * 0x20, sp + 0xB0 + i * 0x20, 0x20);
    }
    memcpy(sp + 0xA0, sp + 0x130, 0x10);

    func_00208DE8(S16(obj, 0x10), sp + 0x60, S16(obj, 0x14));
    func_00129C28(sp + 0x70, obj);
    Vec4_Set(sp + 0x80, D_00384D70, -0.5f, 0.0f, 1.0f);
    Vec3_Normalize(sp + 0x80, sp + 0x80);

    F32(sp, 0x90) = F32(obj, 0x20);
    F32(sp, 0x94) = F32(obj, 0x28);
    W32(sp, 0xA0) = S16(obj, 0x10);
    F32(sp, 0x40) = (f32)S16(obj, 0x1C) / 30.0f;

    /* tail call: returns EftGeyser_Create's v0; a1 is not set on this path (GUESS 0) */
    return EftGeyser_Create(sp + 0x20, 0);
}
