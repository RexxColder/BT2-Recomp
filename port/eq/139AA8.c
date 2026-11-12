#include "common.h"
void bt2_fightlog_note(const char *fmt, ...); /* TEMP TEX0 */

extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern f32 D_003842F0;

extern void func_00129C28(void *dst, void *src);

/* float -> u32 style truncation used for the colour bytes (cvt.w.s with the 2^31 fix-up) */
static s32 f2u(f32 f) {
    if (f >= 2147483648.0f) {
        return (s32)(f - 2147483648.0f) | (s32)0x80000000;
    }
    return (s32)f;
}

/* Queues up to two textured triangles (GIF packets of 0x80 bytes): vertex colours come from c0/c1/c2, alpha of the
   second pass is scaled by fade[3], fade[7], fade[11]; screen vertices p0/p1/p2 are {s16 x, s16 y, s32 z}. */
void func_00139AA8(u8 *p0, u8 *p1, u8 *p2, u8 *c0, u8 *c1, u8 *c2, f32 *uv0, f32 *uv1,
                   f32 *uv2, s32 unused, s32 key, u64 *tex, f32 *fade, s32 count) {
    f32 col[24];
    f32 *c;
    u64 m = 0xFF000000FFFFFFFFull;
    s32 i;
    u8 *pkt;
    u8 *ent;
    u8 *prev;

    if (!(*(f32 *)(c0 + 0xC) > 0.0f) && !(*(f32 *)(c1 + 0xC) > 0.0f) && !(*(f32 *)(c2 + 0xC) > 0.0f)) {
        return;
    }
    if (fade[3] <= D_003842F0 && fade[7] <= D_003842F0 && fade[11] <= D_003842F0) {
        count = 1;
    }
    func_00129C28(&col[0], c0);
    func_00129C28(&col[4], c1);
    func_00129C28(&col[8], c2);
    func_00129C28(&col[12], c0);
    func_00129C28(&col[16], c1);
    func_00129C28(&col[20], c2);
    col[15] = col[15] * fade[3];
    col[19] = col[19] * fade[7];
    col[23] = col[23] * fade[11];

    if (count <= 0) {
        return;
    }
    c = col;
    for (i = 0; i < count; i++) {
        pkt = D_00387AD8;
        D_00387AD8 = pkt + 0x80;
        *(u64 *)(pkt + 0x18) = 0xF42142142160ull;
        *(u64 *)(pkt + 0x00) = 0xA0000007ull;
        *(u64 *)(pkt + 0x10) = 0xC400000000008001ull;
        *(u64 *)(pkt + 0x20) = 0x5B;
        pkt[0x30] = f2u(c[0]);
        pkt[0x31] = f2u(c[1]);
        pkt[0x32] = f2u(c[2]);
        pkt[0x33] = f2u(c[3]);
        *(f32 *)(pkt + 0x34) = uv0[2];
        pkt[0x48] = f2u(c[4]);
        pkt[0x49] = f2u(c[5]);
        pkt[0x4A] = f2u(c[6]);
        pkt[0x4B] = f2u(c[7]);
        *(f32 *)(pkt + 0x4C) = uv1[2];
        pkt[0x60] = f2u(c[8]);
        pkt[0x61] = f2u(c[9]);
        pkt[0x62] = f2u(c[10]);
        pkt[0x63] = f2u(c[11]);
        *(f32 *)(pkt + 0x64) = uv2[2];
        *(u64 *)(pkt + 0x28) = tex[i];
        if ((u32)(*(u64 *)(pkt + 0x28) >> 32) == 0 && (u32)*(u64 *)(pkt + 0x28) > 0xFFFFu) bt2_fightlog_note("TEX0TRUNC 139AA8 %llx", (unsigned long long)*(u64 *)(pkt + 0x28)); /* TEMP TEX0 */
        *(f32 *)(pkt + 0x38) = uv0[0];
        *(f32 *)(pkt + 0x3C) = uv0[1];
        *(f32 *)(pkt + 0x50) = uv1[0];
        *(f32 *)(pkt + 0x54) = uv1[1];
        *(f32 *)(pkt + 0x68) = uv2[0];
        *(f32 *)(pkt + 0x6C) = uv2[1];
        *(u16 *)(pkt + 0x40) = *(u16 *)p0;
        *(u16 *)(pkt + 0x42) = *(u16 *)(p0 + 4);
        *(u64 *)(pkt + 0x40) = (*(u64 *)(pkt + 0x40) & m) | ((u64)(*(s32 *)(p0 + 8) & 0xFFFFFF) << 32);
        pkt[0x47] = 0xFF;
        *(u16 *)(pkt + 0x58) = *(u16 *)p1;
        *(u16 *)(pkt + 0x5A) = *(u16 *)(p1 + 4);
        *(u64 *)(pkt + 0x58) = (*(u64 *)(pkt + 0x58) & m) | ((u64)(*(s32 *)(p1 + 8) & 0xFFFFFF) << 32);
        pkt[0x5F] = 0xFF;
        *(u16 *)(pkt + 0x70) = *(u16 *)p2;
        *(u16 *)(pkt + 0x72) = *(u16 *)(p2 + 4);
        *(u64 *)(pkt + 0x70) = (*(u64 *)(pkt + 0x70) & m) | ((u64)(*(s32 *)(p2 + 8) & 0xFFFFFF) << 32);
        pkt[0x77] = 0xFF;

        if (key < 0) {
            ent = D_00387AE0 + (i << 3);
        } else if (key < 0x1000) {
            ent = D_00387AE0 + ((key * 2 + i) << 3);
        } else {
            ent = D_00387AE0 + (i << 3) + 0xFFF0;
        }
        prev = *(u8 **)(ent + 4);
        *(u8 **)(prev + 4) = pkt;
        *(u8 **)(ent + 4) = pkt;
        c += 12;
    }
}
