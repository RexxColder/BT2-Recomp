#include "common.h"

extern f32 D_00384EAC;
extern f32 D_00384EB0;
extern f32 D_00384EB4;
extern f32 D_00384EB8;
extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_00129B58(u8 *arg0, u8 *arg1, u8 *arg2);
void Vec3_Normalize(u8 *arg0, u8 *arg1);
void EftMath_MtxFromDir(u8 *arg0, u8 *arg1, f32 farg0);
void func_00129C50(u8 *arg0, u8 *arg1, u8 *arg2);
void Vec3_Add(u8 *arg0, u8 *arg1, u8 *arg2);
void func_00129FE0(u8 *a, u8 *b, u8 *c, s32 d, s32 e);
s32 func_0012E840(u8 *p);

/* 0x001A7390: billboard quad. Position (x,y,z) = farg0..2; half sizes hx = farg3 * scale / 16 and hy = farg4 *
   scale / 16, rotated by the angle farg10 (wrapped with D_00384EAC..EB8) into a camera-facing matrix; the four
   corners are projected (func_00129FE0) and, unless func_0012E840 rejects one of them, emitted as a GS sprite packet
   (0x80 bytes from the bump pointer D_00387AD8) linked into the ordering table D_00387AE0. */
s32 func_001A7390(u32 cr, u32 cg, u32 cb, u32 ca, s32 ot, s64 tag, f32 x, f32 y, f32 z, f32 farg3, f32 farg4,
                  f32 u0, f32 v0, f32 u1, f32 v1, f32 scale, f32 angle) {
    u8 sp[0x1A0];
    u8 *pkt;
    u8 *link;
    u8 *prev;
    u8 *p;
    u8 *vpos = sp + 0x80;
    u8 *vdir = sp + 0x90;
    u8 *mtx = sp + 0xA0;
    f32 hx;
    f32 hy;
    f32 ang;
    s32 i;
    s32 r;
    s32 depth;

    ang = angle;
    if (D_00384EAC < ang) {
        ang = ang - D_00384EB0;
    } else if (ang < D_00384EB4) {
        ang = ang + D_00384EB8;
    }
    *(u32 *)(sp + 0xE0) = cg & 0xFF;
    *(u32 *)(sp + 0xE4) = cb & 0xFF;
    *(u32 *)(sp + 0xE8) = ca & 0xFF;
    *(s64 *)(sp + 0xF0) = tag;
    hx = farg3 * scale * 0.0625f;
    hy = farg4 * scale * 0.0625f;
    Vec4_Set(vpos, x, y, z, 1.0f);
    func_00129B58(vdir, gBtlCamView + 0x1F0, vpos);
    Vec3_Normalize(vdir, vdir);
    EftMath_MtxFromDir(mtx, vdir, ang);
    Vec4_Set(sp + 0x40, 0.0f - hx, 0.0f - hy, 0.0f, 1.0f);
    Vec4_Set(sp + 0x50, hx, 0.0f - hy, 0.0f, 1.0f);
    Vec4_Set(sp + 0x60, 0.0f - hx, hy, 0.0f, 1.0f);
    Vec4_Set(sp + 0x70, hx, hy, 0.0f, 1.0f);
    for (i = 0; i < 4; i++) {
        p = sp + 0x40 + i * 16;
        func_00129C50(p, mtx, p);
        Vec3_Add(p, p, vpos);
        *(f32 *)(p + 0xC) = 1.0f;
    }
    func_00129FE0(sp, gBtlCamView + 0x100, sp + 0x40, 4, 1);
    r = func_0012E840(sp);
    if (r != 0) {
        return r;
    }
    r = func_0012E840(sp + 0x10);
    if (r != 0) {
        return r;
    }
    r = func_0012E840(sp + 0x20);
    if (r != 0) {
        return r;
    }
    r = func_0012E840(sp + 0x30);
    if (r != 0) {
        return r;
    }

    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x80;
    *(s64 *)(pkt + 0x00) = 0xA0000007;
    *(s64 *)(pkt + 0x20) = 0x54;
    *(s64 *)(pkt + 0x10) = (s64)0xC400000000008001ULL;
    *(s64 *)(pkt + 0x18) = 0xF42424242160LL;
    pkt[0x30] = (u8)cr;
    pkt[0x31] = (u8)*(u32 *)(sp + 0xE0);
    pkt[0x32] = (u8)*(u32 *)(sp + 0xE4);
    *(f32 *)(pkt + 0x34) = 1.0f;
    pkt[0x33] = (u8)*(u32 *)(sp + 0xE8);
    *(s64 *)(pkt + 0x28) = *(s64 *)(sp + 0xF0);
    *(f32 *)(pkt + 0x4C) = v0;
    *(f32 *)(pkt + 0x58) = u0;
    *(f32 *)(pkt + 0x68) = u1;
    *(f32 *)(pkt + 0x6C) = v1;
    *(f32 *)(pkt + 0x38) = u0;
    *(f32 *)(pkt + 0x3C) = v0;
    *(f32 *)(pkt + 0x48) = u1;
    *(f32 *)(pkt + 0x5C) = v1;
    *(u16 *)(pkt + 0x40) = *(u16 *)(sp + 0x00);
    *(u16 *)(pkt + 0x42) = *(u16 *)(sp + 0x04);
    *(u64 *)(pkt + 0x40) = (*(u64 *)(pkt + 0x40) & 0xFF000000FFFFFFFFULL) | ((u64)(*(u32 *)(sp + 0x08) & 0xFFFFFF) << 32);
    pkt[0x47] = 0xFF;
    *(u16 *)(pkt + 0x50) = *(u16 *)(sp + 0x10);
    *(u16 *)(pkt + 0x52) = *(u16 *)(sp + 0x14);
    *(u64 *)(pkt + 0x50) = (*(u64 *)(pkt + 0x50) & 0xFF000000FFFFFFFFULL) | ((u64)(*(u32 *)(sp + 0x18) & 0xFFFFFF) << 32);
    pkt[0x57] = 0xFF;
    *(u16 *)(pkt + 0x60) = *(u16 *)(sp + 0x20);
    *(u16 *)(pkt + 0x62) = *(u16 *)(sp + 0x24);
    *(u64 *)(pkt + 0x60) = (*(u64 *)(pkt + 0x60) & 0xFF000000FFFFFFFFULL) | ((u64)(*(u32 *)(sp + 0x28) & 0xFFFFFF) << 32);
    pkt[0x67] = 0xFF;
    *(u16 *)(pkt + 0x70) = *(u16 *)(sp + 0x30);
    *(u16 *)(pkt + 0x72) = *(u16 *)(sp + 0x34);
    *(u64 *)(pkt + 0x70) = (*(u64 *)(pkt + 0x70) & 0xFF000000FFFFFFFFULL) | ((u64)(*(u32 *)(sp + 0x38) & 0xFFFFFF) << 32);
    pkt[0x77] = 0xFF;

    depth = *(s32 *)(sp + 0x08) >> 8;
    if (depth < 0) {
        link = D_00387AE0 + (ot << 3);
        prev = *(u8 **)(link + 4);
    } else if (depth < 0x1000) {
        link = D_00387AE0 + ((depth * 2 + ot) << 3);
        prev = *(u8 **)(link + 4);
    } else {
        link = D_00387AE0 + (ot << 3) + 0xFFF0;
        prev = *(u8 **)(link + 4);
    }
    *(u8 **)(prev + 4) = pkt;
    *(u8 **)(link + 4) = pkt;
    return (s32)prev;
}
