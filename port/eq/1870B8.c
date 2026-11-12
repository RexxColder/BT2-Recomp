#include "common.h"

extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

/* Builds a GIF quad packet (plus one or two 0x30-byte state packets depending on mode) and links them
   into the ordering table at D_00387AE0. Returns the table entry it displaced. */
s32 func_001870B8(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3,
                  f32 fA, f32 fB, f32 fC, f32 fD,
                  s32 h0, s32 h1, s32 h2, s32 h3, s32 sortKey, s64 pad5, s64 pad6,
                  s32 shift, s32 mode, u64 extra) {
    u8 *pkt;
    u8 *st;
    u8 *ent;
    u8 *ret;
    s32 keyHi = (sortKey >> 8) << 8;
    s32 key = keyHi >> 8;
    u64 keyBits = (u64)(keyHi & 0xFFFFFF) << 32;
    s32 layer = mode;
    s32 extraPkt = 0;
    u64 m = 0xFF000000FFFFFFFFull;

    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x80;

    *(u16 *)(pkt + 0x40) = t0;
    *(u16 *)(pkt + 0x42) = t1;
    *(u64 *)(pkt + 0x40) = (*(u64 *)(pkt + 0x40) & m) | keyBits;
    *(u64 *)(pkt + 0x28) = extra;
    *(u64 *)(pkt + 0x20) = ((u64)((s64)(s8)shift << 9)) | 0x54;
    *(u64 *)(pkt + 0x00) = 0xA0000007ull;
    *(u64 *)(pkt + 0x10) = 0xC400000000008001ull;
    pkt[0x30] = a0;
    pkt[0x31] = a1;
    *(u64 *)(pkt + 0x18) = (u64)(s64)((s32)(s8)shift * 16) + 0xF42424242160ull;
    pkt[0x32] = a2;
    pkt[0x33] = a3;
    *(f32 *)(pkt + 0x34) = 1.0f;
    *(f32 *)(pkt + 0x48) = fA;
    *(f32 *)(pkt + 0x5C) = fB;
    *(u16 *)(pkt + 0x50) = t2;
    *(u16 *)(pkt + 0x52) = t3;
    *(u16 *)(pkt + 0x60) = h0;
    *(u16 *)(pkt + 0x62) = h1;
    *(u16 *)(pkt + 0x70) = h2;
    *(u16 *)(pkt + 0x72) = h3;
    *(u64 *)(pkt + 0x50) = (*(u64 *)(pkt + 0x50) & m) | keyBits;
    *(u64 *)(pkt + 0x70) = (*(u64 *)(pkt + 0x70) & m) | keyBits;
    *(u64 *)(pkt + 0x60) = (*(u64 *)(pkt + 0x60) & m) | keyBits;
    *(f32 *)(pkt + 0x68) = fC;
    *(f32 *)(pkt + 0x6C) = fD;
    *(f32 *)(pkt + 0x38) = fA;
    *(f32 *)(pkt + 0x3C) = fB;
    *(f32 *)(pkt + 0x4C) = fD;
    *(f32 *)(pkt + 0x58) = fC;
    pkt[0x47] = 0xFF;
    pkt[0x77] = 0xFF;
    pkt[0x57] = 0xFF;
    pkt[0x67] = 0xFF;

    st = D_00387AD8;
    D_00387AD8 = st + 0x30;
    *(u64 *)(st + 0x00) = 0xA0000002ull;
    *(u64 *)(st + 0x10) = 0x1000000000008001ull;
    *(u64 *)(st + 0x18) = 0xE;
    *(u64 *)(st + 0x28) = 0x42;
    if (mode == 2) {
        *(u64 *)(st + 0x20) = 0x42;
        layer = 1;
        extraPkt = 1;
    } else if (mode == 3) {
        *(u64 *)(st + 0x20) = 0x49;
        layer = 1;
        extraPkt = 1;
    }
    if (extraPkt != 0) {
        if (key < 0) {
            ent = D_00387AE0 + 8;
        } else if (key < 0x1000) {
            ent = D_00387AE0 + (key * 16 + 8);
        } else {
            ent = D_00387AE0 + 0xFFF8;
        }
        ret = *(u8 **)(ent + 4);
        *(u8 **)(ret + 4) = st;
        *(u8 **)(ent + 4) = st;
    }

    if (key < 0) {
        ent = D_00387AE0 + (layer << 3);
    } else if (key < 0x1000) {
        ent = D_00387AE0 + ((2 * key + layer) << 3);
    } else {
        ent = D_00387AE0 + (layer << 3) + 0xFFF0;
    }
    ret = *(u8 **)(ent + 4);
    *(u8 **)(ret + 4) = pkt;
    *(u8 **)(ent + 4) = pkt;
    if (extraPkt == 0) {
        return (s32)ret;
    }

    st = D_00387AD8;
    D_00387AD8 = st + 0x30;
    *(u64 *)(st + 0x00) = 0xA0000002ull;
    *(u64 *)(st + 0x10) = 0x1000000000008001ull;
    *(u64 *)(st + 0x18) = 0xE;
    *(u64 *)(st + 0x28) = 0x42;
    *(u64 *)(st + 0x20) = 0x48;
    if (key < 0) {
        ent = D_00387AE0 + 8;
    } else if (key < 0x1000) {
        ent = D_00387AE0 + (key * 16 + 8);
    } else {
        ent = D_00387AE0 + 0xFFF8;
    }
    ret = *(u8 **)(ent + 4);
    *(u8 **)(ret + 4) = st;
    *(u8 **)(ent + 4) = st;
    return (s32)ret;
}
