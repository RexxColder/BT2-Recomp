#include "common.h"
void bt2_fightlog_note(const char *fmt, ...); /* TEMP TEX0 */

/* 0x00181040: sibling of 12C468: clips a polygon against 5 planes (func_0012BEC0), projects it (func_0012A108) and
 * queues it as a triangle fan of 0x80-byte GIF packets (colours of vertex k at obj + 0x120 + 0x10 * k, uv from the
 * projector, tag = texInfo tag + (texInfo[2][0x14] * mul << 37)). When base == 2 each triangle is wrapped between
 * two 0x30-byte packets (0x42 / 0x48) and everything goes to list slot 1. Returns 0 (or the projector result when n <= 2). */
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

u8 *func_0012B9B0(void);
s32 func_0012BEC0(u8 *tbl, s32 n, u8 *obj);
s32 func_0012A108(u8 *a0, u8 *a1, u8 *a2, u8 *a3, u8 *t0, s32 t1);

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

s32 func_00181040(u8 *obj, u8 *arg1, u8 *texInfo, s32 base, s32 key, s32 mul) {
    u8 sp[0x130];   /* tamano de locales del original (antes 0x120) */
    u8 *tbl;
    s32 n = 3;
    s32 i;
    s32 j;
    u8 *q;
    u8 *vA = sp;
    u8 *vB;
    u8 *vC;
    u8 *uA = sp + 0x90;
    u8 *uB;
    u8 *uC;
    u8 *cB;
    u8 *cC;
    u8 *texAux;
    s32 res;

    if (key < 0) {
        key = 0xFFFFFF;
    }
    tbl = func_0012B9B0();
    for (i = 0; i < 5; i++) {
        n = func_0012BEC0(tbl, n, obj);
        tbl += 0x10;
    }
    if (n == 0) {
        return 0;
    }
    res = func_0012A108(sp, sp + 0x90, arg1, obj, obj + 0x90, n);
    if (n <= 2) {
        return res;
    }

    for (j = 2; j < n; j++) {
        vB = sp + 0x10 * (j - 1);
        vC = sp + 0x10 * j;
        uB = uA + 0x10 * (j - 1);
        uC = uA + 0x10 * j;
        cB = obj + 0x120 + 0x10 * (j - 1);
        cC = obj + 0x120 + 0x10 * j;

        if (*(s32 *)(vA + 8) > 0xFFFFFF) {
            *(s32 *)(vA + 8) = 0xFFFFFF;
        }
        if (*(s32 *)(vB + 8) > 0xFFFFFF) {
            *(s32 *)(vB + 8) = 0xFFFFFF;
        }
        if (*(s32 *)(vC + 8) > 0xFFFFFF) {
            *(s32 *)(vC + 8) = 0xFFFFFF;
        }

        q = D_00387AD8;
        D_00387AD8 = q + 0x80;
        *(u64 *)(q + 0x18) = 0xF42142142160ull;
        *(u64 *)(q + 0x20) = 0x5B;
        *(u64 *)(q + 0x00) = 0xA0000007ull;
        *(u64 *)(q + 0x10) = 0xC400000000008001ull;
        vtx_col(q, 0x30, (f32 *)(obj + 0x120));
        *(f32 *)(q + 0x34) = *(f32 *)(uA + 8);
        vtx_col(q, 0x48, (f32 *)cB);
        *(f32 *)(q + 0x4C) = *(f32 *)(uB + 8);
        vtx_col(q, 0x60, (f32 *)cC);
        *(f32 *)(q + 0x64) = *(f32 *)(uC + 8);
        vtx_pos(q, 0x40, vA);
        vtx_pos(q, 0x58, vB);
        vtx_pos(q, 0x70, vC);
        *(f32 *)(q + 0x38) = *(f32 *)(uA + 0);
        *(f32 *)(q + 0x3C) = *(f32 *)(uA + 4);
        *(f32 *)(q + 0x50) = *(f32 *)(uB + 0);
        *(f32 *)(q + 0x54) = *(f32 *)(uB + 4);
        *(f32 *)(q + 0x68) = *(f32 *)(uC + 0);
        *(f32 *)(q + 0x6C) = *(f32 *)(uC + 4);
        texAux = *(u8 **)(texInfo + 8);
        *(u64 *)(q + 0x28) = *(u64 *)texInfo + ((u64)(s64)(s32)(*(s32 *)(texAux + 0x14) * mul) << 37);
        if ((u32)(*(u64 *)(q + 0x28) >> 32) == 0 && (u32)*(u64 *)(q + 0x28) > 0xFFFFu) bt2_fightlog_note("TEX0TRUNC 181040 %llx", (unsigned long long)*(u64 *)(q + 0x28)); /* TEMP TEX0 */

        if (base == 2) {
            u8 *p;

            p = D_00387AD8;
            D_00387AD8 = p + 0x30;
            *(u64 *)(p + 0x00) = 0xA0000002ull;
            *(u64 *)(p + 0x10) = 0x1000000000008001ull;
            *(u64 *)(p + 0x18) = 0xE;
            *(u64 *)(p + 0x20) = 0x42;
            *(u64 *)(p + 0x28) = 0x42;
            if ((u32)(*(u64 *)(p + 0x28) >> 32) == 0 && (u32)*(u64 *)(p + 0x28) > 0xFFFFu) bt2_fightlog_note("TEX0TRUNC 181040 %llx", (unsigned long long)*(u64 *)(p + 0x28)); /* TEMP TEX0 */
            link_pkt(p, 1, key);
            link_pkt(q, 1, key);
            p = D_00387AD8;
            D_00387AD8 = p + 0x30;
            *(u64 *)(p + 0x00) = 0xA0000002ull;
            *(u64 *)(p + 0x10) = 0x1000000000008001ull;
            *(u64 *)(p + 0x18) = 0xE;
            *(u64 *)(p + 0x20) = 0x48;
            *(u64 *)(p + 0x28) = 0x42;
            if ((u32)(*(u64 *)(p + 0x28) >> 32) == 0 && (u32)*(u64 *)(p + 0x28) > 0xFFFFu) bt2_fightlog_note("TEX0TRUNC 181040 %llx", (unsigned long long)*(u64 *)(p + 0x28)); /* TEMP TEX0 */
            link_pkt(p, 1, key);
        } else {
            link_pkt(q, base, key);
        }
    }
    return 0;
}
