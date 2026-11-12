#include "common.h"

extern void func_00312680(void *dst, void *src, f32 s);
extern void sceVu0UnitMatrix(void *m);
extern void func_00312518(void *m, void *cam);
extern void Vu0Screen_StoreMtx(void *m);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *v);
extern void func_00312638(void *dst, void *src, void *k);
extern void func_00142608(s32 *dst, void *m, void *src);
extern f32 EftStage_GetTintScale(void);
extern u64 __fixunssfdi(f32 x);

extern u8 *gBtlCamView;
extern u8 *gEftStorm;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern u8 D_0036DD40[] __attribute__((section(".data")));
extern u8 D_0036DD50[] __attribute__((section(".data")));

/* Links pkt into the ordering table slot picked by z (16 byte slot stride). */
static void OtInsert16(u8 *pkt, s32 z) {
    u8 *slot;
    u8 *node;

    if (z < 0) {
        slot = D_00387AE0 + 8;
    } else if (z < 0x1000) {
        slot = D_00387AE0 + z * 16 + 8;
    } else {
        slot = D_00387AE0 + 0xFFF8;
    }
    node = *(u8 **)(slot + 4);
    *(u8 **)(node + 4) = pkt;
    *(u8 **)(slot + 4) = pkt;
}

/* Four-entry table of lit quads (entry stride 0x30); each visible entry queues a 0xA0 or 0x110 byte packet. */
void func_001427E8(u8 *entries) {
    u8 sp[0x1C0];
    f32 scale;
    u64 flag = 0xFF00000000000000ULL;
    u64 fill;
    u64 col;
    u8 *e = entries;
    s32 count;
    s32 j;
    s32 div;
    s32 ok;
    s32 *p;
    u8 *pkt;
    u8 *tbl;

    __builtin_memcpy(sp + 0x80, D_0036DD40, 16);
    __builtin_memcpy(sp + 0x90, D_0036DD50, 64);
    *(u8 **)(sp + 0x150) = gEftStorm;
    scale = EftStage_GetTintScale() * 128.0f;
    func_00312680(sp + 0x90, sp + 0x90, 150.0f);
    func_00312680(sp + 0xA0, sp + 0xA0, 150.0f);
    func_00312680(sp + 0xB0, sp + 0xB0, 150.0f);
    func_00312680(sp + 0xC0, sp + 0xC0, 150.0f);
    sceVu0UnitMatrix(sp);
    if (gBtlCamView != NULL) {
        func_00312518(sp, gBtlCamView);
    }
    Vu0Screen_StoreMtx(sp + 0x40);
    sceVu0ApplyMatrix(sp + 0x90, sp, sp + 0x90);
    sceVu0ApplyMatrix(sp + 0xA0, sp, sp + 0xA0);
    sceVu0ApplyMatrix(sp + 0xB0, sp, sp + 0xB0);
    sceVu0ApplyMatrix(sp + 0xC0, sp, sp + 0xC0);
    *(s32 *)(sp + 0x154) = 3;
    fill = __fixunssfdi(scale);
    *(u64 *)(sp + 0x158) = fill | 0x3F80000000000000ULL | (fill << 16) | (fill << 8);

    count = *(s32 *)(sp + 0x154);
    do {
        if (*(s32 *)(e + 0x10) != 0 && *(s32 *)(e + 0x20) == 0) {
            div = *(s32 *)(e + 0x14);
            col = *(u64 *)(sp + 0x158) | ((u64)(s64)((*(s32 *)(e + 0x10) << 7) / div) << 24);
            p = (s32 *)(sp + 0x110);
            for (j = 0; j < 4; j++) {
                func_00312638(sp + 0xD0 + j * 16, sp + 0x90 + j * 16, e);
                func_00142608(p, sp + 0x40, sp + 0xD0 + j * 16);
                ok = 0;
                if (p[2] > 0 && p[0] <= 0xFFFF && p[0] > 0) {
                    if (p[1] <= 0xFFFF) {
                        ok = p[1] > 0;
                    }
                }
                if (!ok) break;
                p += 4;
            }
            if (j == 4) {
                tbl = *(u8 **)(sp + 0x150);
                pkt = D_00387AD8;
                if (*(s32 *)(e + 0x24) != 0) {
                    D_00387AD8 = pkt + 0xA0;
                    *(u64 *)(pkt + 0x00) = 0xA0000009ULL;
                    *(u64 *)(pkt + 0x10) = 0x1000000000008008ULL;
                    *(u64 *)(pkt + 0x18) = 0xE;
                    *(u64 *)(pkt + 0x20) = 0x5E;
                    *(u64 *)(pkt + 0x28) = 0;
                    *(u64 *)(pkt + 0x38) = 6;
                    *(u64 *)(pkt + 0x30) = *(u64 *)(tbl + *(s32 *)(e + 0x1C) * 16);
                    *(u64 *)(pkt + 0x48) = 1;
                    *(u64 *)(pkt + 0x40) = col;
                    *(u64 *)(pkt + 0x58) = 2;
                    *(u64 *)(pkt + 0x50) = (u64)*(u32 *)(sp + 0x80) | ((u64)*(u32 *)(sp + 0x84) << 32);
                    *(u64 *)(pkt + 0x68) = 4;
                    *(u64 *)(pkt + 0x70) = col;
                    *(u64 *)(pkt + 0x78) = 1;
                    *(u64 *)(pkt + 0x88) = 2;
                    *(u64 *)(pkt + 0x60) = (u64)(s64)*(s32 *)(sp + 0x130) |
                        ((u64)(s64)*(s32 *)(sp + 0x138) << 32 | (u64)(s64)*(s32 *)(sp + 0x134) << 16) | flag;
                    *(u64 *)(pkt + 0x80) = (u64)*(u32 *)(sp + 0x88) | ((u64)*(u32 *)(sp + 0x8C) << 32);
                    *(u64 *)(pkt + 0x98) = 4;
                    *(u64 *)(pkt + 0x90) = (u64)(s64)*(s32 *)(sp + 0x140) |
                        ((u64)(s64)*(s32 *)(sp + 0x148) << 32 | (u64)(s64)*(s32 *)(sp + 0x144) << 16) | flag;
                    OtInsert16(pkt, *(s32 *)(sp + 0x118) >> 8);
                } else {
                    D_00387AD8 = pkt + 0x110;
                    *(u64 *)(pkt + 0x20) = 0x5E;
                    *(u64 *)(pkt + 0x10) = 0x100000000000800FULL;
                    *(u64 *)(pkt + 0x18) = 0xE;
                    *(u64 *)(pkt + 0x00) = 0xA0000010ULL;
                    *(u64 *)(pkt + 0x28) = 0;
                    *(u64 *)(pkt + 0x38) = 6;
                    *(u64 *)(pkt + 0x30) = *(u64 *)(tbl + *(s32 *)(e + 0x18) * 16);
                    *(u64 *)(pkt + 0x48) = 1;
                    *(u64 *)(pkt + 0x40) = col;
                    *(u64 *)(pkt + 0x58) = 2;
                    *(u64 *)(pkt + 0x50) = (u64)*(u32 *)(sp + 0x80) | ((u64)*(u32 *)(sp + 0x84) << 32);
                    *(u64 *)(pkt + 0x68) = 4;
                    *(u64 *)(pkt + 0x78) = 1;
                    *(u64 *)(pkt + 0x70) = col;
                    *(u64 *)(pkt + 0x88) = 2;
                    *(u64 *)(pkt + 0x60) = (u64)(s64)*(s32 *)(sp + 0x110) |
                        ((u64)(s64)*(s32 *)(sp + 0x118) << 32 | (u64)(s64)*(s32 *)(sp + 0x114) << 16) | flag;
                    *(u64 *)(pkt + 0x80) = (u64)*(u32 *)(sp + 0x88) | ((u64)*(u32 *)(sp + 0x8C) << 32);
                    *(u64 *)(pkt + 0x98) = 4;
                    *(u64 *)(pkt + 0x90) = (u64)(s64)*(s32 *)(sp + 0x120) |
                        ((u64)(s64)*(s32 *)(sp + 0x118) << 32 | (u64)(s64)*(s32 *)(sp + 0x124) << 16) | flag;
                    *(u64 *)(pkt + 0xA8) = 6;
                    *(u64 *)(pkt + 0xA0) = *(u64 *)(tbl + *(s32 *)(e + 0x1C) * 16);
                    *(u64 *)(pkt + 0xB8) = 1;
                    *(u64 *)(pkt + 0xB0) = col;
                    *(u64 *)(pkt + 0xC8) = 2;
                    *(u64 *)(pkt + 0xC0) = (u64)*(u32 *)(sp + 0x80) | ((u64)*(u32 *)(sp + 0x84) << 32);
                    *(u64 *)(pkt + 0xD8) = 4;
                    *(u64 *)(pkt + 0xE0) = col;
                    *(u64 *)(pkt + 0xE8) = 1;
                    *(u64 *)(pkt + 0xF8) = 2;
                    *(u64 *)(pkt + 0xD0) = (u64)(s64)*(s32 *)(sp + 0x130) |
                        ((u64)(s64)*(s32 *)(sp + 0x138) << 32 | (u64)(s64)*(s32 *)(sp + 0x134) << 16) | flag;
                    *(u64 *)(pkt + 0x108) = 4;
                    *(u64 *)(pkt + 0xF0) = (u64)*(u32 *)(sp + 0x88) | ((u64)*(u32 *)(sp + 0x8C) << 32);
                    *(u64 *)(pkt + 0x100) = (u64)(s64)*(s32 *)(sp + 0x140) |
                        ((u64)(s64)*(s32 *)(sp + 0x148) << 32 | (u64)(s64)*(s32 *)(sp + 0x144) << 16) | flag;
                    OtInsert16(pkt, *(s32 *)(sp + 0x118) >> 8);
                }
            }
        }
        e += 0x30;
        count--;
    } while (count >= 0);
}
