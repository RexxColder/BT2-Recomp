#include "common.h"

extern u8 *gBtlCamView;
extern u8 *D_00387870;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern u8 D_0036EB20[];

extern void func_00129C28(u8 *dst, u8 *src);
extern void func_00129C38(u8 *dst, u8 *src);
extern void Vec3_Sub(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Add(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Cross(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Normalize(u8 *dst, u8 *src);
extern void Vec3_Scale(u8 *dst, u8 *src, f32 s);
extern s32 func_001294B0(u8 *out, u8 *in, s32 n, s32 flag);
extern void Vec4_ToInt(u8 *dst, u8 *src);

/* Draws a ribbon (linked list of segments at *list, next at +0x60) as one 0x90-byte GIF quad per segment pair
   (segment, next): the quad is the pair's two end points widened along the camera-facing normal
   by seg[4] / seg[8] times the list scale at +0x38. `obj` picks the texture word, `ctx` the owner. */
void func_001B1A20(u8 *obj, u8 *ctx, u8 *list) {
    u8 sp[0x1b0];   /* tamano de locales del original (antes 0x1a8) */
    u64 tex;
    u8 *seg;
    u8 *next;
    u8 *pkt;
    u8 *slot;
    u8 *slot2;
    s32 first = 1;
    s32 i;
    s32 key;
    u8 *pos0;
    u8 *pos1;

    __builtin_memcpy(sp, D_0036EB20, 0x40);
    if (*(s32 *)(obj + 0x34) == 0) {
        tex = *(u64 *)(D_00387870 + *(s32 *)(obj + 4) * 16 + 0x18);
    } else {
        tex = *(u64 *)(ctx + 0xAA8);
    }
    func_00129C28(sp + 0xE0, gBtlCamView + 0x1F0);

    seg = *(u8 **)list;
    while (seg != 0) {
        next = *(u8 **)(seg + 0x60);
        if (next == 0) {
            break;
        }
        if (!(*(u32 *)seg & 2)) {
            seg = next;
            continue;
        }
        pos0 = seg + 0x40;
        pos1 = next + 0x40;
        Vec3_Sub(sp + 0xF0, pos1, pos0);
        Vec3_Sub(sp + 0x100, pos0, sp + 0xE0);
        Vec3_Cross(sp + 0xF0, sp + 0xF0, sp + 0x100);
        Vec3_Normalize(sp + 0xF0, sp + 0xF0);
        if (first) {
            Vec3_Scale(sp + 0x110, sp + 0xF0, *(f32 *)(seg + 4) * *(f32 *)(list + 0x38));
            Vec3_Scale(sp + 0x120, sp + 0xF0, *(f32 *)(seg + 8) * *(f32 *)(list + 0x38));
            Vec3_Add(sp + 0x40, pos0, sp + 0x110);
            Vec3_Sub(sp + 0x50, pos0, sp + 0x120);
        } else {
            func_00129C38(sp + 0x40, sp + 0x80);
            func_00129C38(sp + 0x50, sp + 0x90);
        }
        first = 0;
        Vec3_Scale(sp + 0x110, sp + 0xF0, *(f32 *)(next + 4) * *(f32 *)(list + 0x38));
        Vec3_Scale(sp + 0x120, sp + 0xF0, *(f32 *)(next + 8) * *(f32 *)(list + 0x38));
        Vec3_Add(sp + 0x60, pos1, sp + 0x110);
        Vec3_Sub(sp + 0x70, pos1, sp + 0x120);
        func_00129C38(sp + 0x80, sp + 0x60);
        func_00129C38(sp + 0x90, sp + 0x70);
        if (func_001294B0(sp + 0x130, sp + 0x40, 4, 1) == 0) {
            seg = *(u8 **)(seg + 0x60);
            continue;
        }

        pkt = D_00387AD8;
        D_00387AD8 = pkt + 0x90;
        if (pkt == 0) {
            return;
        }
        *(u64 *)(pkt + 0x20) = 0x5C;
        *(u64 *)(pkt + 0x00) = 0xA0000008ull;
        *(u64 *)(pkt + 0x10) = 0xE400000000008001ull;
        *(u64 *)(pkt + 0x18) = 0x0042142142142160ull;
        for (i = 0; i < 4; i++) {
            Vec3_Scale(sp + 0xA0 + 16 * i, sp + 16 * i, 1.0f / (f32)*(s32 *)(sp + 0x13C + 16 * i));
        }
        Vec4_ToInt(sp + 0x170, seg + 0x50);
        Vec4_ToInt(sp + 0x180, next + 0x50);
        key = (*(s32 *)(sp + 0x138) + *(s32 *)(sp + 0x168) + (*(s32 *)(sp + 0x158) + *(s32 *)(sp + 0x148))) >> 10;
        if (*(u32 *)(ctx + 0xA40) & 0x10) {
            for (i = 3; i >= 0; i--) {
                *(s32 *)(sp + 0x138 + 16 * i) = 0xFFFFFF;
            }
        }
        for (i = 0; i < 4; i++) {
            u8 *p = pkt + 0x30 + 0x18 * i;
            u8 *c = (i < 2) ? sp + 0x170 : sp + 0x180;
            p[0] = c[0];
            p[1] = c[4];
            p[2] = c[8];
            p[3] = c[12];
            *(f32 *)(p + 4) = *(f32 *)(sp + 0xA8 + 16 * i);
            *(f32 *)(p + 8) = *(f32 *)(sp + 0xA0 + 16 * i);
            *(f32 *)(p + 12) = *(f32 *)(sp + 0xA4 + 16 * i);
            *(u16 *)(p + 0x10) = *(u16 *)(sp + 0x130 + 16 * i);
            *(u16 *)(p + 0x12) = *(u16 *)(sp + 0x134 + 16 * i);
            *(u64 *)(p + 0x10) = (*(u64 *)(p + 0x10) & 0xFF000000FFFFFFFFull) |
                                 ((u64)(*(u32 *)(sp + 0x138 + 16 * i) & 0xFFFFFF) << 32);
            p[0x17] = 0xFF;
        }
        *(u64 *)(pkt + 0x28) = tex;

        if (key < 0) {
            slot = D_00387AE0 + 8;
        } else if (key < 0x1000) {
            slot = D_00387AE0 + key * 16 + 8;
        } else {
            slot = D_00387AE0 + 0xFFF8;
        }
        slot2 = *(u8 **)(slot + 4);
        *(u8 **)(slot2 + 4) = pkt;
        *(u8 **)(slot + 4) = pkt;
        seg = *(u8 **)(seg + 0x60);
    }
}
