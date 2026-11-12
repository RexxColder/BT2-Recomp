#ifndef BATTLE_XC_EFT_CHAIN_H
#define BATTLE_XC_EFT_CHAIN_H

#include "types.h"
#include "sys/math3d.h"
#include "battle/eft_t.h"

/*
 * Agent C views of the BT2 "chain" module (effect pack part kind 18) and the ray burst (part kind 0),
 * 0x1B3378..0x1B4258 (src/battle/xc_1B3378.c). Same code as BT3's eft_s.c second part; the chain work has a
 * different layout in BT2 (flags at 0xA40 instead of 0xE80, strands of 0xA0 bytes at 0x40).
 * EftTTask, EftTVec, EftTTaskList, EftTTex come from battle/eft_t.h (same layout in BT2).
 */

/* Argument of EftChain_Create (0x40 bytes, copied whole into the work). */
typedef struct XcChainArg {
    /* 0x00 */ f32 unk0[3];
    /* 0x0C */ f32 size;          /* EftChain_SetSize */
    /* 0x10 */ EftTVec pos;       /* EftChain_SetPos / _Warp */
    /* 0x20 */ u8 unk20[0x20];
} XcChainArg; /* size 0x40 */

/* One link of a strand. */
typedef struct XcChainLink {
    /* 0x00 */ u8 unk0[0x20];
    /* 0x20 */ Vec4 unk20;
    /* 0x30 */ Vec4 unk30;
    /* 0x40 */ Vec4 pos;
    /* 0x50 */ u8 unk50[0x10];
    /* 0x60 */ struct XcChainLink *next;
} XcChainLink;

/* One of the 16 strands. */
typedef struct XcChainStrand {
    /* 0x00 */ XcChainLink *head;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 flags;         /* bit 0: in use */
    /* 0x0C */ u8 unkC[0x44];
    /* 0x50 */ Vec4 ofs;          /* added to every link by EftChain_Warp */
    /* 0x60 */ u8 unk60[0x40];
} XcChainStrand; /* size 0xA0 */

/* Work of the chain task class 0x3427E8 (update callback 0x1B2FD0). */
typedef struct XcChainWork {
    /* 0x000 */ XcChainArg arg;
    /* 0x040 */ XcChainStrand strand[16];
    /* 0xA40 */ s32 flags;        /* EFT_CHAIN_* of battle/eft_t.h */
    /* 0xA44 */ u8 type;
    /* 0xA45 */ u8 unkA45[0xB];
    /* 0xA50 */ s32 param3;       /* kept in 3..7 */
    /* 0xA54 */ u8 unkA54[0xC];
    /* 0xA60 */ f32 param5;
    /* 0xA64 */ f32 param6;
} XcChainWork;

/* Argument of EftRay_Create (0x60 bytes). As BT3's EftRayArg except autoKill is a byte. */
typedef struct XcRayArg {
    /* 0x00 */ EftTVec pos;
    /* 0x10 */ s32 color[4];
    /* 0x20 */ f32 life;
    /* 0x24 */ f32 length;
    /* 0x28 */ f32 width;
    /* 0x2C */ f32 inner;
    /* 0x30 */ f32 jitter;
    /* 0x34 */ s32 mode;
    /* 0x38 */ u32 count;
    /* 0x3C */ s32 objId;
    /* 0x40 */ s32 blend;
    /* 0x44 */ s32 space;
    /* 0x48 */ s32 delay;
    /* 0x4C */ s32 fadeFrames;
    /* 0x50 */ u8 autoKill;
    /* 0x51 */ u8 unk51[0xF];
} __attribute__((aligned(16))) XcRayArg; /* size 0x60 */

#endif
