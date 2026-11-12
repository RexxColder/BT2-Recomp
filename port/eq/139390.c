#include "common.h"
void bt2_fightlog_note(const char *fmt, ...); /* TEMP TEX0 */

/* 0x00139390: queues up to two GIF triangles for a screen-space quad of three transformed vertices. The vertices
 * (func_00129A50) are tested against the visible screen window (the window bounds depend on func_00126698 /
 * func_00126588); the triangles are drawn when any vertex is inside the window and any colour has alpha > 0.
 * Triangle 1 uses obj colours as they are, triangle 2 scales the alphas by alphas[0/1/2]; a single triangle is
 * drawn when all of them are <= D_003842EC. */
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern f32 D_003842EC;

s32 func_00126698(void);
s32 func_00126588(void);
void func_00129A50(u8 *verts, u8 *uvs, u8 *obj, s32 n);
void func_00129C28(u8 *dst, u8 *src);

/* float -> u32 style truncation used for the colour bytes (cvt.w.s with the 2^31 fix-up) */
static s32 f2u(f32 f) {
    if (f >= 2147483648.0f) {
        return (s32)(f - 2147483648.0f) | (s32)0x80000000;
    }
    return (s32)f;
}

/* append pkt to the list slot: off < 0 -> slot idx, 0 <= off < 0x1000 -> slot idx + 2*off, else slot idx + 0xFFF0 bytes */
static void link_pkt(u8 *pkt, s32 idx, s32 off) {
    u8 *slot;
    u8 *tail;

    if (off < 0) {
        slot = D_00387AE0 + idx * 8;
    } else if (off >= 0x1000) {
        slot = D_00387AE0 + idx * 8 + 0xFFF0;
    } else {
        slot = D_00387AE0 + (off * 2 + idx) * 8;
    }
    tail = *(u8 **)(slot + 4);
    *(u8 **)(tail + 4) = pkt;
    *(u8 **)(slot + 4) = pkt;
}

static void vtx_pos(u8 *q, s32 off, u8 *v) {
    *(u16 *)(q + off) = *(u16 *)v;
    *(u16 *)(q + off + 2) = *(u16 *)(v + 4);
    *(u32 *)(q + off + 4) = (*(u32 *)(q + off + 4) & 0xFF000000u) | (*(u32 *)(v + 8) & 0xFFFFFFu);
    q[off + 7] = 0xFF;
}

static void vtx_col(u8 *q, s32 off, f32 *c) {
    q[off + 0] = (u8)f2u(c[0]);
    q[off + 1] = (u8)f2u(c[1]);
    q[off + 2] = (u8)f2u(c[2]);
    q[off + 3] = (u8)f2u(c[3]);
}

/* 1 when the vertex is NOT inside the window (the caller draws when some vertex returns 0) */
static s32 vtx_outside(u8 *v) {
    s32 hi = 0x910;
    s32 lo = 0x6F0;
    s32 out = 1;
    s32 x;
    s32 y;

    if (func_00126698() == 0) {
        if (func_00126588() != 0) {
            lo = 0x7F0;
        } else {
            hi = 0x810;
        }
    }
    x = *(s32 *)v;
    if (*(s32 *)(v + 8) > 0 && x < hi * 16 && lo * 16 < x) {
        y = *(s32 *)(v + 4);
        if (y < 0x8F00) {
            out = y < 0x7101;
        }
    }
    return out;
}

void func_00139390(u8 *obj, s32 unused, u64 *tags, f32 *alphas, s32 bias) {
    u8 sp[0xC0];
    u8 *colA = obj + 0x20;
    u8 *colB = obj + 0x50;
    u8 *colC = obj + 0x80;
    s32 n = 2;
    s32 t;
    s32 off;
    u8 *q;
    f32 *c;

    func_00129A50(sp, sp + 0x30, obj, 3);
    if (vtx_outside(sp) && vtx_outside(sp + 0x10) && vtx_outside(sp + 0x20)) {
        return;
    }
    off = (*(s32 *)(sp + 8) >> 8) - bias;
    if (!(*(f32 *)(colA + 0xC) > 0.0f)) {
        if (!(*(f32 *)(colB + 0xC) > 0.0f)) {
            if (*(f32 *)(colC + 0xC) <= 0.0f) {
                return;
            }
        }
    }
    if (alphas[3] <= D_003842EC && alphas[7] <= D_003842EC && alphas[11] <= D_003842EC) {
        n = 1;
    }
    func_00129C28(sp + 0x60, colA);
    func_00129C28(sp + 0x70, colB);
    func_00129C28(sp + 0x80, colC);
    func_00129C28(sp + 0x90, colA);
    func_00129C28(sp + 0xA0, colB);
    func_00129C28(sp + 0xB0, colC);
    *(f32 *)(sp + 0x9C) = *(f32 *)(sp + 0x9C) * alphas[3];
    *(f32 *)(sp + 0xAC) = *(f32 *)(sp + 0xAC) * alphas[7];
    *(f32 *)(sp + 0xBC) = *(f32 *)(sp + 0xBC) * alphas[11];

    c = (f32 *)(sp + 0x60);
    for (t = 0; t < n; t++) {
        q = D_00387AD8;
        D_00387AD8 = q + 0x80;
        *(u64 *)(q + 0x00) = 0xA0000007ull;
        *(u64 *)(q + 0x10) = 0xC400000000008001ull;
        *(u64 *)(q + 0x18) = 0xF42142142160ull;
        *(u64 *)(q + 0x20) = 0x5B;
        vtx_col(q, 0x30, c);
        *(f32 *)(q + 0x34) = *(f32 *)(sp + 0x38);
        vtx_col(q, 0x48, c + 4);
        *(f32 *)(q + 0x4C) = *(f32 *)(sp + 0x48);
        vtx_col(q, 0x60, c + 8);
        *(f32 *)(q + 0x64) = *(f32 *)(sp + 0x58);
        *(u64 *)(q + 0x28) = tags[t];
        if ((u32)(*(u64 *)(q + 0x28) >> 32) == 0 && (u32)*(u64 *)(q + 0x28) > 0xFFFFu) bt2_fightlog_note("TEX0TRUNC 139390 %llx", (unsigned long long)*(u64 *)(q + 0x28)); /* TEMP TEX0 */
        *(f32 *)(q + 0x38) = *(f32 *)(sp + 0x30);
        *(f32 *)(q + 0x3C) = *(f32 *)(sp + 0x34);
        *(f32 *)(q + 0x50) = *(f32 *)(sp + 0x40);
        *(f32 *)(q + 0x54) = *(f32 *)(sp + 0x44);
        *(f32 *)(q + 0x68) = *(f32 *)(sp + 0x50);
        *(f32 *)(q + 0x6C) = *(f32 *)(sp + 0x54);
        vtx_pos(q, 0x40, sp);
        vtx_pos(q, 0x58, sp + 0x10);
        vtx_pos(q, 0x70, sp + 0x20);
        link_pkt(q, t, off);
        c += 12;
    }
}
