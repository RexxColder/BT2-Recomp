#ifndef BATTLE_XC_EFT_PTCL4_H
#define BATTLE_XC_EFT_PTCL4_H

#include "types.h"
#include "sys/math3d.h"
#include "battle/eft_t.h"

/*
 * Agent C view of a second BT2 emitter module, 0x1BCB48..0x1C0D18, called EftPtcl4 here: the same interface as the
 * particle emitter EftPtcl3 (include/battle/xc_eft_ptcl.h) with a smaller work (0x110 bytes) and particles taken from
 * the node pool at the start of the module (200 nodes of 0x100 bytes, D_0038788C). Task class 0x342920 =
 * { EftPtcl4_Update, EftPtcl4_Init, EftPtcl4_Term, 0x1C0680, 0x1C0688, EftPtcl4_Draw }, manager class 0x342908.
 */

/* One entry of the texture set. */
typedef struct XcPtcl4Res {
    /* 0x000 */ EftTTex tex[32];
    /* 0x200 */ u8 unk200[4];
    /* 0x204 */ u32 uploaded;     /* bit n: entry n's TEX0 is built for this frame */
} XcPtcl4Res;

typedef struct XcPtcl4Def {
    /* 0x0 */ u8 unk0[3];
    /* 0x3 */ u8 shape;           /* 0 / 2: axis quads (polygons with flag 0x20); 1, 3: other draw routines */
} XcPtcl4Def;

/* Argument of EftPtcl4_Create (0x50 bytes, copied whole into the work). */
typedef struct XcPtcl4Arg {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 size;
    /* 0x08 */ u8 unk8[8];
    /* 0x10 */ EftTVec pos;
    /* 0x20 */ EftTVec dir;
    /* 0x30 */ s32 texIdx;
    /* 0x34 */ XcPtcl4Res *res;
    /* 0x38 */ XcPtcl4Def *def;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 objId;
    /* 0x44 */ u8 unk44[0xC];
} __attribute__((aligned(16))) XcPtcl4Arg; /* size 0x50 */

#define XC_PTCL4_ALIVE 0x01
#define XC_PTCL4_STOP 0x02
#define XC_PTCL4_DEAD 0x04
#define XC_PTCL4_VIEW 0x10        /* drawn only while viewObj is in view */
#define XC_PTCL4_POLYS 0x20       /* shapes 0 / 2 drawn as polygons */

/* Work of the task class 0x342920 (0x110 bytes). */
typedef struct XcPtcl4Work {
    /* 0x000 */ void *head;       /* node list (head, tail) of the module's pool */
    /* 0x004 */ void *tail;
    /* 0x008 */ u8 unk8[8];
    /* 0x010 */ XcPtcl4Arg arg;
    /* 0x060 */ s32 flags;        /* XC_PTCL4_* */
    /* 0x064 */ u8 type;
    /* 0x065 */ u8 unk65[7];
    /* 0x06C */ s32 viewObj;
    /* 0x070 */ u8 unk70[8];
    /* 0x078 */ f32 startDelay;   /* guess */
    /* 0x07C */ f32 stopDelay;    /* guess */
    /* 0x080 */ Mtx44 base;
    /* 0x0C0 */ Mtx44 mtx;        /* rotation built from arg.dir */
    /* 0x100 */ f32 pitch;
    /* 0x104 */ f32 yaw;
    /* 0x108 */ u8 unk108[8];
} XcPtcl4Work; /* size 0x110 */

/* The manager block (D_0038788C): the node pool. */
typedef struct XcPtcl4Mgr {
    /* 0x0 */ u8 *pool;           /* 200 nodes of 0x100 bytes */
    /* 0x4 */ s32 next;           /* where the next free-node search starts */
    /* 0x8 */ s32 used;
} XcPtcl4Mgr; /* size 0xC */

#endif
