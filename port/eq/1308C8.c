#include "common.h"

extern u8 *gEftBubble;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern f32 D_00384204;

void sceVu0CopyMatrix(f32 *dst, u8 *src);
void sceVu0UnitMatrix(f32 *m);
f32 EftMath_WrapAngle(f32 farg0);
void sceVu0RotMatrixZ(f32 *arg0, f32 *arg1, f32 arg2);
void sceVu0MulMatrix(f32 *arg0, f32 *arg1, f32 *arg2);
void sceVu0ApplyMatrix(u8 *dst, u8 *m, u8 *v);
s32 Eft_IsScreenPosVisible(s32 *pos);
void func_003126C8(void *arg0, void *arg1);
void func_00130770(s32 *arg0, f32 *arg1, f32 *arg2);

/* Queues one screen-facing quad (4 projected corners) into the depth-sorted list. */
void func_001308C8(void *obj, f32 *proj, u8 r, u8 g, u8 b, u8 a, u64 *tex, u8 layer,
                   f32 size, f32 angle) {
    f32 mtx[16];
    f32 unused[4];
    f32 corners[16];
    s32 scr[16];
    f32 rot[16];
    f32 half;
    u8 *pkt;
    u8 *link;
    u8 *bucket;
    s32 i;
    s32 key;

    sceVu0CopyMatrix(mtx, gEftBubble + 0x20);
    if (angle != 0.0f) {
        sceVu0UnitMatrix(rot);
        sceVu0RotMatrixZ(rot, rot, EftMath_WrapAngle((angle / 180.0f) * D_00384204));
        sceVu0MulMatrix(mtx, mtx, rot);
    }
    func_003126C8(unused, obj);
    half = size * 0.5f;
    corners[0] = -half;
    corners[1] = -half;
    corners[2] = 0.0f;
    corners[3] = 1.0f;
    corners[4] = half;
    corners[5] = -half;
    corners[6] = 0.0f;
    corners[7] = 1.0f;
    corners[8] = -half;
    corners[9] = half;
    corners[10] = 0.0f;
    corners[11] = 1.0f;
    corners[12] = half;
    corners[13] = half;
    corners[14] = 0.0f;
    corners[15] = 1.0f;
    for (i = 0; i < 4; i++) {
        sceVu0ApplyMatrix((u8 *)&corners[i * 4], (u8 *)mtx, (u8 *)&corners[i * 4]);
        func_00130770(&scr[i * 4], proj, &corners[i * 4]);
        if (Eft_IsScreenPosVisible(&scr[i * 4]) == 0) {
            return;
        }
    }
    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x80;
    if (pkt == 0) {
        return;
    }
    *(u64 *)(pkt + 0x10) = 0xC400000000008001ULL;
    *(u64 *)(pkt + 0x18) = 0xF42424242160ULL;
    *(u64 *)(pkt + 0x20) = 0x54;
    *(u64 *)pkt = 0xA0000007ULL;
    pkt[0x30] = r;
    pkt[0x31] = g;
    pkt[0x32] = b;
    pkt[0x33] = a;
    *(f32 *)(pkt + 0x6C) = 1.0f;
    *(f32 *)(pkt + 0x34) = 1.0f;
    *(s32 *)(pkt + 0x38) = 0;
    *(s32 *)(pkt + 0x3C) = 0;
    *(f32 *)(pkt + 0x48) = 1.0f;
    *(s32 *)(pkt + 0x4C) = 0;
    *(s32 *)(pkt + 0x58) = 0;
    *(f32 *)(pkt + 0x5C) = 1.0f;
    *(f32 *)(pkt + 0x68) = 1.0f;
    for (i = 0; i < 4; i++) {
        u8 *dst = pkt + 0x40 + i * 0x10;
        *(u16 *)(dst + 0) = (u16)scr[i * 4];
        *(u16 *)(dst + 2) = (u16)scr[i * 4 + 1];
        *(u64 *)dst = (*(u64 *)dst & 0xFF000000FFFFFFFFULL) |
                      ((u64)((u32)scr[i * 4 + 2] & 0xFFFFFF) << 32);
        dst[7] = 0xFF;
    }
    key = (scr[2] + scr[14] + scr[10] + scr[6]) >> 10;
    *(u64 *)(pkt + 0x28) = *tex;
    if (key < 0) {
        bucket = D_00387AE0 + layer * 8;
        link = *(u8 **)(bucket + 4);
    } else if (key >= 0x1000) {
        bucket = D_00387AE0 + layer * 8 + 0xFFF0;
        link = *(u8 **)(bucket + 4);
    } else {
        bucket = D_00387AE0 + (key * 2 + layer) * 8;
        link = *(u8 **)(bucket + 4);
    }
    *(u8 **)(link + 4) = pkt;
    *(u8 **)(bucket + 4) = pkt;
}
