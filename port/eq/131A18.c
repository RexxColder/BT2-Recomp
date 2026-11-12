#include "common.h"

extern f32 EftStage_GetTintScale(void);
extern void func_00129C28(void *dst, void *src);
extern void Vec3_Scale(u8 *dst, u8 *src, f32 s);
extern void Vec4_Sub(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Cross(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Normalize(u8 *dst, u8 *src);
extern void Vec3_ScaleAdd(u8 *dst, u8 *a, u8 *b, f32 s);
extern s32 func_001294B0(void *dst, void *src, s32 n, s32 flag);

extern u64 D_0036DB90[8];
extern f32 D_00384214;
extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

/* float -> byte with the 2^31 split used by the game */
static u32 FloatToU32(f32 x) {
    if (x >= 2147483648.0f) {
        return (u32)(s32)(x - 2147483648.0f) | 0x80000000;
    }
    return (u32)(s32)x;
}

/* Link pkt at the end of the ordering-table bucket for depth key. */
static void OtLink(s32 key, u8 *pkt) {
    u8 *slot;
    u8 *tail;

    if (key < 0) {
        slot = D_00387AE0;
    } else if (key >= 0x1000) {
        slot = D_00387AE0 + 0xFFF0;
    } else {
        slot = D_00387AE0 + key * 16;
    }
    tail = *(u8 **)(slot + 4);
    *(u8 **)(tail + 4) = pkt;
    *(u8 **)(slot + 4) = pkt;
}

/* Draws the 3 strip segments of a quad ribbon (colored quads in a GIF packet), linked in the OT. */
s32 func_00131A18(u8 *arg0) {
    u8 sp[0x1e0];   /* tamano de locales del original (antes 0x1d8) */
    u8 *obj;
    u8 *seg;
    u8 *next;
    f32 tint;
    f32 widthPos;
    f32 widthNeg;
    f32 u0;
    f32 u1;
    f32 vOfs;
    f32 vStep;
    s32 first;
    s32 i;
    s32 k;
    s32 depth;
    u64 tex;
    u8 *pkt;
    u8 *vtx;

    obj = *(u8 **)(arg0 + 0x38);
    *(s32 *)(sp + 0x1D0) = 1;
    u1 = D_00384214;
    vStep = u1;
    u0 = 0.0f;
    widthPos = *(f32 *)(obj + 0xB0);
    vOfs = *(f32 *)(obj + 0xE4);
    for (i = 0; i < 8; i++) {
        *(u64 *)(sp + 0x190 + i * 8) = D_0036DB90[i];
    }

    tint = EftStage_GetTintScale();
    func_00129C28(sp + 0x40, gBtlCamView + 0x1F0);
    for (i = 0; i < 4; i++) {
        func_00129C28(sp + 0x150 + i * 16, sp + 0x190 + i * 16);
    }
    for (i = 0; i < 4; i++) {
        *(f32 *)(sp + i * 16) = *(f32 *)(obj + 0x80);
        *(f32 *)(sp + i * 16 + 4) = *(f32 *)(obj + 0x84) - (*(f32 *)(obj + 0xB4) * 0.25f) * (f32)i;
        *(f32 *)(sp + i * 16 + 8) = *(f32 *)(obj + 0x88);
        *(f32 *)(sp + i * 16 + 12) = 1.0f;
    }
    Vec3_Scale(sp + 0x60, obj + 0xA0, tint);
    Vec3_Scale(sp + 0x70, obj + 0xA0, tint);
    Vec3_Scale(sp + 0x80, obj + 0xA0, tint);
    Vec3_Scale(sp + 0x90, obj + 0xA0, tint);
    widthNeg = -widthPos;

    seg = sp;
    for (k = 0; k < 3; k++) {
        next = seg + 0x10;
        Vec4_Sub(sp + 0xA0, next, seg);
        Vec4_Sub(sp + 0x50, seg, sp + 0x40);
        Vec3_Cross(sp + 0xA0, sp + 0xA0, sp + 0x50);
        Vec3_Normalize(sp + 0xA0, sp + 0xA0);
        first = *(s32 *)(sp + 0x1D0);
        if (first != 0) {
            Vec3_ScaleAdd(sp + 0x110, sp + 0xA0, seg, widthPos);
            *(s32 *)(sp + 0x1D0) = 0;
            Vec3_ScaleAdd(sp + 0x120, sp + 0xA0, seg, widthNeg);
        } else {
            func_00129C28(sp + 0x110, sp + 0xB0);
            func_00129C28(sp + 0x120, sp + 0xC0);
        }
        Vec3_ScaleAdd(sp + 0x130, sp + 0xA0, next, widthPos);
        Vec3_ScaleAdd(sp + 0x140, sp + 0xA0, next, widthNeg);
        func_00129C28(sp + 0xB0, sp + 0x130);
        func_00129C28(sp + 0xC0, sp + 0x140);
        *(f32 *)(sp + 0x11C) = 1.0f;
        *(f32 *)(sp + 0x14C) = 1.0f;
        *(f32 *)(sp + 0x13C) = 1.0f;
        *(f32 *)(sp + 0x12C) = 1.0f;

        if (func_001294B0(sp + 0xD0, sp + 0x110, 4, 1) != 0) {
            *(f32 *)(sp + 0x164) = u0 + vOfs;
            *(f32 *)(sp + 0x184) = u1 + vOfs;
            depth = (*(s32 *)(sp + 0xD8) + *(s32 *)(sp + 0x108) + (*(s32 *)(sp + 0xF8) + *(s32 *)(sp + 0xE8))) >> 10;
            *(f32 *)(sp + 0x154) = u0 + vOfs;
            *(f32 *)(sp + 0x174) = u1 + vOfs;
            if (k == 2) {
                *(f32 *)(sp + 0x8C) = 0.0f;
                *(f32 *)(sp + 0x9C) = 0.0f;
            }
            tex = *(u64 *)(*(u8 **)(obj + 0xE8) + 0x10);

            if (*(f32 *)(sp + 0x6C) > 0.0f || *(f32 *)(sp + 0x7C) > 0.0f || *(f32 *)(sp + 0x8C) > 0.0f) {
                pkt = D_00387AD8;
                D_00387AD8 = pkt + 0x30;
                *(u64 *)(pkt + 0x00) = 0xA0000002ULL;
                *(u64 *)(pkt + 0x10) = 0x1000000000008001ULL;
                *(u64 *)(pkt + 0x18) = 0xE;
                *(u64 *)(pkt + 0x28) = 8;
                *(u64 *)(pkt + 0x20) = 0;
                OtLink(depth, pkt);

                pkt = D_00387AD8;
                D_00387AD8 = pkt + 0x90;
                *(u64 *)(pkt + 0x10) = 0xE400000000008001ULL;
                *(u64 *)(pkt + 0x20) = 0x5C;
                *(u64 *)(pkt + 0x00) = 0xA0000008ULL;
                *(u64 *)(pkt + 0x18) = 0x42142142142160ULL;
                for (i = 0; i < 4; i++) {
                    static const s32 pktOfs[4] = {0x30, 0x48, 0x60, 0x78};
                    static const s32 fOfs[4] = {0x34, 0x4C, 0x64, 0x7C};
                    static const s32 uvSrc[4] = {0x158, 0x168, 0x178, 0x188};
                    u8 *col = sp + 0x60 + i * 16;
                    *(u8 *)(pkt + pktOfs[i] + 0) = (u8)FloatToU32(*(f32 *)(col + 0));
                    *(u8 *)(pkt + pktOfs[i] + 1) = (u8)FloatToU32(*(f32 *)(col + 4));
                    *(u8 *)(pkt + pktOfs[i] + 2) = (u8)FloatToU32(*(f32 *)(col + 8));
                    *(u8 *)(pkt + pktOfs[i] + 3) = (u8)FloatToU32(*(f32 *)(col + 12));
                    *(f32 *)(pkt + fOfs[i]) = *(f32 *)(sp + uvSrc[i]);
                }
                *(u64 *)(pkt + 0x28) = tex;
                *(f32 *)(pkt + 0x38) = *(f32 *)(sp + 0x150);
                *(f32 *)(pkt + 0x3C) = *(f32 *)(sp + 0x154);
                *(f32 *)(pkt + 0x50) = *(f32 *)(sp + 0x160);
                *(f32 *)(pkt + 0x54) = *(f32 *)(sp + 0x164);
                *(f32 *)(pkt + 0x68) = *(f32 *)(sp + 0x170);
                *(f32 *)(pkt + 0x6C) = *(f32 *)(sp + 0x174);
                *(f32 *)(pkt + 0x80) = *(f32 *)(sp + 0x180);
                *(f32 *)(pkt + 0x84) = *(f32 *)(sp + 0x184);
                for (i = 0; i < 4; i++) {
                    vtx = pkt + 0x40 + i * 0x18;
                    *(u16 *)(vtx + 0) = *(u16 *)(sp + 0xD0 + i * 16);
                    *(u16 *)(vtx + 2) = *(u16 *)(sp + 0xD4 + i * 16);
                    *(u64 *)vtx = (*(u64 *)vtx & 0xFF000000FFFFFFFFULL) |
                                  ((u64)((u32)*(s32 *)(sp + 0xD8 + i * 16) & 0xFFFFFF) << 32);
                    *(u8 *)(vtx + 7) = 0xFF;
                }
                OtLink(depth, pkt);
            }
            u0 = u0 + vStep;
            u1 = u1 + vStep;
            if (k >= 2) {
                u1 = 1.0f;
            }
        }
        seg = next;
    }
    return 0;
}
