#include "common.h"
void bt2_fightlog_note(const char *fmt, ...); /* TEMP TEX0 */

extern f32 D_003842F4;

void func_00129D40(s32 *dst, f32 *src);
u8 *Dma_BeginDirect(void);
void Dma_EndDirect(u8 *end);

/* Queues `count` gouraud triangles directly into the DMA stream: vertex positions xyz0..2 (x,y u16 at +0/+4, z 24 bit
 * at +8), colours rgba0..2 converted to ints (the last three scaled by the fog w factors), st0..2, one texture per pass. */
void func_0013A070(u16 *xyz0, u16 *xyz1, u16 *xyz2, f32 *rgba0, f32 *rgba1, f32 *rgba2,
                   f32 *st0, f32 *st1, f32 *st2, s32 alphaMode, u64 *tex, f32 *fog, s32 count) {
    u64 texCopy[2];
    s32 col[24];
    s32 layer = 1;
    s32 i;
    u8 *pkt;
    s32 *c;
    u64 keep = 0xFF000000FFFFFFFFULL;

    if (!(rgba0[3] > 0.0f) && !(rgba1[3] > 0.0f) && !(rgba2[3] > 0.0f)) {
        return;
    }
    if (fog[3] <= D_003842F4 && fog[7] <= D_003842F4 && fog[11] <= D_003842F4) {
        count = 1;
    }
    texCopy[0] = tex[0];
    texCopy[1] = tex[1];
    if (alphaMode < 0) {
        layer = 0;
    }
    func_00129D40(&col[0], rgba0);
    func_00129D40(&col[4], rgba1);
    func_00129D40(&col[8], rgba2);
    func_00129D40(&col[12], rgba0);
    func_00129D40(&col[16], rgba1);
    func_00129D40(&col[20], rgba2);
    col[19] = (s32)((f32)col[19] * fog[7]);
    col[23] = (s32)((f32)col[23] * fog[11]);
    col[15] = (s32)((f32)col[15] * fog[3]);
    if (count <= 0) {
        return;
    }
    c = &col[0];
    i = 0;
    do {
        pkt = Dma_BeginDirect();
        *(u64 *)(pkt + 0x00) = 0xC400000000008001ULL;
        *(u64 *)(pkt + 0x10) = ((s64)layer << 6) | ((s64)(s8)i << 9) | 0x1B;
        *(u64 *)(pkt + 0x08) = (s64)((s32)(s8)i << 4) + 0xF42142142160LL;
        i++;
        pkt[0x20] = (u8)c[0];
        pkt[0x21] = (u8)c[1];
        pkt[0x22] = (u8)c[2];
        pkt[0x23] = (u8)c[3];
        *(f32 *)(pkt + 0x24) = st0[2];
        pkt[0x38] = (u8)c[4];
        pkt[0x39] = (u8)c[5];
        pkt[0x3A] = (u8)c[6];
        pkt[0x3B] = (u8)c[7];
        *(f32 *)(pkt + 0x3C) = st1[2];
        pkt[0x50] = (u8)c[8];
        pkt[0x51] = (u8)c[9];
        pkt[0x52] = (u8)c[10];
        pkt[0x53] = (u8)c[11];
        c += 12;
        *(f32 *)(pkt + 0x54) = st2[2];
        *(u64 *)(pkt + 0x18) = texCopy[i - 1];
        if ((u32)(*(u64 *)(pkt + 0x18) >> 32) == 0 && (u32)*(u64 *)(pkt + 0x18) > 0xFFFFu) bt2_fightlog_note("TEX0TRUNC 13A070 %llx ret %p", (unsigned long long)*(u64 *)(pkt + 0x18), __builtin_return_address(0)); /* TEMP TEX0 */
        *(f32 *)(pkt + 0x28) = st0[0];
        *(f32 *)(pkt + 0x2C) = st0[1];
        *(f32 *)(pkt + 0x40) = st1[0];
        *(f32 *)(pkt + 0x44) = st1[1];
        *(f32 *)(pkt + 0x58) = st2[0];
        *(f32 *)(pkt + 0x5C) = st2[1];
        *(u16 *)(pkt + 0x30) = xyz0[0];
        *(u16 *)(pkt + 0x32) = xyz0[2];
        *(u64 *)(pkt + 0x30) = (*(u64 *)(pkt + 0x30) & keep) | ((u64)(*(u32 *)(xyz0 + 4) & 0xFFFFFF) << 32);
        pkt[0x37] = 0xFF;
        *(u16 *)(pkt + 0x48) = xyz1[0];
        *(u16 *)(pkt + 0x4A) = xyz1[2];
        *(u64 *)(pkt + 0x48) = (*(u64 *)(pkt + 0x48) & keep) | ((u64)(*(u32 *)(xyz1 + 4) & 0xFFFFFF) << 32);
        pkt[0x4F] = 0xFF;
        *(u16 *)(pkt + 0x60) = xyz2[0];
        *(u16 *)(pkt + 0x62) = xyz2[2];
        *(u64 *)(pkt + 0x60) = (*(u64 *)(pkt + 0x60) & keep) | ((u64)(*(u32 *)(xyz2 + 4) & 0xFFFFFF) << 32);
        pkt[0x67] = 0xFF;
        Dma_EndDirect(pkt + 0x70);
    } while (i < count);
}
