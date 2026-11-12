#include "common.h"

extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

extern void func_00129C28(u8 *dst, u8 *src);
extern void Vec4_Set(u8 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec3_Sub(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Add(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Cross(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Normalize(u8 *dst, u8 *src);
extern void Vec3_Scale(u8 *dst, u8 *src, f32 s);
extern s32 func_001294B0(u8 *out, u8 *in, s32 n, s32 flag);
extern void Vec4_ToInt(u8 *dst, u8 *src);
extern void func_001BEAC0(u8 *a0, u8 *a1, u8 *node, u8 *a3);
extern void func_001BE0D8(u8 *a0, u8 *a1, u8 *node, u8 *a3);

/* Walks the billboard list at *list and queues each node's quad (4 projected corners, one 0x90-byte GIF packet)
   into the ordering table at D_00387AE0. Nodes with a callback flag (+0xE8) go to func_001BEAC0 / func_001BE0D8
   (picked by cfg[3]); cfg[9] makes the quad a double-width strip around the axis. */
void func_001BF030(u8 **list, u8 *ctx, u8 *cfg) {
    u8 sp[0x1B0];
    u8 *node;
    u8 *pkt;
    u8 *slot;
    u8 *slot2;
    u8 *pvec;
    s32 i;
    s32 key;
    s32 mask;

    func_00129C28(sp + 0x40, gBtlCamView + 0x1F0);
    for (i = 0; i < 4; i++) {
        *(f32 *)(sp + 0x60 + 16 * i) = (f32)(i - 2 * (i / 2));
        *(f32 *)(sp + 0x64 + 16 * i) = (f32)(i / 2);
        *(f32 *)(sp + 0x68 + 16 * i) = 1.0f;
        *(s32 *)(sp + 0x6C + 16 * i) = 0;
        Vec4_Set(sp + 16 * i, 0.0f, 0.0f, 0.0f, 1.0f);
    }

    node = *list;
    if (node == 0) {
        return;
    }
    do {
        if (*(s32 *)(node + 0xE8) != 0) {
            if (cfg[3] == 0) {
                func_001BEAC0((u8 *)list, ctx, node, cfg);
            } else {
                func_001BE0D8((u8 *)list, ctx, node, cfg);
            }
            node = *(u8 **)(node + 0xE0);
            continue;
        }
        Vec3_Sub(sp + 0x50, node + 0x50, sp + 0x40);
        Vec3_Cross(sp + 0x50, node + 0x60, sp + 0x50);
        Vec3_Normalize(sp + 0x50, sp + 0x50);
        Vec3_Scale(sp + 0xE0, sp + 0x50, *(f32 *)(node + 0x20));
        Vec3_Add(sp + 0x00, node + 0x50, sp + 0xE0);
        Vec3_Sub(sp + 0x10, node + 0x50, sp + 0xE0);
        if (cfg[9] == 0) {
            Vec3_Scale(sp + 0xF0, node + 0x60, *(f32 *)(node + 0x28));
            Vec3_Add(sp + 0x20, sp + 0x00, sp + 0xF0);
            Vec3_Add(sp + 0x30, sp + 0x10, sp + 0xF0);
        } else {
            Vec3_Scale(sp + 0xF0, node + 0x60, *(f32 *)(node + 0x28) * 0.5f);
            Vec3_Add(sp + 0x20, sp + 0x00, sp + 0xF0);
            Vec3_Add(sp + 0x30, sp + 0x10, sp + 0xF0);
            Vec3_Sub(sp + 0x00, sp + 0x00, sp + 0xF0);
            Vec3_Sub(sp + 0x10, sp + 0x10, sp + 0xF0);
        }
        if (func_001294B0(sp + 0x100, sp, 4, 1) == 0) {
            node = *(u8 **)(node + 0xE0);
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
            Vec3_Scale(sp + 0xA0 + 16 * i, sp + 0x60 + 16 * i,
                       1.0f / (f32)*(s32 *)(sp + 0x10C + 16 * i));
        }
        Vec4_ToInt(sp + 0x140, node + 0x70);
        key = (*(s32 *)(sp + 0x108) + *(s32 *)(sp + 0x138) + (*(s32 *)(sp + 0x128) + *(s32 *)(sp + 0x118))) >> 10;
        if (*(u32 *)((u8 *)list + 0x60) & 0x10) {
            for (i = 3; i >= 0; i--) {
                *(s32 *)(sp + 0x108 + 16 * i) = 0xFFFFFF;
            }
        }
        for (i = 0; i < 4; i++) {
            u8 *p = pkt + 0x30 + 0x18 * i;
            p[0] = sp[0x140];
            p[1] = sp[0x144];
            p[2] = sp[0x148];
            p[3] = sp[0x14C];
            *(f32 *)(p + 4) = *(f32 *)(sp + 0xA8 + 16 * i);
            *(f32 *)(p + 8) = *(f32 *)(sp + 0xA0 + 16 * i);
            *(f32 *)(p + 12) = *(f32 *)(sp + 0xA4 + 16 * i);
            *(u16 *)(p + 0x10) = *(u16 *)(sp + 0x100 + 16 * i);
            *(u16 *)(p + 0x12) = *(u16 *)(sp + 0x104 + 16 * i);
            *(u64 *)(p + 0x10) = (*(u64 *)(p + 0x10) & 0xFF000000FFFFFFFFull) |
                                 ((u64)(*(u32 *)(sp + 0x108 + 16 * i) & 0xFFFFFF) << 32);
            p[0x17] = 0xFF;
        }
        *(u64 *)(pkt + 0x28) = *(u64 *)(*(u8 **)(ctx + 0x34) + 16 * *(s32 *)(ctx + 0x30));

        {
            s32 layer = node[5];
            if (key < 0) {
                slot = D_00387AE0 + layer * 8;
                slot2 = *(u8 **)(slot + 4);
            } else if (key < 0x1000) {
                slot = D_00387AE0 + (key * 2 + layer) * 8;
                slot2 = *(u8 **)(slot + 4);
            } else {
                slot = D_00387AE0 + layer * 8 + 0xFFF0;
                slot2 = *(u8 **)(slot + 4);
            }
        }
        *(u8 **)(slot2 + 4) = pkt;
        *(u8 **)(slot + 4) = pkt;
        node = *(u8 **)(node + 0xE0);
    } while (node != 0);
}
