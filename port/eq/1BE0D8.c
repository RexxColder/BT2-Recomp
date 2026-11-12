#include "common.h"

typedef struct { u64 lo, hi; } q128;

extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

void func_00129C28(q128 *dst, q128 *src);
void func_00129C38(u8 *dst, u8 *src);
s32 func_00129440(s32 *out, f32 *in);
void Vec3_Scale(u8 *dst, u8 *src, f32 s);
f32 Vec3_Add(u8 *dst, u8 *a, u8 *b);
void Vec3_Sub(u8 *dst, u8 *a, u8 *b);
void Vec3_Cross(u8 *dst, u8 *a, u8 *b);
s32 Vec3_Normalize(u8 *dst, u8 *src);
s32 Vec4_Set(u8 *v, f32 x, f32 y, f32 z, f32 w);

/* float -> byte as the game does it: values >= 2^31 are rebased and get the sign bit set. */
static u8 FtoByte(f32 x) {
    if (x >= 2147483648.0f) {
        return (u8)((s32)(x - 2147483648.0f) | 0x80000000);
    }
    return (u8)(s32)x;
}


/* Per-vertex GS packet fields (vertex k at pkt + 0x30 + k * 0x18). */
#define PKT_COLOR(k) do { u8 *c = pkt + 0x30 + (k) * 0x18; \
    c[0] = FtoByte(*(f32 *)(sp + 0x110)); c[1] = FtoByte(*(f32 *)(sp + 0x114)); \
    c[2] = FtoByte(*(f32 *)(sp + 0x118)); c[3] = FtoByte(*(f32 *)(sp + 0x11C)); \
    *(f32 *)(c + 4) = *(f32 *)(sp + 0xD8 + (k) * 16); } while (0)
#define PKT_UV(k) do { u8 *c = pkt + 0x30 + (k) * 0x18; \
    *(f32 *)(c + 8) = *(f32 *)(sp + 0xD0 + (k) * 16); *(f32 *)(c + 12) = *(f32 *)(sp + 0xD4 + (k) * 16); } while (0)
#define PKT_XYZ(k) do { u8 *c = pkt + 0x40 + (k) * 0x18; u64 q; \
    *(u16 *)(c + 0) = *(u16 *)(sp + 0x130 + (k) * 16); *(u16 *)(c + 2) = *(u16 *)(sp + 0x134 + (k) * 16); \
    q = *(u64 *)c; \
    q = (q & 0xFF000000FFFFFFFFULL) | ((u64)(s64)(*(s32 *)(sp + 0x138 + (k) * 16) & 0xFFFFFF) << 32); \
    *(u64 *)c = q; c[7] = 0xFF; } while (0)

/* 0x001BE0D8: ribbon/trail drawer. Walks a linked list of nodes (next at +0xF0, pos at +0x50), builds a camera-facing
 * quad per segment, projects it, and links a 0x90-byte GS packet into the ordering table. */
void func_001BE0D8(u8 *arg0, u8 *arg1, u8 *arg2) {
    u8 sp[0x190];
    u8 *node;
    u8 *next;
    u8 *pkt;
    u8 *slot;
    u8 *tail;
    u8 *pos;
    u8 *npos;
    f32 stepU;
    f32 u;
    f32 v;
    f32 one;
    s32 first;
    s32 idx;
    s32 bad;
    s32 i;
    s32 k;
    s32 key;
    s32 z;

    func_00129C28((q128 *)(sp + 0x60), (q128 *)(gBtlCamView + 0x1F0));
    first = 1;
    idx = 0;
    one = 1.0f;
    u = 0.0f;
    stepU = 1.0f / (f32)(arg2[6] - 1);
    v = stepU + 0.0f;
    for (i = 0; i < 4; i++) {
        s32 h = i >> 1;
        *(f32 *)(sp + 0x90 + i * 16) = (f32)(i - h * 2);
        *(f32 *)(sp + 0x94 + i * 16) = (f32)h;
        *(f32 *)(sp + 0x98 + i * 16) = one;
        Vec4_Set(sp + i * 16, 0.0f, 0.0f, 0.0f, one);
        *(s32 *)(sp + 0x9C + i * 16) = 0;
    }
    func_00129C28((q128 *)(sp + 0x110), (q128 *)(arg2 + 0x70));
    node = *(u8 **)(arg2 + 0xE8);
    if (node == 0) {
        return;
    }
    do {
        next = *(u8 **)(node + 0xF0);
        if (next != 0) {
            pos = node + 0x50;
            npos = next + 0x50;
            Vec3_Sub(sp + 0x70, npos, pos);
            Vec3_Sub(sp + 0x80, pos, sp + 0x60);
            Vec3_Cross(sp + 0x70, sp + 0x70, sp + 0x80);
            Vec3_Normalize(sp + 0x70, sp + 0x70);
            Vec3_Scale(sp + 0x120, sp + 0x70, *(f32 *)(arg2 + 0x20));
            if (first) {
                first = 0;
                Vec3_Add(sp + 0x00, pos, sp + 0x120);
                Vec3_Sub(sp + 0x10, pos, sp + 0x120);
            } else {
                func_00129C38(sp + 0x00, sp + 0x40);
                func_00129C38(sp + 0x10, sp + 0x50);
            }
            Vec3_Add(sp + 0x20, npos, sp + 0x120);
            Vec3_Sub(sp + 0x30, npos, sp + 0x120);
            func_00129C38(sp + 0x40, sp + 0x20);
            func_00129C38(sp + 0x50, sp + 0x30);
            if (idx >= arg2[6] - 2) {
                v = 1.0f;
            }
            one = 1.0f;
            bad = 0;
            *(f32 *)(sp + 0x94) = u;
            *(f32 *)(sp + 0xA4) = u;
            *(f32 *)(sp + 0xB4) = v;
            *(f32 *)(sp + 0xC4) = v;
            for (i = 0; i < 4;) {
                k = i * 16;
                i++;
                func_00129440((s32 *)(sp + 0x130 + k), (f32 *)(sp + k));
                if (*(u32 *)(sp + 0x130 + k) > 0xFFF0) {
                    bad = 1;
                    break;
                }
                if (*(u32 *)(sp + 0x134 + k) > 0xFFF0) {
                    bad = 1;
                    break;
                }
                if (*(s32 *)(sp + 0x138 + k) < 0) {
                    bad = 1;
                    break;
                }
                Vec3_Scale(sp + 0xD0 + k, sp + 0x90 + k, one / (f32)*(s32 *)(sp + 0x13C + k));
            }
            if (!bad) {
                pkt = D_00387AD8;
                D_00387AD8 = pkt + 0x90;
                if (pkt == 0) {
                    return;
                }
                *(u64 *)(pkt + 0x20) = 0x5C;
                *(u64 *)(pkt + 0x00) = 0xA0000008ULL;
                *(u64 *)(pkt + 0x10) = 0xE400000000008001ULL;
                *(u64 *)(pkt + 0x18) = 0x0042142142142160ULL;
                key = (*(s32 *)(sp + 0x138) + *(s32 *)(sp + 0x168) + (*(s32 *)(sp + 0x158) + *(s32 *)(sp + 0x148))) >> 10;
                if (*(u32 *)(arg0 + 0x60) & 0x10) {
                    for (k = 3; k >= 0; k--) {
                        *(s32 *)(sp + 0x138 + k * 16) = 0xFFFFFF;
                    }
                }
                PKT_COLOR(0);
                PKT_COLOR(1);
                PKT_COLOR(2);
                PKT_COLOR(3);
                PKT_UV(0);
                PKT_UV(1);
                PKT_UV(2);
                PKT_UV(3);
                PKT_XYZ(0);
                PKT_XYZ(1);
                PKT_XYZ(2);
                PKT_XYZ(3);
                *(u64 *)(pkt + 0x28) = *(u64 *)(*(u8 **)(arg1 + 0x34) + *(s32 *)(arg1 + 0x30) * 16);
                if (key < 0) {
                    slot = D_00387AE0 + node[5] * 8;
                    tail = *(u8 **)(slot + 4);
                } else if (key >= 0x1000) {
                    slot = D_00387AE0 + node[5] * 8 + 0xFFF0;
                    tail = *(u8 **)(slot + 4);
                } else {
                    slot = D_00387AE0 + (key * 2 + node[5]) * 8;
                    tail = *(u8 **)(slot + 4);
                }
                *(u8 **)(tail + 4) = pkt;
                *(u8 **)(slot + 4) = pkt;
            }
        }
        u += stepU;
        v += stepU;
        idx++;
        node = *(u8 **)(node + 0xF0);
    } while (node != 0);
}
