#include "common.h"
void bt2_fightlog_note(const char *fmt, ...); /* TEMP TEX0 */

u8 *func_0012B9B0(void);
s32 func_0012BB50(u8 *arg0, s32 arg1, u8 *arg2);
void func_003126C8(void *dst, void *src);
void func_0012D868(void *out, s32 mode, void *in, s32 count, void *outf, void *uv);
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

/* Appends the packet to the ordering-table list `slot` (tail pointer at +4). */
#define LINK(slot, pkt) \
    do { \
        u8 *tail_ = *(u8 **)((slot) + 4); \
        *(u8 **)(tail_ + 4) = (pkt); \
        *(u8 **)((slot) + 4) = (pkt); \
    } while (0)

/* cvt.w.s with the 2^31 split the original does: low byte of the colour component */
#define COLB(f) ((f) >= 2147483648.0f ? (u8)((s32)((f) - 2147483648.0f) | 0x80000000) : (u8)(s32)(f))

s32 func_001E5570(u8 *poly, s32 mode, u64 tag, s32 kind, s32 key, u32 force_far) {
    s32 scr[9][4];
    f32 in_[9][4];
    f32 col[9][4];
    f32 uv[9][4];
    f32 outf[9][4];
    s32 count;
    s32 i, k, pass;
    s32 saved_kind;
    u8 *planes;
    u8 *pkt;
    u8 *slot;
    s32 hdr;
    u8 *c;

    force_far &= 0xFF;
    planes = func_0012B9B0();
    saved_kind = kind;
    count = 3;
    for (pass = 4; pass >= 0; ) {
        pass--;
        count = func_0012BB50(planes, count, poly);
        planes += 16;
    }
    if (count == 0) {
        return 0;
    }
    for (i = 0; i < count; i++) {
        func_003126C8(in_[i], poly + i * 16);
        func_003126C8(col[i], poly + i * 16 + 0x120);
        func_003126C8(uv[i], poly + i * 16 + 0x90);
        in_[i][3] = 1.0f;
        uv[i][2] = 1.0f;
        uv[i][3] = 0.0f;
    }
    func_0012D868(scr, mode, in_, count, outf, uv);
    for (i = 2; i < count; i++) {
        if (scr[0][2] > 0xFFFFFF) {
            scr[0][2] = 0xFFFFFF;
        }
        if (scr[i - 1][2] > 0xFFFFFF) {
            scr[i - 1][2] = 0xFFFFFF;
        }
        if (scr[i][2] > 0xFFFFFF) {
            scr[i][2] = 0xFFFFFF;
        }
        if (force_far != 0) {
            scr[0][2] = 0xFFFFFF;
            scr[i - 1][2] = 0xFFFFFF;
            scr[i][2] = 0xFFFFFF;
        }
        hdr = 0;
        if (kind == 2 || kind == 3) {
            pkt = D_00387AD8;
            kind = 1;
            hdr = 1;
            D_00387AD8 = pkt + 0x30;
            *(u64 *)(pkt + 0x00) = 0xA0000002ULL;
            *(u64 *)(pkt + 0x10) = 0x1000000000008001ULL;
            *(u64 *)(pkt + 0x20) = (saved_kind == 2) ? 0x42 : 0x49;
            *(u64 *)(pkt + 0x18) = 0xE;
            *(u64 *)(pkt + 0x28) = 0x42;
            if (key < 0) {
                slot = D_00387AE0 + 8;
            } else if (key < 0x1000) {
                slot = D_00387AE0 + (key * 2 + 1) * 8;
            } else {
                slot = D_00387AE0 + 0xFFF8;
            }
            LINK(slot, pkt);
        }
        pkt = D_00387AD8;
        D_00387AD8 = pkt + 0x80;
        *(u64 *)(pkt + 0x18) = 0xF42142142160ULL;
        *(u64 *)(pkt + 0x20) = 0x5B;
        *(u64 *)(pkt + 0x00) = 0xA0000007ULL;
        *(u64 *)(pkt + 0x10) = 0xC400000000008001ULL;
        c = poly + 0x120;
        pkt[0x30] = COLB(*(f32 *)(c + 0));
        pkt[0x31] = COLB(*(f32 *)(c + 4));
        pkt[0x32] = COLB(*(f32 *)(c + 8));
        pkt[0x33] = COLB(*(f32 *)(c + 12));
        *(f32 *)(pkt + 0x34) = outf[0][2];
        c = poly + 0x120 + (i - 1) * 16;
        pkt[0x48] = COLB(*(f32 *)(c + 0));
        pkt[0x49] = COLB(*(f32 *)(c + 4));
        pkt[0x4A] = COLB(*(f32 *)(c + 8));
        pkt[0x4B] = COLB(*(f32 *)(c + 12));
        *(f32 *)(pkt + 0x4C) = outf[i - 1][2];
        c = poly + 0x120 + i * 16;
        pkt[0x60] = COLB(*(f32 *)(c + 0));
        pkt[0x61] = COLB(*(f32 *)(c + 4));
        pkt[0x62] = COLB(*(f32 *)(c + 8));
        pkt[0x63] = COLB(*(f32 *)(c + 12));
        *(f32 *)(pkt + 0x64) = outf[i][2];
        *(u16 *)(pkt + 0x40) = *(u16 *)&scr[0][0];
        *(u16 *)(pkt + 0x42) = *(u16 *)&scr[0][1];
        *(u64 *)(pkt + 0x40) = (*(u64 *)(pkt + 0x40) & 0xFF000000FFFFFFFFULL) | ((u64)((u32)scr[0][2] & 0xFFFFFF) << 32);
        pkt[0x47] = 0xFF;
        *(u16 *)(pkt + 0x58) = *(u16 *)&scr[i - 1][0];
        *(u16 *)(pkt + 0x5A) = *(u16 *)&scr[i - 1][1];
        *(u64 *)(pkt + 0x58) = (*(u64 *)(pkt + 0x58) & 0xFF000000FFFFFFFFULL) | ((u64)((u32)scr[i - 1][2] & 0xFFFFFF) << 32);
        pkt[0x5F] = 0xFF;
        *(u16 *)(pkt + 0x70) = *(u16 *)&scr[i][0];
        *(u16 *)(pkt + 0x72) = *(u16 *)&scr[i][1];
        *(u64 *)(pkt + 0x70) = (*(u64 *)(pkt + 0x70) & 0xFF000000FFFFFFFFULL) | ((u64)((u32)scr[i][2] & 0xFFFFFF) << 32);
        pkt[0x77] = 0xFF;
        *(f32 *)(pkt + 0x38) = outf[0][0];
        *(f32 *)(pkt + 0x3C) = outf[0][1];
        *(f32 *)(pkt + 0x50) = outf[i - 1][0];
        *(f32 *)(pkt + 0x54) = outf[i - 1][1];
        *(f32 *)(pkt + 0x68) = outf[i][0];
        *(f32 *)(pkt + 0x6C) = outf[i][1];
        *(u64 *)(pkt + 0x28) = tag;
        if ((u32)(*(u64 *)(pkt + 0x28) >> 32) == 0 && (u32)*(u64 *)(pkt + 0x28) > 0xFFFFu) bt2_fightlog_note("TEX0TRUNC 1E5570 %llx ret %p", (unsigned long long)*(u64 *)(pkt + 0x28), __builtin_return_address(0)); /* TEMP TEX0 */
        if (key < 0) {
            slot = D_00387AE0 + kind * 8;
        } else if (key < 0x1000) {
            slot = D_00387AE0 + (key * 2 + kind) * 8;
        } else {
            slot = D_00387AE0 + kind * 8 + 0xFFF0;
        }
        LINK(slot, pkt);
        if (hdr) {
            pkt = D_00387AD8;
            D_00387AD8 = pkt + 0x30;
            *(u64 *)(pkt + 0x20) = 0x48;
            *(u64 *)(pkt + 0x00) = 0xA0000002ULL;
            *(u64 *)(pkt + 0x10) = 0x1000000000008001ULL;
            *(u64 *)(pkt + 0x18) = 0xE;
            *(u64 *)(pkt + 0x28) = 0x42;
            if (key < 0) {
                slot = D_00387AE0 + 8;
            } else if (key < 0x1000) {
                slot = D_00387AE0 + (key * 2 + 1) * 8;
            } else {
                slot = D_00387AE0 + 0xFFF8;
            }
            kind = saved_kind;
            LINK(slot, pkt);
        }
    }
    return 0;
}
