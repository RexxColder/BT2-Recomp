#include "common.h"

extern void sceVu0UnitMatrix(void *m);
extern void sceVu0RotMatrixY(void *d, void *s, f32 angle);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *v);
extern f32 EftMath_WrapAngle(f32 farg0);
extern void func_00312638(void *dst, void *src, void *k);
extern void func_0012D868(s32 *out, void *a, void *b, s32 n, void *c, void *d);
extern s32 EftShotFx_IsOnScreen(void *p, s32 n);
extern s32 func_001420F0(void);

extern f32 D_00384500;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

/* Inserts pkt into the ordering table slot chosen by z and ot; returns the previous tail node. */
static u8 *OtInsert(u8 *pkt, s32 z, u32 ot) {
    u8 *slot;
    u8 *node;

    if (z < 0) {
        slot = D_00387AE0 + ot * 8;
        node = *(u8 **)(slot + 4);
    } else if (z < 0x1000) {
        slot = D_00387AE0 + (z * 2 + ot) * 8;
        node = *(u8 **)(slot + 4);
    } else {
        slot = D_00387AE0 + ot * 8 + 0xFFF0;
        node = *(u8 **)(slot + 4);
    }
    *(u8 **)(node + 4) = pkt;
    *(u8 **)(slot + 4) = pkt;
    return node;
}

/* Textured quad (4 corners built from w/h scale factors, optional Y rotation) with state packets around it. */
s32 func_00140FA0(u8 *world, u8 *mtx, u8 *ctx, u32 cr, u32 cg, u32 cb, u32 ca, u32 state,
                  f32 angle, f32 w, f32 sx, f32 sz, f32 hs, u64 *tex, u8 ot) {
    u8 sp[0x1C0];
    f32 hh;
    f32 far_z;
    f32 rot_z;
    f32 *v;
    f32 *vtx = (f32 *)(sp + 0x00);
    s32 *uvs = (s32 *)(sp + 0x80);
    u8 *pkt;
    u8 *p2;
    u8 *p3;
    s32 i;
    s32 z;
    u64 old;

    hh = w * 0.5f * hs;
    far_z = w * sx;
    rot_z = w * sz;
    *(s32 *)(sp + 0x04) = 0;
    vtx[0] = -hh;
    vtx[2] = far_z;
    vtx[3] = 1.0f;
    vtx[4] = hh;
    *(s32 *)(sp + 0x14) = 0;
    vtx[6] = far_z;
    vtx[7] = 1.0f;
    vtx[8] = -hh;
    *(s32 *)(sp + 0x24) = 0;
    vtx[10] = rot_z;
    vtx[11] = 1.0f;
    vtx[12] = hh;
    *(s32 *)(sp + 0x34) = 0;
    vtx[14] = rot_z;
    vtx[15] = 1.0f;
    *(u8 **)(sp + 0x140) = world;
    *(u8 **)(sp + 0x144) = mtx;
    *(u8 **)(sp + 0x148) = ctx;
    *(u32 *)(sp + 0x150) = state & 0xFF;
    cr &= 0xFF;
    cg &= 0xFF;
    cb &= 0xFF;
    ca &= 0xFF;

    if (angle != 0.0f) {
        f32 mid = (far_z - rot_z) * 0.5f;
        sceVu0UnitMatrix(sp + 0x100);
        sceVu0RotMatrixY(sp + 0x100, sp + 0x100, EftMath_WrapAngle(angle / 180.0f * D_00384500));
        for (i = 0; i < 4; i++) {
            v = vtx + i * 4;
            v[2] = v[2] - mid;
            sceVu0ApplyMatrix(v, sp + 0x100, v);
            v[2] = v[2] + mid;
        }
    }

    uvs[0] = 0;
    uvs[1] = 0;
    *(f32 *)&uvs[2] = 1.0f;
    uvs[3] = 0;
    *(f32 *)&uvs[4] = 1.0f;
    uvs[5] = 0;
    *(f32 *)&uvs[6] = 1.0f;
    uvs[7] = 0;
    uvs[8] = 0;
    *(f32 *)&uvs[9] = 1.0f;
    *(f32 *)&uvs[10] = 1.0f;
    uvs[11] = 0;
    *(f32 *)&uvs[12] = 1.0f;
    *(f32 *)&uvs[13] = 1.0f;
    *(f32 *)&uvs[14] = 1.0f;
    uvs[15] = 0;

    for (i = 0; i < 4; i++) {
        v = vtx + i * 4;
        sceVu0ApplyMatrix(v, *(u8 **)(sp + 0x144), v);
        func_00312638(v, v, *(u8 **)(sp + 0x140));
        v[3] = 1.0f;
    }
    func_0012D868((s32 *)(sp + 0xC0), *(u8 **)(sp + 0x148), sp, 4, sp + 0x40, sp + 0x80);
    for (i = 0; i < 4; i++) {
        if (EftShotFx_IsOnScreen(sp + 0xC0 + i * 0x10, 4) == 0) {
            return 0;
        }
    }

    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x90;
    if (pkt == NULL) return (s32)(pkt + 0x90);

    *(u64 *)(pkt + 0x20) = 0x5C;
    *(u64 *)(pkt + 0x00) = 0xA0000008ULL;
    *(u64 *)(pkt + 0x10) = 0xE400000000008001ULL;
    *(u64 *)(pkt + 0x18) = 0x42142142142160ULL;
    *(u8 *)(pkt + 0x30) = (u8)cr;
    *(u8 *)(pkt + 0x31) = (u8)cg;
    *(u8 *)(pkt + 0x32) = (u8)cb;
    *(u8 *)(pkt + 0x33) = (u8)ca;
    *(u8 *)(pkt + 0x48) = (u8)cr;
    *(f32 *)(pkt + 0x34) = *(f32 *)(sp + 0x48);
    *(u8 *)(pkt + 0x49) = (u8)cg;
    *(u8 *)(pkt + 0x4A) = (u8)cb;
    *(u8 *)(pkt + 0x4B) = (u8)ca;
    *(u8 *)(pkt + 0x60) = (u8)cr;
    *(f32 *)(pkt + 0x4C) = *(f32 *)(sp + 0x58);
    *(u8 *)(pkt + 0x61) = (u8)cg;
    *(u8 *)(pkt + 0x62) = (u8)cb;
    *(u8 *)(pkt + 0x63) = (u8)ca;
    *(u8 *)(pkt + 0x78) = (u8)cr;
    *(f32 *)(pkt + 0x64) = *(f32 *)(sp + 0x68);
    *(u8 *)(pkt + 0x79) = (u8)cg;
    *(u8 *)(pkt + 0x7A) = (u8)cb;
    *(u8 *)(pkt + 0x7B) = (u8)ca;
    *(f32 *)(pkt + 0x7C) = *(f32 *)(sp + 0x78);
    *(f32 *)(pkt + 0x38) = *(f32 *)(sp + 0x40);
    *(f32 *)(pkt + 0x3C) = *(f32 *)(sp + 0x44);
    *(f32 *)(pkt + 0x50) = *(f32 *)(sp + 0x50);
    *(f32 *)(pkt + 0x54) = *(f32 *)(sp + 0x54);
    *(f32 *)(pkt + 0x68) = *(f32 *)(sp + 0x60);
    *(f32 *)(pkt + 0x6C) = *(f32 *)(sp + 0x64);
    *(f32 *)(pkt + 0x80) = *(f32 *)(sp + 0x70);
    *(f32 *)(pkt + 0x84) = *(f32 *)(sp + 0x74);

    for (i = 0; i < 4; i++) {
        u8 *q = pkt + 0x40 + i * 0x18;
        u8 *src = sp + 0xC0 + i * 0x10;
        *(u16 *)(q + 0) = *(u16 *)(src + 0);
        *(u16 *)(q + 2) = *(u16 *)(src + 4);
        old = *(u64 *)q;
        old = (old & 0xFF000000FFFFFFFFULL) | ((u64)(*(u32 *)(src + 8) & 0xFFFFFF) << 32);
        *(u64 *)q = old;
        *(u8 *)(q + 7) = 0xFF;
    }

    z = ((*(s32 *)(sp + 0xC8) + *(s32 *)(sp + 0xF8)) + (*(s32 *)(sp + 0xE8) + *(s32 *)(sp + 0xD8))) >> 10;
    if (func_001420F0() != 0) {
        z = z - 500;
    } else {
        z = z + 500;
    }
    *(u64 *)(pkt + 0x28) = *tex;

    p2 = D_00387AD8;
    D_00387AD8 = p2 + 0x30;
    if (p2 == NULL) return (s32)(p2 + 0x30);
    *(u64 *)(p2 + 0x00) = 0xA0000002ULL;
    *(u64 *)(p2 + 0x10) = 0x1000000000008001ULL;
    *(u64 *)(p2 + 0x18) = 0xE;
    *(u64 *)(p2 + 0x20) = ((u64)*(u32 *)(sp + 0x150) << 4) | 0x5000D;
    *(u64 *)(p2 + 0x28) = 0x47;
    OtInsert(p2, z, ot);
    OtInsert(pkt, z, ot);

    p3 = D_00387AD8;
    D_00387AD8 = p3 + 0x30;
    if (p3 == NULL) return (s32)(p3 + 0x30);
    *(u64 *)(p3 + 0x00) = 0xA0000002ULL;
    *(u64 *)(p3 + 0x10) = 0x1000000000008001ULL;
    *(u64 *)(p3 + 0x18) = 0xE;
    *(u64 *)(p3 + 0x20) = 0x50000;
    *(u64 *)(p3 + 0x28) = 0x47;
    return (s32)OtInsert(p3, z, ot);
}
