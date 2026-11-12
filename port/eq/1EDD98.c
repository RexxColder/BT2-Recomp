#include "common.h"
void bt2_fightlog_note(const char *fmt, ...); /* TEMP TEX0 */

extern f32 D_003856E0;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

/* append packet p to the depth-sorted list: bucket by layer (and by sub-layer when given) */
#define ENQUEUE(p) \
    do { \
        u8 *node; \
        u8 *last; \
        if (sub < 0) { \
            node = D_00387AE0 + layer * 8; \
        } else if (sub < 0x1000) { \
            node = D_00387AE0 + (sub * 2 + layer) * 8; \
        } else { \
            node = D_00387AE0 + layer * 8 + 0xFFF0; \
        } \
        last = *(u8 **)(node + 4); \
        *(u8 **)(last + 4) = (p); \
        *(u8 **)(node + 4) = (p); \
    } while (0)

/* four float colour channels as bytes (float -> unsigned conversion) */
#define PUT_COLOR(p, off, c) \
    do { \
        (p)[(off) + 0] = (u8)(u32)(c)[0]; \
        (p)[(off) + 1] = (u8)(u32)(c)[1]; \
        (p)[(off) + 2] = (u8)(u32)(c)[2]; \
        (p)[(off) + 3] = (u8)(u32)(c)[3]; \
    } while (0)

/* screen vertex: x, y halves and a 24 bit z, alpha forced to 0xFF */
#define PUT_VERT(p, off, v) \
    do { \
        *(u16 *)((p) + (off)) = *(u16 *)(v); \
        *(u16 *)((p) + (off) + 2) = *(u16 *)((v) + 4); \
        *(u32 *)((p) + (off) + 4) = (*(u32 *)((p) + (off) + 4) & 0xFF000000u) | (*(u32 *)((v) + 8) & 0xFFFFFF); \
        (p)[(off) + 7] = 0xFF; \
    } while (0)

/* Queues one gouraud triangle (3 vertices, colours and texture coords) with optional begin/end state packets. */
void func_001EDD98(u8 *va, u8 *vb, u8 *vc, f32 *colA, f32 *colB, f32 *colC, f32 *stA, f32 *stB, f32 *stC,
                   u8 beginState, u8 endState, u8 textured, s32 layer, s32 sub, u64 reg) {
    u8 *p;
    s32 tagBit = 1;

    if (colA[3] < D_003856E0 && colB[3] < D_003856E0 && colC[3] < D_003856E0) {
        return;
    }
    if (layer < 0) {
        layer = 0;
        tagBit = 0;
    }

    if (beginState != 0) {
        p = D_00387AD8;
        D_00387AD8 = p + 0x30;
        *(u64 *)(p + 0x00) = 0xA0000002ULL;
        *(u64 *)(p + 0x10) = 0x1000000000008001ULL;
        *(u64 *)(p + 0x18) = 0xE;
        *(u64 *)(p + 0x28) = 8;
        *(u64 *)(p + 0x20) = 0;
        ENQUEUE(p);
    }
    if (endState != 0) {
        p = D_00387AD8;
        D_00387AD8 = p + 0x30;
        *(u64 *)(p + 0x00) = 0xA0000002ULL;
        *(u64 *)(p + 0x10) = 0x1000000000008001ULL;
        *(u64 *)(p + 0x20) = 0x310000E0ULL;
        *(u64 *)(p + 0x18) = 0xE;
        *(u64 *)(p + 0x28) = 0x4E;
        ENQUEUE(p);
    }

    if (textured != 0) {
        p = D_00387AD8;
        D_00387AD8 = p + 0x80;
        *(u64 *)(p + 0x20) = ((u64)tagBit << 6) | 0x1B;
        *(u64 *)(p + 0x10) = 0xC400000000008001ULL;
        *(u64 *)(p + 0x00) = 0xA0000007ULL;
        *(u64 *)(p + 0x18) = 0xF42142142160ULL;
        PUT_COLOR(p, 0x30, colA);
        *(f32 *)(p + 0x34) = stA[2];
        PUT_COLOR(p, 0x48, colB);
        *(f32 *)(p + 0x4C) = stB[2];
        PUT_COLOR(p, 0x60, colC);
        *(f32 *)(p + 0x64) = stC[2];
        *(u64 *)(p + 0x28) = reg;
        if ((u32)(*(u64 *)(p + 0x28) >> 32) == 0 && (u32)*(u64 *)(p + 0x28) > 0xFFFFu) bt2_fightlog_note("TEX0TRUNC 1EDD98 %llx ret %p", (unsigned long long)*(u64 *)(p + 0x28), __builtin_return_address(0)); /* TEMP TEX0 */
        *(f32 *)(p + 0x38) = stA[0];
        *(f32 *)(p + 0x3C) = stA[1];
        *(f32 *)(p + 0x50) = stB[0];
        *(f32 *)(p + 0x54) = stB[1];
        *(f32 *)(p + 0x68) = stC[0];
        *(f32 *)(p + 0x6C) = stC[1];
        PUT_VERT(p, 0x40, va);
        PUT_VERT(p, 0x58, vb);
        PUT_VERT(p, 0x70, vc);
        ENQUEUE(p);
    } else {
        p = D_00387AD8;
        D_00387AD8 = p + 0x60;
        *(u64 *)(p + 0x20) = ((u64)tagBit << 6) | 0xB;
        *(u64 *)(p + 0x10) = 0x8400000000008001ULL;
        *(u64 *)(p + 0x00) = 0xA0000005ULL;
        *(u64 *)(p + 0x18) = 0xF4141410ULL;
        PUT_COLOR(p, 0x28, colA);
        *(f32 *)(p + 0x2C) = 1.0f;
        PUT_COLOR(p, 0x38, colB);
        *(f32 *)(p + 0x3C) = 1.0f;
        PUT_COLOR(p, 0x48, colC);
        *(f32 *)(p + 0x4C) = 1.0f;
        PUT_VERT(p, 0x30, va);
        PUT_VERT(p, 0x40, vb);
        PUT_VERT(p, 0x50, vc);
        ENQUEUE(p);
    }

    if (endState != 0) {
        p = D_00387AD8;
        D_00387AD8 = p + 0x30;
        *(u64 *)(p + 0x00) = 0xA0000002ULL;
        *(u64 *)(p + 0x10) = 0x1000000000008001ULL;
        *(u64 *)(p + 0x18) = 0xE;
        *(u64 *)(p + 0x28) = 0x4E;
        *(u64 *)(p + 0x20) = 0x1310000E0ULL;
        ENQUEUE(p);
    }
}
