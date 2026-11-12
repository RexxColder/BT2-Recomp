#include "common.h"

extern u8 *D_00387AD8;
extern u8 *D_00387AE4;
extern f32 D_003856E8;
extern f32 D_003856EC;
extern f32 D_003856F0;
extern f32 D_003856F4;
extern u8 D_003435B0[];

void func_00312730(f32 *dst, s32 *src);
void func_00312710(s32 *dst, f32 *src);
void func_00312680(f32 *dst, f32 *src, f32 scale);
void func_00312668(f32 *dst, f32 *src, u8 *k);
void sceVu0UnitMatrix(f32 *m);
void sceVu0RotMatrixZ(f32 *dst, f32 *src, f32 angle);
void sceVu0ApplyMatrix(f32 *dst, f32 *m, f32 *src);

/* Queues one rotated, scaled screen sprite (4 vertices at +-half extents) into the depth-sorted list.
 * Integer args 5..: x, y (centre), layer, half-width; stack: half-height, (unused slot), tex flag, list base, texture. */
void func_001EFA68(u8 r, u8 g, u8 b, u8 a, s32 cx, s32 cy, s32 layer, s32 halfW,
                   f32 x0, f32 y0, f32 dx, f32 dy, f32 scale, f32 angle,
                   s32 halfH, s64 pad, s32 flag, s32 listBase, u64 *tex) {
    s32 ext0[4];
    s32 ext1[4];
    f32 axisA[4];
    f32 axisB[4];
    f32 mtx[16];
    u8 *pkt;
    u8 *list;
    f32 x1;
    f32 y1;
    u64 mask;

    if (D_003856E8 < angle) {
        angle -= D_003856EC;
    } else if (angle < D_003856F0) {
        angle += D_003856F4;
    }
    x1 = x0 + dx;
    y1 = y0 + dy;
    ext0[0] = halfW;
    ext0[1] = halfH;
    ext0[2] = 0;
    ext0[3] = 1;
    ext1[0] = -halfW;
    ext1[1] = halfH;
    ext1[2] = 0;
    ext1[3] = 1;
    func_00312730(axisA, ext0);
    func_00312730(axisB, ext1);
    sceVu0UnitMatrix(mtx);
    sceVu0RotMatrixZ(mtx, mtx, angle);
    func_00312680(axisA, axisA, scale);
    func_00312680(axisB, axisB, scale);
    sceVu0ApplyMatrix(axisA, mtx, axisA);
    sceVu0ApplyMatrix(axisB, mtx, axisB);
    func_00312668(axisA, axisA, D_003435B0);
    func_00312668(axisB, axisB, D_003435B0);
    func_00312710(ext0, axisA);
    func_00312710(ext1, axisB);

    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x80;
    mask = 0x00FFFFFF00000000ULL;
    *(u64 *)(pkt + 0x28) = *tex;
    *(u64 *)(pkt + 0x20) = ((s64)(s8)flag << 9) | 0x54;
    *(u64 *)(pkt + 0x00) = 0xA0000007ULL;
    *(u64 *)(pkt + 0x18) = (s64)((s32)(s8)flag << 4) + 0xF42424242160LL;
    *(u64 *)(pkt + 0x10) = 0xC400000000008001ULL;
    pkt[0x30] = r;
    pkt[0x31] = g;
    pkt[0x32] = b;
    pkt[0x33] = a;
    *(f32 *)(pkt + 0x34) = 1.0f;
    *(f32 *)(pkt + 0x48) = x0;
    *(f32 *)(pkt + 0x5C) = y0;
    *(f32 *)(pkt + 0x68) = x1;
    *(f32 *)(pkt + 0x6C) = y1;
    *(f32 *)(pkt + 0x38) = x0;
    *(f32 *)(pkt + 0x3C) = y0;
    *(f32 *)(pkt + 0x4C) = y1;
    *(f32 *)(pkt + 0x58) = x1;

    *(u16 *)(pkt + 0x40) = (cx - (u16)ext0[0]) * 16 + 0x7000;
    *(u16 *)(pkt + 0x42) = (cy - (u16)ext0[1]) * 16 + 0x7200;
    *(u64 *)(pkt + 0x40) |= mask;
    pkt[0x47] = 0xFF;

    *(u16 *)(pkt + 0x50) = ((u16)ext1[0] + cx) * 16 + 0x7000;
    *(u16 *)(pkt + 0x52) = ((u16)ext1[1] + cy) * 16 + 0x7200;
    *(u64 *)(pkt + 0x50) |= mask;
    pkt[0x57] = 0xFF;

    *(u16 *)(pkt + 0x60) = (cx - (u16)ext1[0]) * 16 + 0x7000;
    *(u16 *)(pkt + 0x62) = (cy - (u16)ext1[1]) * 16 + 0x7200;
    *(u64 *)(pkt + 0x60) |= mask;
    pkt[0x67] = 0xFF;

    *(u16 *)(pkt + 0x70) = ((u16)ext0[0] + cx) * 16 + 0x7000;
    *(u16 *)(pkt + 0x72) = ((u16)ext0[1] + cy) * 16 + 0x7200;
    *(u64 *)(pkt + 0x70) |= mask;
    pkt[0x77] = 0xFF;

    list = D_00387AE4 + (layer * 2 + listBase) * 8;
    *(u8 **)(*(u8 **)(list + 4) + 4) = pkt;
    *(u8 **)(list + 4) = pkt;
}
