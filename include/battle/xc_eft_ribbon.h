#ifndef BATTLE_XC_EFT_RIBBON_H
#define BATTLE_XC_EFT_RIBBON_H

#include "types.h"
#include "sys/math3d.h"
#include "battle/eft_t.h"

/*
 * Agent C view of BT2's ribbon module (BT3 eft_ab_c.c EftRibbon, effect pack part kind 17), task class 0x3429B0 =
 * { EftRibbon_Update, 0x1C6CF8 (init), EftRibbon_Term, 0x1C6F70, 0x1C6F78, EftRibbon_Draw }, manager class 0x342998.
 * The BT2 work is 0x170 bytes (BT3: 0x1E0); kind 2 ribbons hand their points to an EftTrail instead of drawing.
 */

/* Argument of EftRibbon_Create (0x40 bytes, copied whole into the work). */
typedef struct XcRibbonArg {
    /* 0x00 */ u8 type;           /* owner's effect type */
    /* 0x01 */ u8 unk1[3];
    /* 0x04 */ s32 chr;           /* owner */
    /* 0x08 */ u8 unk8[4];
    /* 0x0C */ f32 size;          /* EftRibbon_SetSize */
    /* 0x10 */ EftTVec pos;       /* first point */
    /* 0x20 */ u8 unk20[0x18];
    /* 0x38 */ void *prm;         /* parameter block of the pack */
    /* 0x3C */ void *tex;
} __attribute__((aligned(16))) XcRibbonArg; /* size 0x40 */

/* A node of a ribbon; only the position. */
typedef struct XcRibbonNode {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ Vec4 pos;
} XcRibbonNode;

#define XC_RIBBON_ALIVE 0x01
#define XC_RIBBON_STOP 0x02       /* fading out */
#define XC_RIBBON_DEAD 0x04       /* the update kills the task */

/* Work of the task class 0x3429B0 (0x170 bytes). */
typedef struct XcRibbonWork {
    /* 0x000 */ XcRibbonNode *head;
    /* 0x004 */ u8 unk4[0xC];
    /* 0x010 */ XcRibbonArg arg;
    /* 0x050 */ s32 flags;        /* XC_RIBBON_* */
    /* 0x054 */ s32 kind;         /* 0, 1: drawn here; 2: an EftTrail */
    /* 0x058 */ s32 unk58;        /* EftRibbon_SetUnk58 */
    /* 0x05C */ s32 unk5C;        /* EftRibbon_SetUnk5C */
    /* 0x060 */ u8 unk60[0xC];
    /* 0x06C */ f32 fadeTime;     /* frames; at least 1 */
    /* 0x070 */ u8 unk70[0x20];
    /* 0x090 */ Vec4 end;         /* second point */
    /* 0x0A0 */ u8 unkA0[0xC8];
    /* 0x168 */ void *trail;      /* kind 2: the EftTrail handle */
    /* 0x16C */ u8 unk16C[4];
} XcRibbonWork; /* size 0x170 */

/* A texture set with the scene entry it was loaded from. */
typedef struct XcRibbonTex {
    /* 0x0 */ s32 *entry;         /* common entry 0x26 of the battle scene */
    /* 0x4 */ u8 unk4[4];
    /* 0x8 */ u8 set[0x104];      /* EftTexSet_Load16 */
} XcRibbonTex;

/* gEftRibbonMgr (D_0038789C). */
typedef struct XcRibbonMgr {
    /* 0x000 */ void *nodes;      /* 40000 bytes */
    /* 0x004 */ u8 unk4[4];
    /* 0x008 */ XcRibbonTex tex;
    /* 0x114 */ s32 uploaded;     /* cleared by the manager update */
    /* 0x118 */ u8 unk118[0x10];
} XcRibbonMgr; /* size 0x128 */

#endif
