#include "common.h"

extern u8 *D_00387AD8;
extern u8 *D_00387AE4;
extern f32 D_00385064;
extern f32 D_00385068;
extern f32 D_0038506C;
extern f32 D_00385070;
extern u8 D_0036EF10[] __attribute__((section(".data")));

s32 func_0012EAA0(void);
void sceVu0RotTransPers(void *arg0, s32 arg1, void *arg2, s32 arg3);
void func_00312730(f32 *dst, s32 *src);
void sceVu0UnitMatrix(void *arg0);
void sceVu0RotMatrixZ(f32 *arg0, f32 *arg1, f32 arg2);
void sceVu0ApplyMatrix(void *arg0, void *arg1, void *arg2);
void func_00312668(void *a0, void *a1, void *a2);
void func_00312710(s32 *dst, f32 *src);
s32 func_001B8588(s32 arg0, s32 arg1, s32 arg2);

#define H(p, off) (*(u16 *)((p) + (off)))
#define W(p, off) (*(s32 *)((p) + (off)))

/* Draws a rotated screen-space quad (sprite) for a world point: projects arg1 (w set to 1), scales the
   half-size (arg2, arg3 in 1/4096 units of the pixel size from arg4) by depth, builds the four rotated
   corners (angle farg4, wrapped to the D_00385064.. range), rejects the sprite when any corner is
   rejected by func_001B8588, otherwise appends a 0x80-byte GIF packet to the list at D_00387AD8 / links
   it through D_00387AE4. farg0..farg3 are the packet's u,v pairs; arg0 supplies the 4 color bytes
   (stride 4), arg5 the 8-byte tag data. */
void func_001B85B8(f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, u8 *arg0, f32 *arg1,
                   s32 arg2, s32 arg3, u32 arg4, u64 *arg5) {
    u8 sp[0xA0];
    f32 scaleBase;
    f32 size;
    f32 ratio;
    s32 depthScale;
    u32 halfX;
    u32 halfY;
    f32 angle = farg4;
    u8 *p;

    scaleBase = *(f32 *)((u8 *)func_0012EAA0() + 0x40);
    *(u64 *)(sp + 0x90) = *(u64 *)(D_0036EF10 + 0);
    *(u64 *)(sp + 0x98) = *(u64 *)(D_0036EF10 + 8);
    arg1[3] = 1.0f;
    sceVu0RotTransPers(sp, func_0012EAA0(), arg1, 1);

    size = (f32)arg4 * scaleBase;
    ratio = size / (f32)W(sp, 0xC);
    depthScale = (s32)ratio;
    if (ratio >= 2147483648.0f) {
        depthScale = (s32)(ratio - 2147483648.0f) | 0x80000000;
    }
    halfX = (u32)(arg2 * depthScale) >> 12;
    halfY = (u32)(arg3 * depthScale) >> 12;
    if (halfX < 2) {
        return;
    }
    if (halfY < 2) {
        return;
    }

    if (D_00385064 < angle) {
        angle = angle - D_00385068;
    } else if (angle < D_0038506C) {
        angle = angle + D_00385070;
    }

    W(sp, 0x10) = halfX;
    W(sp, 0x14) = halfY;
    W(sp, 0x18) = 0;
    W(sp, 0x1C) = 1;
    W(sp, 0x20) = -(s32)halfX;
    W(sp, 0x24) = halfY;
    W(sp, 0x28) = 0;
    W(sp, 0x2C) = 1;
    func_00312730((f32 *)(sp + 0x30), (s32 *)(sp + 0x10));
    func_00312730((f32 *)(sp + 0x40), (s32 *)(sp + 0x20));
    sceVu0UnitMatrix(sp + 0x50);
    sceVu0RotMatrixZ((f32 *)(sp + 0x50), (f32 *)(sp + 0x50), angle);
    sceVu0ApplyMatrix(sp + 0x30, sp + 0x50, sp + 0x30);
    sceVu0ApplyMatrix(sp + 0x40, sp + 0x50, sp + 0x40);
    func_00312668(sp + 0x30, sp + 0x30, sp + 0x90);
    func_00312668(sp + 0x40, sp + 0x40, sp + 0x90);
    func_00312710((s32 *)(sp + 0x10), (f32 *)(sp + 0x30));
    func_00312710((s32 *)(sp + 0x20), (f32 *)(sp + 0x40));

    if (func_001B8588(W(sp, 0) - W(sp, 0x10), W(sp, 4) - W(sp, 0x14), W(sp, 8)) != 0) {
        return;
    }
    if (func_001B8588(W(sp, 0) + W(sp, 0x20), W(sp, 4) + W(sp, 0x24), W(sp, 8)) != 0) {
        return;
    }
    if (func_001B8588(W(sp, 0) - W(sp, 0x20), W(sp, 4) - W(sp, 0x24), W(sp, 8)) != 0) {
        return;
    }
    if (func_001B8588(W(sp, 0) + W(sp, 0x10), W(sp, 4) + W(sp, 0x14), W(sp, 8)) != 0) {
        return;
    }

    p = D_00387AD8;
    D_00387AD8 = p + 0x80;
    *(u64 *)(p + 0x00) = 0xA0000007;
    *(u64 *)(p + 0x20) = 0x54;
    *(u64 *)(p + 0x10) = 0xC400000000008001ULL;
    *(u64 *)(p + 0x18) = 0xF42424242160ULL;
    *(u64 *)(p + 0x28) = *arg5;
    p[0x30] = arg0[0];
    p[0x31] = arg0[4];
    p[0x32] = arg0[8];
    *(f32 *)(p + 0x34) = 1.0f;
    p[0x33] = arg0[12];
    *(f32 *)(p + 0x4C) = farg1;
    *(f32 *)(p + 0x58) = farg0;
    *(f32 *)(p + 0x68) = farg2;
    *(f32 *)(p + 0x6C) = farg3;
    *(f32 *)(p + 0x38) = farg0;
    *(f32 *)(p + 0x3C) = farg1;
    *(f32 *)(p + 0x48) = farg2;
    *(f32 *)(p + 0x5C) = farg3;

    H(p, 0x40) = H(sp, 0) - H(sp, 0x10);
    H(p, 0x42) = H(sp, 4) - H(sp, 0x14);
    W(p, 0x44) = (W(sp, 8) & 0xFFFFFF) | 0xFF000000;
    H(p, 0x50) = H(sp, 0) + H(sp, 0x20);
    H(p, 0x52) = H(sp, 4) + H(sp, 0x24);
    W(p, 0x54) = (W(sp, 8) & 0xFFFFFF) | 0xFF000000;
    H(p, 0x60) = H(sp, 0) - H(sp, 0x20);
    H(p, 0x62) = H(sp, 4) - H(sp, 0x24);
    W(p, 0x64) = (W(sp, 8) & 0xFFFFFF) | 0xFF000000;
    H(p, 0x70) = H(sp, 0) + H(sp, 0x10);
    H(p, 0x72) = H(sp, 4) + H(sp, 0x14);
    W(p, 0x74) = (W(sp, 8) & 0xFFFFFF) | 0xFF000000;

    *(u8 **)(*(u8 **)(D_00387AE4 + 4) + 4) = p;
    *(u8 **)(D_00387AE4 + 4) = p;
}
