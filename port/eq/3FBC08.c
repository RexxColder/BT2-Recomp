#include "common.h"

extern u8 *D_0042A588 __attribute__((section(".data")));  /* G: stage/result menu state (620 bytes) */
extern u8 *D_0042139C __attribute__((section(".data")));  /* table of resource offsets */
extern u8 *D_003876A0 __attribute__((section(".data")));  /* game save data */
extern u8 *D_003876A4 __attribute__((section(".data")));  /* player data */

extern s32 GetTimerSystemTime();
extern s32 Res_RelocateOffsets();
extern s32 func_003FB7B0();
extern s32 func_003FB830();
extern s32 func_003FBB08();
extern void func_0026E7F0();
extern s32 func_0026EAE0();
extern u8 *func_0028BAA8();
extern void func_0029BB88();
extern u8 *func_002B24C8();
extern s32 func_00325370();
extern s32 rand();

#define G (D_0042A588)
#define P (D_003876A4)
#define SAVE (D_003876A0)
#define GW(off) (*(s32 *)(G + (off)))
#define PH(off) (*(u16 *)(P + (off)))
#define PS(off) (*(s16 *)(P + (off)))
#define REC(off) (SAVE + 1152 + (off))      /* current play record inside the save data */
#define REC_FLAGS (*(u64 *)(SAVE + 1160))

/* Address of the sub-block whose (word-aligned) offset is stored at hdr + off. */
static u8 *HdrPtr(u8 *hdr, s32 off) {
    return hdr + ((*(u32 *)(hdr + off) >> 2) << 2);
}

/* Same, then relocate the block in place; returns the relocated block pointer. */
static u8 *Section(u8 *hdr, s32 off) {
    u8 *blk = HdrPtr(hdr, off);
    Res_RelocateOffsets(&blk, blk, blk);
    return blk;
}

/* 0x003FBC08: load the result-screen resources of table entry arg0 and build the result data. */
s32 func_003FBC08(s32 arg0) {
    u8 *hdr;
    u8 *blk;
    s32 i;
    s32 count;

    G = func_0028BAA8(620);
    __builtin_memset(G, 0, 620);
    *(u8 **)G = D_0042139C + ((*(u32 *)(D_0042139C + arg0 * 4) >> 2) << 2);
    GW(4) = (s32)func_002B24C8(*(u8 **)G, 0, 0);
    func_00325370(GetTimerSystemTime());
    hdr = (u8 *)GW(4);

    GW(0x88) = (s32)Section(hdr, 60);

    blk = Section(hdr, 12);
    GW(0xAC) = *(s32 *)(blk + 16);
    GW(0xA4) = *(s32 *)(blk + 16) + 64;
    GW(0xD4) = *(s32 *)(blk + 16) + 128;

    blk = Section(hdr, 16);
    GW(0xD0) = *(s32 *)(blk + 16);

    blk = Section(hdr, 20);
    GW(0xB0) = *(s32 *)(blk + 16);

    blk = Section(hdr, 24);
    GW(0xCC) = *(s32 *)(blk + 16);

    blk = Section(hdr, 32);
    GW(0xD8) = *(s32 *)(blk + 16);

    blk = Section(hdr, 36);
    GW(0x90) = *(s32 *)(blk + 16);
    GW(0x8C) = *(s32 *)(blk + 16) + 64;

    blk = Section(hdr, 40);
    GW(0xA8) = *(s32 *)(blk + 16);
    GW(0xB4) = *(s32 *)(blk + 16) + 64;
    GW(0xB8) = *(s32 *)(blk + 16) + 128;
    GW(0xC8) = *(s32 *)(blk + 16) + 192;

    blk = Section(hdr, 44);
    GW(0x98) = *(s32 *)(blk + 16);
    GW(0xC0) = *(s32 *)(blk + 16) + 64;

    blk = Section(hdr, 52);
    GW(0x9C) = *(s32 *)(blk + 16);
    GW(0xBC) = *(s32 *)(blk + 16) + 64;

    blk = Section(hdr, 56);
    GW(0x94) = *(s32 *)(blk + 16);

    blk = Section(hdr, 48);
    GW(0xC4) = *(s32 *)(blk + 16);
    GW(0xA0) = *(s32 *)(blk + 16) + 64;

    func_0026E7F0(G + 96, HdrPtr(hdr, 8), G + 140);
    func_0026EAE0(G + 96, 60);

    blk = Section(hdr, 68);
    GW(0xE8) = *(s32 *)(blk + 16);
    GW(0xE4) = *(s32 *)(blk + 16) + 64;

    blk = Section(hdr, 72);
    GW(0xEC) = *(s32 *)(blk + 16);

    func_0026E7F0(G + 16, HdrPtr(hdr, 64), G + 228);
    func_0026EAE0(G + 16, 60);

    blk = Section(hdr, 28);
    GW(0xF4) = *(s32 *)(blk + 16);
    GW(0xF8) = *(s32 *)(blk + 16);

    func_0026E7F0(G + 56, HdrPtr(hdr, 160), G + 244);
    func_0026EAE0(G + 56, 60);

    GW(8) = (s32)HdrPtr(hdr, 80);
    GW(0xC) = (s32)HdrPtr(hdr, 76);
    GW(0x268) = (s32)HdrPtr(hdr, 84);
    GW(0x24C) = (s32)HdrPtr(hdr, 112) + 4;
    GW(0x250) = (s32)HdrPtr(hdr, 116) + 4;
    GW(0x260) = (s32)HdrPtr(hdr, 168) + 4;
    GW(0x25C) = (s32)HdrPtr(hdr, 4) + 4;
    GW(0x254) = (s32)HdrPtr(hdr, 152) + 4;
    GW(0x258) = (s32)HdrPtr(hdr, 156) + 4;
    GW(0x264) = (s32)HdrPtr(hdr, 172) + 4;
    func_0029BB88(HdrPtr(hdr, 88), GW(0xC));
    GW(0x248) = -1;

    *(u32 *)(P + 64) &= ~0x20000u;

    if ((*(u32 *)REC(0) & 1) == 0) {
        /* no record yet: defaults */
        GW(0x124) = 0;
        GW(0x128) = 0;
        GW(0x12C) = 0;
        GW(0x130) = 0;
        for (i = 0; i < 5; i++) {
            GW(0x13C + i * 4) = 5;
            GW(0x154 + i * 4) = 0;
            GW(0x16C + i * 4) = 0;
        }
        GW(0x168) = 0;
        GW(0x180) = 0;
        GW(0x118) = 3;
        GW(0x104) = rand() % 3 + 34;
        GW(0xFC) |= 0x100;
        return GW(0xFC);
    }

    /* add the record's play time (ms, s, m, h) to the player's clock */
    PH(126) += *(u16 *)REC(66);
    if (PS(126) >= 1000) {
        PH(126) -= 1000;
        PH(124)++;
    }
    PH(124) += *(u16 *)REC(64);
    if (PS(124) >= 60) {
        PH(124) -= 60;
        PH(122)++;
    }
    PH(122) += *(u16 *)REC(62);
    if (PS(122) >= 60) {
        PH(122) -= 60;
        PH(120)++;
    }
    PH(120) += *(u16 *)REC(60);
    if (PS(120) >= 10) {
        PH(120) = 9;
    }

    GW(0x124) = (s32)*(f32 *)REC(48);
    if (GW(0x124) <= 0) {
        GW(0x124) = 1;
    }
    GW(0x128) = *(s16 *)REC(60) * 3600 + *(s16 *)REC(62) * 60 + *(s16 *)REC(64);
    GW(0x12C) = *(s32 *)REC(40);
    GW(0x130) = *(s32 *)REC(24);

    for (i = 0; i < 5; i++) {
        GW(0x13C + i * 4) = func_003FB830(i);
        GW(0x154 + i * 4) = func_003FBB08(GW(0x13C + i * 4)) * 100;
    }

    if (*(u32 *)(SAVE + 1160) & 1) {
        *(u32 *)(P + 64) |= 0x20000;
    }
    if (*(s32 *)(P + 104) == 1) {
        if (!(*(s32 *)(P + 64) & 1)) {
            REC_FLAGS |= 0x4000000000ULL;
        }
    } else {
        s32 pf = *(s32 *)(P + 64);
        if (!(pf & 1) && !(pf & 2)) {
            REC_FLAGS |= 0x4000000000ULL;
        }
    }

    /* list the set bits of the record flags (41 entries) and total their scores */
    GW(0x22C) = 0;
    for (i = 0; i < 41; i++) {
        if ((REC_FLAGS >> (i & 63)) & 1) {
            count = GW(0x22C);
            GW(0x188 + count * 4) = i;
            GW(0x22C) = count + 1;
            GW(0x168) += *(s32 *)(*(u8 **)(G + 0x25C) + i * 4);
        }
    }
    GW(0x168) *= 100;
    GW(0x128) = func_003FB7B0(GW(0x128));
    GW(0xFC) |= 0xFC;
    GW(0x118) = 0;

    switch ((u32)GW(0x14C)) {
    case 0:
        GW(0x104) = 33;
        return 33;
    case 1:
        GW(0x104) = 32;
        return 32;
    case 2:
        GW(0x104) = 31;
        return 31;
    case 3:
        GW(0x104) = 30;
        return 30;
    case 4:
    case 5:
        GW(0x104) = 29;
        return 29;
    default:
        return GW(0x14C);
    }
}
