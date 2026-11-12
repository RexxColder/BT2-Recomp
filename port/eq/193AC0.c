#include "common.h"

extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern u32 D_0036E930[8];

extern void Vec4_Set(u8 *dst, f32 x, f32 y, f32 z, f32 w);
extern void func_00129BD0(u8 *dst, u8 *src, f32 s);
extern void Vec3_Add(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Sub(u8 *dst, u8 *a, u8 *b);
extern s32 func_001294B0(u8 *out, u8 *pts, s32 n, s32 flag);
extern void func_00129D40(u8 *dst, u8 *src);

/* Draws the billboard quads (4-vertex GIF packets of 0x90 bytes) of a linked list of effect nodes
   (node+0x140 = next): each node's centre +- half extent along two axes, projected, with perspective-correct uv. */
s32 func_00193AC0(u8 *list, u8 *cfg) {
    u8 p[0x40];       /* sp+0x00: world corners (centre +- axes) */
    f32 uv[16];       /* sp+0x40: (i % 2, i / 2, 1, 0) */
    f32 uvq[16];      /* sp+0x80: uv / w */
    u8 tmpA[0x10];    /* sp+0xC0 */
    u8 tmpB[0x10];    /* sp+0xD0 */
    u8 proj[0x40];    /* sp+0xE0: {s16 x, s16 y@4, s32 z@8, w@0xC} per corner */
    u8 col[0x10];     /* sp+0x120 */
    u32 idx[8];
    u8 *node;
    u8 *pkt;
    u8 *ent;
    u8 *prev;
    s32 i;
    s32 key;
    u64 m = 0xFF000000FFFFFFFFull;

    __builtin_memcpy(idx, D_0036E930, 0x20);
    for (i = 0; i < 4; i++) {
        uv[i * 4 + 0] = (f32)(i % 2);
        uv[i * 4 + 1] = (f32)(i / 2);
        uv[i * 4 + 2] = 1.0f;
        *(s32 *)&uv[i * 4 + 3] = 0;
        Vec4_Set(p + i * 16, 0.0f, 0.0f, 0.0f, 1.0f);
    }
    node = *(u8 **)list;
    while (node != 0) {
        func_00129BD0(tmpA, node + 0xF0, *(f32 *)(node + 0x3C));
        Vec3_Add(p + 0x00, node + 0x90, tmpA);
        Vec3_Sub(p + 0x10, node + 0x90, tmpA);
        if (cfg[4] == 0) {
            func_00129BD0(tmpB, node + 0xE0, *(f32 *)(node + 0x34));
            Vec3_Add(p + 0x20, p + 0x00, tmpB);
            Vec3_Add(p + 0x30, p + 0x10, tmpB);
        } else {
            func_00129BD0(tmpB, node + 0xE0, *(f32 *)(node + 0x34) * 0.5f);
            Vec3_Add(p + 0x20, p + 0x00, tmpB);
            Vec3_Add(p + 0x30, p + 0x10, tmpB);
            Vec3_Sub(p + 0x00, p + 0x00, tmpB);
            Vec3_Sub(p + 0x10, p + 0x10, tmpB);
        }
        if (func_001294B0(proj, p, 4, 1) != 0) {
            pkt = D_00387AD8;
            D_00387AD8 = pkt + 0x90;
            if (pkt == 0) {
                return (s32)(u32)D_00387AD8; /* pool slot was NULL: store left 0x90 there, returned as is */
            }
            *(u64 *)(pkt + 0x20) = 0x5C;
            *(u64 *)(pkt + 0x00) = 0xA0000008ull;
            *(u64 *)(pkt + 0x10) = 0xE400000000008001ull;
            *(u64 *)(pkt + 0x18) = 0x42142142142160ull;
            for (i = 0; i < 4; i++) {
                uv[i * 4 + 0] = *(f32 *)(node + 0x130 + 4 * idx[i * 2]);
                uv[i * 4 + 1] = *(f32 *)(node + 0x130 + 4 * idx[i * 2 + 1]);
                func_00129BD0((u8 *)&uvq[i * 4], (u8 *)&uv[i * 4], 1.0f / (f32)*(s32 *)(proj + i * 16 + 0xC));
            }
            func_00129D40(col, node + 0x110);
            key = (*(s32 *)(proj + 0x08) + *(s32 *)(proj + 0x18) + *(s32 *)(proj + 0x28) + *(s32 *)(proj + 0x38)) >> 10;
            if ((*(u32 *)(list + 0x60) & 0x40) != 0) {
                for (i = 3; i >= 0; i--) {
                    *(s32 *)(proj + i * 16 + 8) = 0xFFFFFF;
                }
            }
            for (i = 0; i < 4; i++) {
                u8 *q = pkt + 0x30 + i * 0x18;
                q[0] = col[0];
                q[1] = col[4];
                q[2] = col[8];
                q[3] = col[12];
                *(f32 *)(q + 4) = uvq[i * 4 + 2];
                *(f32 *)(q + 8) = uvq[i * 4 + 0];
                *(f32 *)(q + 12) = uvq[i * 4 + 1];
            }
            for (i = 0; i < 4; i++) {
                u8 *q = pkt + 0x40 + i * 0x18;
                u8 *pj = proj + i * 16;
                *(u16 *)(q + 0) = *(u16 *)(pj + 0);
                *(u16 *)(q + 2) = *(u16 *)(pj + 4);
                *(u64 *)q = (*(u64 *)q & m) | ((u64)(*(s32 *)(pj + 8) & 0xFFFFFF) << 32);
                q[7] = 0xFF;
            }
            *(u64 *)(pkt + 0x28) = *(u64 *)(list + 0x1E8);
            {
                s32 slot = node[4];
                if (key < 0) {
                    ent = D_00387AE0 + (slot << 3);
                } else if (key < 0x1000) {
                    ent = D_00387AE0 + ((2 * key + slot) << 3);
                } else {
                    ent = D_00387AE0 + (slot << 3) + 0xFFF0;
                }
            }
            prev = *(u8 **)(ent + 4);
            *(u8 **)(prev + 4) = pkt;
            *(u8 **)(ent + 4) = pkt;
        }
        node = *(u8 **)(node + 0x140);
    }
    return 0;
}
