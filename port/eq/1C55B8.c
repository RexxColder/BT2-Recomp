#include "common.h"

void func_00129C28(f32 *dst, f32 *src);
void func_00129B58(f32 *dst, f32 *a, f32 *b);
void Vec3_Cross(f32 *dst, f32 *a, f32 *b);
void Vec3_Normalize(f32 *dst, f32 *src);
void func_00129BD0(f32 *dst, f32 *src, f32 s);
void Vec3_Sub(f32 *dst, f32 *a, f32 *b);
void Vec3_Add(f32 *dst, f32 *a, f32 *b);
void func_001294B0(f32 *out, f32 *in, s32 count, s32 arg3);
void func_0012C250(f32 *tri, u8 *cam, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s64 arg6, s32 arg7);
extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern f32 D_0036EF60[], D_0036EFA0[];

/* Appends the packet to the ordering-table bucket for sort key `key`. */
#define LINK_PACKET(pkt, key) \
    do { \
        u8 *slot_; \
        u8 *tail_; \
        if ((key) < 0) { \
            slot_ = D_00387AE0 + 8; \
        } else if ((key) < 0x1000) { \
            slot_ = D_00387AE0 + (key) * 16 + 8; \
        } else { \
            slot_ = D_00387AE0 + 0xFFF8; \
        } \
        tail_ = *(u8 **)(slot_ + 4); \
        *(u8 **)(tail_ + 4) = (pkt); \
        *(u8 **)(slot_ + 4) = (pkt); \
    } while (0)

/* Copies the three vec4 of strip piece m (positions, uv, colours) into the triangle buffer. */
#define LOAD_TRI(strip, uv, m) \
    do { \
        func_00129C28(tri + 0, (strip) + (m) * 4); \
        func_00129C28(tri + 4, (strip) + (m) * 4 + 4); \
        func_00129C28(tri + 8, (strip) + (m) * 4 + 8); \
        func_00129C28(tri + 36, (uv) + (m) * 4); \
        func_00129C28(tri + 40, (uv) + (m) * 4 + 4); \
        func_00129C28(tri + 44, (uv) + (m) * 4 + 8); \
        func_00129C28(tri + 72, col + (m) * 4); \
        func_00129C28(tri + 76, col + (m) * 4 + 4); \
        func_00129C28(tri + 80, col + (m) * 4 + 8); \
    } while (0)

void func_001C55B8(u8 *obj, u8 *rib) {
    f32 tab[32];
    f32 cam[4];
    f32 edge[4];
    f32 toCam[4];
    f32 off[4];
    f32 stripA[16];
    f32 savedA[8];
    f32 stripB[16];
    f32 savedB[8];
    f32 uvA[16];
    f32 uvB[16];
    f32 col[16];
    f32 scr[16];
    f32 tri[108] __attribute__((aligned(16))); /* asm: sp+0x280..0x42F (0x1B0 bytes): 12C250 clips into it (was 84: stack smash) */
    f32 *src;
    u8 *node, *next, *pkt;
    s32 first, i, m, key;

    first = 1;
    __builtin_memcpy(tab, D_0036EF60, 0x40);
    __builtin_memcpy(tab + 16, D_0036EFA0, 0x40);
    __builtin_memset(off, 0, sizeof(off));
    func_00129C28(cam, (f32 *)(gBtlCamView + 0x1F0));
    src = (*(u32 *)(rib + 0x50) & 0x20) ? tab + 16 : tab;
    for (i = 0; i < 4; i++) {
        func_00129C28(uvA + i * 4, src + i * 4);
    }
    if (*(u32 *)(rib + 0x50) & 0x10) {
        for (i = 0; i < 4; i++) {
            func_00129C28(uvB + i * 4, src + i * 4);
            uvB[i * 4] = uvB[i * 4] + *(f32 *)(rib + 0x80);
        }
    }
    node = *(u8 **)(rib + 0);
    if (node == NULL) {
        return;
    }
    do {
        next = *(u8 **)(node + 0x40);
        if (next != NULL) {
            func_00129B58(edge, (f32 *)(next + 0x10), (f32 *)(node + 0x10));
            func_00129B58(toCam, (f32 *)(node + 0x10), cam);
            Vec3_Cross(edge, edge, toCam);
            Vec3_Normalize(edge, edge);
            func_00129BD0(off, edge, *(f32 *)(rib + 0x74));
            if (first) {
                Vec3_Sub(stripA + 0, (f32 *)(node + 0x10), off);
                Vec3_Add(stripA + 4, (f32 *)(node + 0x10), off);
                stripA[3] = 1.0f;
                stripA[7] = 1.0f;
            } else {
                func_00129C28(stripA + 0, savedA + 0);
                func_00129C28(stripA + 4, savedA + 4);
            }
            Vec3_Sub(stripA + 8, (f32 *)(next + 0x10), off);
            Vec3_Add(stripA + 12, (f32 *)(next + 0x10), off);
            stripA[11] = 1.0f;
            stripA[15] = 1.0f;
            func_00129C28(savedA + 0, stripA + 8);
            func_00129C28(savedA + 4, stripA + 12);
            if (*(u32 *)(rib + 0x50) & 0x10) {
                if (first) {
                    func_00129BD0(off, edge, *(f32 *)(rib + 0x78));
                    Vec3_Sub(stripB + 0, (f32 *)(node + 0x10), off);
                    Vec3_Add(stripB + 4, (f32 *)(node + 0x10), off);
                    stripB[3] = 1.0f;
                    stripB[7] = 1.0f;
                } else {
                    func_00129C28(stripB + 0, savedB + 0);
                    func_00129C28(stripB + 4, savedB + 4);
                }
                func_00129BD0(off, edge, *(f32 *)(rib + 0x78));
                Vec3_Sub(stripB + 8, (f32 *)(next + 0x10), off);
                Vec3_Add(stripB + 12, (f32 *)(next + 0x10), off);
                stripB[11] = 1.0f;
                stripB[15] = 1.0f;
                func_00129C28(savedB + 0, stripB + 8);
                func_00129C28(savedB + 4, stripB + 12);
            }
            func_00129C28(col + 0, (f32 *)(node + 0x20));
            first = 0;
            func_00129C28(col + 4, (f32 *)(node + 0x20));
            func_00129C28(col + 8, (f32 *)(next + 0x20));
            func_00129C28(col + 12, (f32 *)(next + 0x20));
            func_001294B0(scr, stripA, 4, 1);
            key = ((s32 *)scr)[2] + ((s32 *)scr)[6] + ((s32 *)scr)[10] + ((s32 *)scr)[14];
            key = key >> 10;
            for (m = 0; m < 2; m++) {
                LOAD_TRI(stripA, uvA, m);
                func_0012C250(tri, gBtlCamView + 0x100, 1, 0, 0, 0,
                              *(s64 *)(rib + 8 + 0x140 + *(u8 *)(node + 4) * 8), key);
            }
            if (*(u32 *)(rib + 0x50) & 0x10) {
                pkt = D_00387AD8;
                D_00387AD8 = pkt + 0x30;
                *(u64 *)(pkt + 0x00) = 0xA0000002ULL;
                *(u64 *)(pkt + 0x10) = 0x1000000000008001ULL;
                *(u64 *)(pkt + 0x18) = 0xE;
                *(u64 *)(pkt + 0x28) = 8;
                *(u64 *)(pkt + 0x20) = 0;
                LINK_PACKET(pkt, key);
                func_00129C28(col + 0, (f32 *)(node + 0x30));
                func_00129C28(col + 4, (f32 *)(node + 0x30));
                func_00129C28(col + 8, (f32 *)(next + 0x30));
                func_00129C28(col + 12, (f32 *)(next + 0x30));
                for (m = 0; m < 2; m++) {
                    LOAD_TRI(stripB, uvB, m);
                    func_0012C250(tri, gBtlCamView + 0x100, 1, 1, 0, 0, *(s64 *)(rib + 0x160), key);
                }
            }
        }
        node = *(u8 **)(node + 0x40);
    } while (node != NULL);
}
