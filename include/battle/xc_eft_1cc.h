#ifndef BATTLE_XC_EFT_1CC_H
#define BATTLE_XC_EFT_1CC_H

#include "types.h"
#include "sys/math3d.h"
#include "battle/eft_t.h"

/*
 * Agent C view of the BT2 effect module 0x1CB5F0..0x1CCD60, task class 0x342D98 = { EftMod1CC_Update,
 * EftMod1CC_Init, EftMod1CC_Term, 0x1CC7E8, 0x1CC7F0, EftMod1CC_Draw } (manager class 0x342D80, 20 tasks of 0xD0
 * bytes). Not identified; the argument block is copied whole into the start of the work. Name prefix EftMod1CC.
 */

typedef struct XcMod1CCRes {
    /* 0x000 */ EftTTex tex[16];
    /* 0x100 */ u8 unk100[4];
    /* 0x104 */ u32 uploaded;     /* bit n: entry n's TEX0 is built for this frame */
} XcMod1CCRes;

typedef struct XcMod1CCPrm {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 kind;           /* draw routine */
    /* 0x02 */ u8 unk2[6];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 unk20[4];
    /* 0x24 */ s32 cols;
    /* 0x28 */ s32 rows;
} XcMod1CCPrm;

#define XC_MOD1CC_ALIVE 0x01
#define XC_MOD1CC_STOP 0x02
#define XC_MOD1CC_DEAD 0x04
#define XC_MOD1CC_ENDLESS 0x08    /* no life time */
#define XC_MOD1CC_VIEW 0x10       /* drawn only while its owner is in view */
#define XC_MOD1CC_ANIM 0x100      /* texture animation of more than one frame */

/* The first 0x40 bytes of the work: the create argument, copied whole. */
typedef struct XcMod1CCArgBlock {
    /* 0x00 */ u64 d[8];
} __attribute__((aligned(16))) XcMod1CCArgBlock;

/* Work (0xD0 bytes); 0x00..0x40 is the create argument. */
typedef struct XcMod1CCWork {
    /* 0x00 */ s32 chr;           /* owner */
    /* 0x04 */ s32 texIdx;
    /* 0x08 */ f32 life;          /* seconds; <= 0: until stopped */
    /* 0x0C */ f32 size;
    /* 0x10 */ EftTVec pos;
    /* 0x20 */ EftTVec dir;       /* unit vector */
    /* 0x30 */ XcMod1CCRes *res;
    /* 0x34 */ XcMod1CCPrm *prm;
    /* 0x38 */ Vec4 *unk38;
    /* 0x3C */ u8 unk3C[4];
    /* 0x40 */ s32 flags;         /* XC_MOD1CC_* */
    /* 0x44 */ u8 type;
    /* 0x45 */ u8 unk45[3];
    /* 0x48 */ s32 frames;        /* cols * rows of the texture animation */
    /* 0x4C */ f32 du;            /* 1 / cols */
    /* 0x50 */ f32 dv;            /* 1 / rows */
    /* 0x54 */ u8 unk54[4];
    /* 0x58 */ f32 lifeFrames;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ u8 unk6C[4];
    /* 0x70 */ f32 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ Vec4 unk80;
    /* 0x90 */ Vec4 unk90;
    /* 0xA0 */ EftTTex texA;
    /* 0xB0 */ EftTTex texB;
    /* 0xC0 */ u64 tex0;
    /* 0xC8 */ u8 unkC8[8];
} __attribute__((aligned(16))) XcMod1CCWork; /* size 0xD0 */

#endif
