#ifndef BATTLE_XC_EFT_1CB_H
#define BATTLE_XC_EFT_1CB_H

#include "types.h"
#include "sys/math3d.h"
#include "battle/eft_t.h"

/*
 * Agent C view of the BT2 effect module whose task class is 0x342C68 = { EftMod1CB_Update, EftMod1CB_Init,
 * EftMod1CB_Term, 0x1CB120, 0x1CB128, EftMod1CB_Draw } (manager class 0x342C50). The module is not identified; it
 * keeps two texture sets (scene common entries 0x20 and 0x21) and up to 20 tasks. Name prefix EftMod1CB.
 */

typedef struct XcMod1CBArg {
    /* 0x00 */ s32 chr;           /* owner */
    /* 0x04 */ s32 unk4;          /* zeroed by the init callback */
    /* 0x08 */ u8 unk8[4];
    /* 0x0C */ f32 size;
    /* 0x10 */ EftTVec pos;
    /* 0x20 */ u8 unk20[0x18];
    /* 0x38 */ void *prm;         /* parameter block of the pack */
    /* 0x3C */ u8 unk3C[4];
} __attribute__((aligned(16))) XcMod1CBArg; /* size 0x40 */

#define XC_MOD1CB_ALIVE 0x01
#define XC_MOD1CB_STOP 0x02
#define XC_MOD1CB_DEAD 0x04

typedef struct XcMod1CBWork {
    /* 0x000 */ u8 unk0[4];
    /* 0x004 */ s32 texB;         /* EftMod1CB_SetTex */
    /* 0x008 */ u8 unk8[8];
    /* 0x010 */ XcMod1CBArg arg;
    /* 0x050 */ s32 flags;        /* XC_MOD1CB_* */
    /* 0x054 */ u8 type;          /* owner's effect type */
    /* 0x055 */ u8 unk55[0xF];
    /* 0x064 */ f32 unk64;
    /* 0x068 */ f32 unk68;
    /* 0x06C */ u8 unk6C[0x34];
    /* 0x0A0 */ EftTTex texA;
    /* 0x0B0 */ EftTTex texBEntry;
    /* 0x0C0 */ u8 unkC0[0x50];
} XcMod1CBWork; /* size 0x110 */

/* One of the manager's two texture sets. */
typedef struct XcMod1CBTex {
    /* 0x000 */ u8 unk0[0x20];
    /* 0x020 */ s32 *entry;       /* scene common entry */
    /* 0x024 */ u8 unk24[4];
    /* 0x028 */ u8 set[0x104];    /* EftTexSet_Load16 */
    /* 0x12C */ s32 uploaded;     /* cleared every frame */
} XcMod1CBTex; /* size 0x130 */

/* The manager block (D_003878B8). */
typedef struct XcMod1CBMgr {
    /* 0x000 */ void *pool;       /* 0x17700 bytes */
    /* 0x004 */ u8 unk4[4];
    /* 0x008 */ s32 count;        /* live tasks */
    /* 0x00C */ u8 unkC[4];
    /* 0x010 */ XcMod1CBTex tex[2];
    /* 0x270 */ void *table;      /* D_00342C80 */
    /* 0x274 */ u8 unk274[4];
} XcMod1CBMgr; /* size 0x278 */

#endif
