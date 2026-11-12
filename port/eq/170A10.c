#include "common.h"

u8 *EftHit_GetNew(void);
f32 func_00152958(u8 *arg0);
u8 *func_00127F88(void);
void ColSphere_Set(f32 radius, u8 *sphere, u8 *src);
void EftHit_SetShapeSpheres(u8 *hit, u8 *s0, u8 *s1);
void func_00127128(u8 *hit);

/* 0x00170A10: creates a hit object from task->0x38 data (two spheres at S+0x80 / S+0x90, scaled radius). */
void func_00170A10(u8 *task) {
    u8 *S = *(u8 **)(task + 0x38);
    u8 *hit;
    u8 *sphA;
    u8 *sphB;
    f32 radius;

    hit = EftHit_GetNew();
    radius = *(f32 *)(S + 0x1C) * func_00152958(S + 0xB4);
    *(u64 *)(hit + 0x10) = *(u64 *)(S + 0x70);
    *(u64 *)(hit + 0x18) = *(u64 *)(S + 0x78);
    *(u64 *)(hit + 0x20) = *(u64 *)(S + 0x80);
    *(u64 *)(hit + 0x28) = *(u64 *)(S + 0x88);
    *(u64 *)(hit + 0x30) = *(u64 *)(S + 0x90);
    *(u64 *)(hit + 0x38) = *(u64 *)(S + 0x98);
    *(u64 *)(hit + 0x40) = *(u64 *)(S + 0xA0);
    *(u8 **)(hit + 0x60) = task;
    *(u64 *)(hit + 0x48) = *(u64 *)(S + 0xA8);
    *(u32 *)(hit + 0x64) = *(u32 *)(S + 0xB0);
    sphA = func_00127F88();
    sphB = func_00127F88();
    ColSphere_Set(radius, sphA, S + 0x80);
    ColSphere_Set(radius, sphB, S + 0x90);
    EftHit_SetShapeSpheres(hit, sphA, sphB);
    func_00127128(hit);
}
