#include "common.h"

extern void func_00129C28(void *dst, void *src);
extern void Vec4_Set(void *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec3_Sub(void *dst, void *a, void *b);
extern void Vec3_Add(void *dst, void *a, void *b);
extern void Vec3_Cross(void *dst, void *a, void *b);
extern void Vec3_Normalize(void *dst, void *src);
extern void func_00129BD0(void *dst, void *src, f32 scale);
extern s32 func_001294B0(void *out, void *in, s32 n, s32 flag);
extern void func_00129D40(void *dst, void *src);

extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
void bt2_fightlog_note(const char *fmt, ...);

/* Links pkt into the ordering table slot chosen by z and ot (8 byte slot stride). */
static void OtInsert(u8 *pkt, s32 z, u32 ot) {
    u8 *slot;
    u8 *node;

    if (z < 0) {
        slot = D_00387AE0 + ot * 8;
    } else if (z < 0x1000) {
        slot = D_00387AE0 + (z * 2 + ot) * 8;
    } else {
        slot = D_00387AE0 + ot * 8 + 0xFFF0;
    }
    node = *(u8 **)(slot + 4);
    *(u8 **)(node + 4) = pkt;
    *(u8 **)(slot + 4) = pkt;
}

/* Sibling of 193470 for a list with next at +0x120 (pos +0x80, axis +0x90, color +0xA0, uv origin +0xD0, ot +5, flag opt+5, ctrl+0x70/0x74 uv step). */
void func_001BAD80(u8 *ctrl, s32 unused, u8 *opt) {
    u8 sp[0x1C0];
    u8 *node;
    u8 *pkt;
    s32 i;
    s32 z;

    func_00129C28(sp + 0x40, gBtlCamView + 0x1F0);
    for (i = 0; i < 4; i++) {
        *(f32 *)(sp + 0x68 + i * 16) = 1.0f;
        *(s32 *)(sp + 0x6C + i * 16) = 0;
        Vec4_Set(sp + i * 16, 0.0f, 0.0f, 0.0f, 1.0f);
    }

    node = *(u8 **)ctrl;
    while (node != NULL) {
        Vec3_Sub(sp + 0x50, node + 0x80, sp + 0x40);
        Vec3_Cross(sp + 0x50, node + 0x90, sp + 0x50);
        Vec3_Normalize(sp + 0x50, sp + 0x50);
        func_00129BD0(sp + 0xE0, sp + 0x50, *(f32 *)(node + 0x3C));
        Vec3_Add(sp + 0x00, node + 0x80, sp + 0xE0);
        Vec3_Sub(sp + 0x10, node + 0x80, sp + 0xE0);
        if (opt[5] == 0) {
            func_00129BD0(sp + 0xF0, node + 0x90, *(f32 *)(node + 0x34));
            Vec3_Add(sp + 0x20, sp + 0x00, sp + 0xF0);
            Vec3_Add(sp + 0x30, sp + 0x10, sp + 0xF0);
        } else {
            func_00129BD0(sp + 0xF0, node + 0x90, *(f32 *)(node + 0x34) * 0.5f);
            Vec3_Add(sp + 0x20, sp + 0x00, sp + 0xF0);
            Vec3_Add(sp + 0x30, sp + 0x10, sp + 0xF0);
            Vec3_Sub(sp + 0x00, sp + 0x00, sp + 0xF0);
            Vec3_Sub(sp + 0x10, sp + 0x10, sp + 0xF0);
        }

        if (func_001294B0(sp + 0x100, sp, 4, 1) != 0) {
            pkt = D_00387AD8;
            D_00387AD8 = pkt + 0x90;
            if (pkt == NULL) return;
            *(u64 *)(pkt + 0x00) = 0xA0000008ULL;
            *(u64 *)(pkt + 0x20) = 0x5C;
            *(u64 *)(pkt + 0x10) = 0xE400000000008001ULL;
            *(u64 *)(pkt + 0x18) = 0x42142142142160ULL;

            for (i = 0; i < 4; i++) {
                f32 fu = (f32)(i % 2) * *(f32 *)(ctrl + 0x70);
                f32 fv = (f32)(i / 2) * *(f32 *)(ctrl + 0x74);
                *(f32 *)(sp + 0x60 + i * 16) = fu + *(f32 *)(node + 0xD0);
                *(f32 *)(sp + 0x64 + i * 16) = fv + *(f32 *)(node + 0xD8);
                func_00129BD0(sp + 0xA0 + i * 16, sp + 0x60 + i * 16, 1.0f / (f32)*(s32 *)(sp + 0x10C + i * 16));
            }
            func_00129D40(sp + 0x140, node + 0xA0);
            { static int k; if ((k++ % 500) == 0) bt2_fightlog_note("PTCL-QUAD nodo rgba %g %g %g %g -> int %d %d %d %d", /* TEMP */
                *(f32 *)(node + 0xA0), *(f32 *)(node + 0xA4), *(f32 *)(node + 0xA8), *(f32 *)(node + 0xAC),
                *(s32 *)(sp + 0x140), *(s32 *)(sp + 0x144), *(s32 *)(sp + 0x148), *(s32 *)(sp + 0x14C)); }
            z = ((*(s32 *)(sp + 0x108) + *(s32 *)(sp + 0x138)) + (*(s32 *)(sp + 0x128) + *(s32 *)(sp + 0x118))) >> 10;
            if ((*(u32 *)(ctrl + 0x60) & 0x20) != 0) {
                for (i = 3; i >= 0; i--) {
                    *(s32 *)(sp + 0x108 + i * 16) = 0xFFFFFF;
                }
            }

            *(u8 *)(pkt + 0x30) = sp[0x140];
            *(u8 *)(pkt + 0x31) = sp[0x144];
            *(u8 *)(pkt + 0x32) = sp[0x148];
            *(u8 *)(pkt + 0x33) = sp[0x14C];
            *(f32 *)(pkt + 0x34) = *(f32 *)(sp + 0xA8);
            *(u8 *)(pkt + 0x48) = sp[0x140];
            *(u8 *)(pkt + 0x49) = sp[0x144];
            *(u8 *)(pkt + 0x4A) = sp[0x148];
            *(u8 *)(pkt + 0x4B) = sp[0x14C];
            *(f32 *)(pkt + 0x4C) = *(f32 *)(sp + 0xB8);
            *(u8 *)(pkt + 0x60) = sp[0x140];
            *(u8 *)(pkt + 0x61) = sp[0x144];
            *(u8 *)(pkt + 0x62) = sp[0x148];
            *(u8 *)(pkt + 0x63) = sp[0x14C];
            *(f32 *)(pkt + 0x64) = *(f32 *)(sp + 0xC8);
            *(u8 *)(pkt + 0x78) = sp[0x140];
            *(u8 *)(pkt + 0x79) = sp[0x144];
            *(u8 *)(pkt + 0x7A) = sp[0x148];
            *(u8 *)(pkt + 0x7B) = sp[0x14C];
            *(f32 *)(pkt + 0x7C) = *(f32 *)(sp + 0xD8);
            *(f32 *)(pkt + 0x38) = *(f32 *)(sp + 0xA0);
            *(f32 *)(pkt + 0x3C) = *(f32 *)(sp + 0xA4);
            *(f32 *)(pkt + 0x50) = *(f32 *)(sp + 0xB0);
            *(f32 *)(pkt + 0x54) = *(f32 *)(sp + 0xB4);
            *(f32 *)(pkt + 0x68) = *(f32 *)(sp + 0xC0);
            *(f32 *)(pkt + 0x6C) = *(f32 *)(sp + 0xC4);
            *(f32 *)(pkt + 0x80) = *(f32 *)(sp + 0xD0);
            *(f32 *)(pkt + 0x84) = *(f32 *)(sp + 0xD4);

            for (i = 0; i < 4; i++) {
                u8 *q = pkt + 0x40 + i * 0x18;
                u8 *src = sp + 0x100 + i * 0x10;
                u64 old;
                *(u16 *)(q + 0) = *(u16 *)(src + 0);
                *(u16 *)(q + 2) = *(u16 *)(src + 4);
                old = *(u64 *)q;
                old = (old & 0xFF000000FFFFFFFFULL) | ((u64)(*(u32 *)(src + 8) & 0xFFFFFF) << 32);
                *(u64 *)q = old;
                *(u8 *)(q + 7) = 0xFF;
            }
            *(u64 *)(pkt + 0x28) = *(u64 *)(ctrl + 0x280);
            OtInsert(pkt, z, node[5]);
        }
        node = *(u8 **)(node + 0x120);
    }
}
