#include "common.h"

void *EftHit_GetNew(void);
s32 EftHitArena_AllocBox(void);
void ColCapsule_Set(f32 farg0, s32 arg0, s32 arg1, s32 arg2);
void EftHit_SetShapeBoxes(s32 arg0, s32 arg1, s32 arg2);
void func_00127128(s32 arg0);

void func_001B05A0(s32 arg0) {
    u8 *hit;
    u8 *src;
    u8 *cap2;
    s32 box1;
    s32 box0;

    hit = (u8 *)EftHit_GetNew();
    src = *(u8 **)(arg0 + 0x38);
    cap2 = src + 0x10;

    *(f32 *)(hit + 0x10) = *(f32 *)(src + 0x00);
    *(f32 *)(hit + 0x14) = *(f32 *)(src + 0x04);
    *(f32 *)(hit + 0x18) = *(f32 *)(src + 0x08);
    *(f32 *)(hit + 0x1C) = *(f32 *)(src + 0x0C);
    *(f32 *)(hit + 0x20) = *(f32 *)(src + 0x00);
    *(f32 *)(hit + 0x24) = *(f32 *)(src + 0x04);
    *(f32 *)(hit + 0x28) = *(f32 *)(src + 0x08);
    *(f32 *)(hit + 0x2C) = *(f32 *)(src + 0x0C);
    *(f32 *)(hit + 0x30) = *(f32 *)(src + 0x10);
    *(f32 *)(hit + 0x34) = *(f32 *)(src + 0x14);
    *(f32 *)(hit + 0x38) = *(f32 *)(src + 0x18);
    *(s32 *)(hit + 0x60) = arg0;
    *(f32 *)(hit + 0x3C) = *(f32 *)(src + 0x1C);
    *(s32 *)(hit + 0x64) = *(s32 *)(src + 0x174);

    if (*(s32 *)(src + 0x60) & 4) {
        *(s32 *)(hit + 0x50) = *(s32 *)(hit + 0x50) | 0x10;
    }

    box1 = EftHitArena_AllocBox();
    box0 = EftHitArena_AllocBox();
    ColCapsule_Set(1.0f, box1, (s32)cap2, (s32)src);
    ColCapsule_Set(1.0f, box0, (s32)(src + 0x20), (s32)cap2);
    EftHit_SetShapeBoxes((s32)hit, box1, box0);
    func_00127128((s32)hit);
}
