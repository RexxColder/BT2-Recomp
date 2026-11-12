#include "common.h"

/* 0x001C3208: 4-corner billboard quad effect (rotated optional), projected, GS packet 0x90 bytes + OT link. */
extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern f32 D_0038515C;

extern s32 func_00129F60();
extern void Vec4_Set(f32 *v, f32 x, f32 y, f32 z, f32 w);
extern void Vec3_Set(f32 *v, f32 x, f32 y, f32 z);
extern void func_00128EF0(void);
extern void Vu0Cur_LoadIdentity(void);
extern f32 EftMath_WrapAngle(f32 angle);
extern void Vu0Cur_RotateZ(f32 angle);
extern void Vu0Cur_MulVec4();
extern void func_00128F08(void);
extern s32 func_001C2848();
extern void func_001C2878();

/* cvt.w.s with the >= 2^31 unsigned path used by the asm */
static s32 cvt_u(f32 x) {
    if (x >= 2147483648.0f) {
        return (s32)(x - 2147483648.0f) | (s32)0x80000000;
    }
    return (s32)x;
}

/* __fixunssfdi */
static u64 fix_u64(f32 x) {
    if (x <= 0.0f) {
        return 0;
    }
    return (u64)x;
}

/* one packet vertex: xy as shorts at +0, z in bits 32..55 of the qword, 0xFF at +7 */
static void put_vertex(u8 *p, f32 *v) {
    u64 q;

    *(u16 *)(p + 0) = (u16)cvt_u(v[0]);
    *(u16 *)(p + 2) = (u16)cvt_u(v[1]);
    q = *(u64 *)p;
    q = (q & 0xFF000000FFFFFFFFULL) | ((fix_u64(v[2]) & 0xFFFFFF) << 32);
    *(u64 *)p = q;
    p[7] = 0xFF;
}

void func_001C3208(u8 *fx) {
    u8 sp[0x50];
    f32 *c0 = (f32 *)(sp + 0x10);
    f32 *c1 = (f32 *)(sp + 0x20);
    f32 *c2 = (f32 *)(sp + 0x30);
    f32 *c3 = (f32 *)(sp + 0x40);
    u8 *cam = gBtlCamView;
    f32 camScale = *(f32 *)(cam + 0x224);
    s32 count = cvt_u(*(f32 *)(fx + 0x10));
    s32 prod;
    u32 size;
    f32 sz;
    f32 ang;
    u8 *pkt;
    u8 *ot;
    u8 *slot;
    u8 *prev;
    s32 depth;
    s32 ix;
    f32 fa, fb, fc, fd, fe, ff;
    f32 f1v, f2v, f3v, f4v;

    if (count == 0) {
        return;
    }
    func_00129F60(sp, cam + 0x100, fx + 0x20, 1);
    prod = count * cvt_u((camScale * 4096.0f) / (f32)*(s32 *)(sp + 0xC));
    size = (u32)prod >> 12;
    if (size < 2) {
        return;
    }
    sz = (f32)size;
    Vec4_Set(c0, -sz, -sz, 0.0f, 1.0f);
    Vec4_Set(c1, sz, -sz, 0.0f, 1.0f);
    Vec4_Set(c2, -sz, sz, 0.0f, 1.0f);
    Vec4_Set(c3, sz, sz, 0.0f, 1.0f);
    if (*(f32 *)(fx + 0x14) != 0.0f) {
        func_00128EF0();
        Vu0Cur_LoadIdentity();
        ang = EftMath_WrapAngle(*(f32 *)(fx + 0x14));
        *(f32 *)(fx + 0x14) = ang;
        Vu0Cur_RotateZ(ang);
        Vu0Cur_MulVec4(c0, c0);
        Vu0Cur_MulVec4(c1, c1);
        Vu0Cur_MulVec4(c2, c2);
        Vu0Cur_MulVec4(c3, c3);
        func_00128F08();
    }
    Vec3_Set(c0, (f32)*(s32 *)(sp + 0) + c0[0], (f32)*(s32 *)(sp + 4) + c0[1], (f32)*(s32 *)(sp + 8));
    Vec3_Set(c1, (f32)*(s32 *)(sp + 0) + c1[0], (f32)*(s32 *)(sp + 4) + c1[1], (f32)*(s32 *)(sp + 8));
    Vec3_Set(c2, (f32)*(s32 *)(sp + 0) + c2[0], (f32)*(s32 *)(sp + 4) + c2[1], (f32)*(s32 *)(sp + 8));
    Vec3_Set(c3, (f32)*(s32 *)(sp + 0) + c3[0], (f32)*(s32 *)(sp + 4) + c3[1], (f32)*(s32 *)(sp + 8));
    if (func_001C2848((s32)c0[0], (s32)c0[1], (s32)c0[2]) != 0) { return; }
    if (func_001C2848((s32)c1[0], (s32)c1[1], (s32)c1[2]) != 0) { return; }
    if (func_001C2848((s32)c2[0], (s32)c2[1], (s32)c2[2]) != 0) { return; }
    if (func_001C2848((s32)c3[0], (s32)c3[1], (s32)c3[2]) != 0) { return; }

    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x90;
    *(u64 *)(pkt + 0x20) = 0x5C;
    *(u64 *)(pkt + 0x00) = 0xA0000008ULL;
    *(u64 *)(pkt + 0x10) = 0xE400000000008001ULL;
    *(u64 *)(pkt + 0x18) = 0x0042142142142160ULL;
    if ((fx[1] & 1) != 0) {
        func_001C2878(pkt, fx + 0xE0, fx + 0x20, fx + 0x18);
    } else {
        pkt[0x30] = fx[0x18]; pkt[0x31] = fx[0x19]; pkt[0x32] = fx[0x1A]; pkt[0x33] = fx[0x1B];
        *(f32 *)(pkt + 0x34) = 1.0f;
        pkt[0x48] = fx[0x18]; pkt[0x49] = fx[0x19]; pkt[0x4A] = fx[0x1A]; pkt[0x4B] = fx[0x1B];
        *(f32 *)(pkt + 0x4C) = 1.0f;
        pkt[0x60] = fx[0x18]; pkt[0x61] = fx[0x19]; pkt[0x62] = fx[0x1A]; pkt[0x63] = fx[0x1B];
        *(f32 *)(pkt + 0x64) = 1.0f;
        pkt[0x78] = fx[0x18]; pkt[0x79] = fx[0x19]; pkt[0x7A] = fx[0x1A]; pkt[0x7B] = fx[0x1B];
        *(f32 *)(pkt + 0x7C) = 1.0f;
    }
    put_vertex(pkt + 0x40, c0);
    put_vertex(pkt + 0x58, c1);
    put_vertex(pkt + 0x70, c2);
    put_vertex(pkt + 0x88, c3);

    fa = (f32)(s8)fx[0xC] * D_0038515C;
    fb = (f32)(s8)fx[0xD] * D_0038515C;
    fc = (f32)(s8)fx[0xE] * D_0038515C;
    fd = (f32)(s8)fx[0xF] * D_0038515C;
    f3v = fa;
    f4v = fb;
    f1v = fa + fc;
    f2v = fb + fd;
    if ((fx[1] & 0x10) != 0) {
        fe = f3v;
        f3v = f1v;
        f1v = fe;
    }
    if ((fx[1] & 0x20) != 0) {
        ff = f4v;
        f4v = f2v;
        f2v = ff;
    }
    *(f32 *)(pkt + 0x54) = f4v;
    *(f32 *)(pkt + 0x68) = f3v;
    *(f32 *)(pkt + 0x80) = f1v;
    *(f32 *)(pkt + 0x84) = f2v;
    *(f32 *)(pkt + 0x38) = f3v;
    *(f32 *)(pkt + 0x3C) = f4v;
    *(f32 *)(pkt + 0x50) = f1v;
    *(f32 *)(pkt + 0x6C) = f2v;
    *(u64 *)(pkt + 0x28) = *(u64 *)(*(u8 **)(fx + 8) + (fx[3] << 4));

    depth = *(s32 *)(sp + 8) >> 8;
    ot = D_00387AE0;
    if (depth < 0) {
        slot = ot + fx[2] * 8;
        prev = *(u8 **)(slot + 4);
    } else if (depth < 0x1000) {
        slot = ot + (2 * depth + fx[2]) * 8;
        prev = *(u8 **)(slot + 4);
    } else {
        slot = ot + fx[2] * 8 + 0xFFF0;
        prev = *(u8 **)(slot + 4);
    }
    ix = 0;
    (void)ix;
    *(u8 **)(prev + 4) = pkt;
    *(u8 **)(slot + 4) = pkt;
}
