#ifndef BATTLE_XC_EFT_PTCL_H
#define BATTLE_XC_EFT_PTCL_H

#include "types.h"
#include "sys/math3d.h"
#include "battle/eft_t.h"

/*
 * Agent C view of BT2's particle emitter module (the counterpart of BT3's EftPtcl, eft_u_b.c), task class
 * 0x3428F0 = { EftPtcl3_Update, EftPtcl3_Init, EftPtcl3_Term, 0x1BC210 (nothing), 0x1BC218 (BtlTask_SetDead),
 * EftPtcl3_Draw }, manager class 0x3428D8. The work is a smaller, older layout than BT3's (0x290 bytes instead of
 * BT3's EftPtclWork). Only the fields the matched functions touch are named.
 */

/* One particle (pool of 0x33F40 bytes in the manager). */
typedef struct XcPtcl {
    /* 0x000 */ u8 unk0[0x70];
    /* 0x070 */ Vec4 ofs;         /* EftPtcl3_Warp: pos = ofs + emitter position */
    /* 0x080 */ Vec4 pos;
    /* 0x090 */ u8 unk90[0x90];
    /* 0x120 */ struct XcPtcl *next;
} XcPtcl;

/* One entry of the texture set an emitter draws with. */
typedef struct XcPtclRes {
    /* 0x000 */ EftTTex tex[16];
    /* 0x100 */ u8 unk100[4];
    /* 0x104 */ u32 uploaded;     /* bit n: entry n's TEX0 is built for this frame */
} XcPtclRes;

/* What a definition says about the shape; only the byte the draw callback reads. */
typedef struct XcPtclDef {
    /* 0x0 */ u8 unk0[3];
    /* 0x3 */ u8 shape;           /* 0: axis quads (or polygons with flag 0x200), 1, 2: other draw routines */
} XcPtclDef;

/* Argument of EftPtcl3_Create (0x50 bytes, copied whole into the work). */
typedef struct XcPtclArg {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 size;          /* EftPtcl3_SetSize */
    /* 0x08 */ u8 unk8[8];
    /* 0x10 */ EftTVec pos;       /* EftPtcl3_SetPos / _Warp */
    /* 0x20 */ EftTVec dir;       /* EftPtcl3_SetDir (unit vector) */
    /* 0x30 */ s32 texIdx;
    /* 0x34 */ XcPtclRes *res;
    /* 0x38 */ XcPtclDef *def;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 objId;         /* owner, for the scene's hidden / stopped tests */
    /* 0x44 */ u8 unk44[0xC];
} __attribute__((aligned(16))) XcPtclArg; /* size 0x50 */

/* XcPtclWork.flags */
#define XC_PTCL_ALIVE 0x001
#define XC_PTCL_STOP 0x002        /* stop emitting */
#define XC_PTCL_DEAD 0x004        /* the task ends on its next update */
#define XC_PTCL_FRONT 0x020       /* drawn only in the view that shows its fighter */
#define XC_PTCL_FLAG80 0x080
#define XC_PTCL_FLAG100 0x100
#define XC_PTCL_POLYS 0x200       /* shape 0 drawn as polygons */

/* Work of the emitter task class 0x3428F0 (0x290 bytes). */
typedef struct XcPtclWork {
    /* 0x000 */ XcPtcl *head;     /* the live particles, linked by next */
    /* 0x004 */ u8 unk4[0xC];
    /* 0x010 */ XcPtclArg arg;
    /* 0x060 */ s32 flags;        /* XC_PTCL_* */
    /* 0x064 */ u8 type;          /* owner's effect type */
    /* 0x065 */ u8 unk65[0xD7];
    /* 0x13C */ f32 startDelay;   /* guess */
    /* 0x140 */ f32 stopDelay;    /* guess */
    /* 0x144 */ u8 unk144[0xC];
    /* 0x150 */ Vec4 target;      /* EftPtcl3_SetTarget */
    /* 0x160 */ Vec4 aim;         /* unit vector emitter -> target */
    /* 0x170 */ Mtx44 aimMtx;     /* rotation built from aim */
    /* 0x1B0 */ u8 unk1B0[0x20];
    /* 0x1D0 */ Mtx44 base;       /* the matrix the rotations start from */
    /* 0x210 */ Mtx44 mtx;        /* rotation built from arg.dir */
    /* 0x250 */ f32 pitch;
    /* 0x254 */ f32 yaw;
    /* 0x258 */ u8 unk258[8];
    /* 0x260 */ EftTTex texA;     /* image entry */
    /* 0x270 */ EftTTex texB;     /* palette entry */
    /* 0x280 */ u64 tex0;         /* this frame's TEX0 */
    /* 0x288 */ u8 unk288[8];
} XcPtclWork; /* size 0x290 */

/* The manager block (D_00387884). */
typedef struct XcPtclMgr {
    /* 0x0 */ XcPtcl *pool;       /* 0x33F40 bytes */
    /* 0x4 */ u8 unk4[8];
} XcPtclMgr; /* size 0xC */

#endif
