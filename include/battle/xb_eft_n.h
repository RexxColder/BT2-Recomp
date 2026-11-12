#ifndef BATTLE_XB_EFT_N_H
#define BATTLE_XB_EFT_N_H

#include "types.h"
#include "sys/math3d.h"
#include "battle/xb_eft_m.h"

/*
 * BT2 views for agent B's aura task / manager / lightning files (src/battle/xb_17C9D0.c onwards), after BT3's
 * include/battle/eft_n.h. Differences from BT3 (all seen in the BT2 code):
 *   EftAuraWork: one more word at 0x10 (the parameter flags), so 0x10..0x68 sit 4 bytes later than in BT3;
 *                the argument block is at 0x68 (BT3 0x64).
 *   EftAuraMgr:  `started` is a byte at 0x494; the parameter file pointer is at 0x498 (BT3 0x49C); grp[0] holds
 *                common entry 2 and grp[1] entry 3 (BT3 the other way round); the parameter file is entry 8 (BT3 1).
 */

/* Argument block of the aura task (copied into the work at +0x68). */
typedef struct EftAuraArg {
    /* 0x0 */ s32 objId;
    /* 0x4 */ s32 variant;   /* 0 = normal (aura flag 0x10), not 0 = flag 0x20, which is never drawn */
} EftAuraArg;

/* Work of one fighter's aura task (0x510 bytes, BtlTask_CreateChildList; `EftAura` in xb_eft_m.h). */
typedef struct EftAuraWork {
    /* 0x000 */ s32 flags;       /* 1 active, 2 finished, 4 hidden, 8 first frame, 0x10 / 0x20 variant, 0x40 model new */
    /* 0x004 */ u32 altMask;
    /* 0x008 */ s32 fadeA;
    /* 0x00C */ s32 fadeB;
    /* 0x010 */ s32 paramFlags;  /* BtlCharApi_ObjGetParamFlags0: any of 0x5E selects the second colour table */
    /* 0x014 */ s32 type;        /* aura type of the character */
    /* 0x018 */ s32 unk18;       /* the type again */
    /* 0x01C */ s32 colorCount;
    /* 0x020 */ s32 texFirst;
    /* 0x024 */ s32 texCount;
    /* 0x028 */ s32 partsStarted;
    /* 0x02C */ s32 fade;        /* 0 steady, 1 fading in, 2 fading out, 3 fading out and then finished */
    /* 0x030 */ s32 burst;       /* 0 none, 1 rising, 2 peak, 4 ending */
    /* 0x034 */ s32 frame;
    /* 0x038 */ s32 flameCount;
    /* 0x03C */ f32 alpha;
    /* 0x040 */ f32 burstSpeed;
    /* 0x044 */ f32 burstTime;
    /* 0x048 */ f32 lifeScale;
    /* 0x04C */ f32 level;
    /* 0x050 */ f32 burstLevel;
    /* 0x054 */ f32 unk50;
    /* 0x058 */ f32 unk54;
    /* 0x05C */ f32 unk58;
    /* 0x060 */ f32 unk5C;
    /* 0x064 */ f32 scale;
    /* 0x068 */ EftAuraArg arg;
    /* 0x070 */ Vec4 pos;
    /* 0x080 */ Vec4 prevPos;
    /* 0x090 */ Vec4 part[EFT_AURA_PARTS];
    /* 0x130 */ Vec4 partPrev[EFT_AURA_PARTS];
    /* 0x1D0 */ Vec4 partEnd[EFT_AURA_PARTS];
    /* 0x270 */ Vec4 partRef[EFT_AURA_PARTS];
    /* 0x310 */ Vec4 unk310;
    /* 0x320 */ Vec4 axis;
    /* 0x330 */ Vec4 sparkPos[EFT_AURA_SPARKS];
    /* 0x3F0 */ Vec4 colorStart;
    /* 0x400 */ Vec4 colorEnd;
    /* 0x410 */ Vec4 colorAlt[4];
    /* 0x450 */ Vec4 sparkColor[4];
    /* 0x490 */ Vec4 sparkColorAlt[4];
    /* 0x4D0 */ u64 tex[7];      /* GS TEX0 of the flame sheet: [0] normal, [1 + n] with flag 0x80 */
    /* 0x508 */ s32 sparkState;  /* handed to EftAura_UpdateSparks */
    /* 0x50C */ s32 unk50C;
} EftAuraWork; /* size 0x510 */

typedef struct EftNTexEntry {
    /* 0x00 */ u64 tex0;
    /* 0x08 */ u64 unk8;
} EftNTexEntry; /* 0x10 */

typedef struct EftNTexSet {
    /* 0x000 */ EftNTexEntry entry[32];
    /* 0x200 */ s32 count;
    /* 0x204 */ s32 unk204;
} EftNTexSet; /* 0x208 */

typedef struct EftAuraTexGroup {
    /* 0x000 */ s32 ready;       /* cleared by the manager every frame */
    /* 0x004 */ u8 unk4[0x1C];
    /* 0x020 */ s32 *data;       /* common entry 2 / 3 */
    /* 0x024 */ s32 unk24;
    /* 0x028 */ EftNTexSet set;
} EftAuraTexGroup; /* size 0x230 */

/* Effect task (BT3 include/battle/eft_g.h). */
typedef struct EftNTask {
    /* 0x00 */ u8 flags;
    /* 0x01 */ u8 unk1[0x37];
    /* 0x38 */ void *work;
} EftNTask;

/* gEftAuraPool (0x4A0 bytes). */
typedef struct EftAuraMgr {
    /* 0x000 */ s32 count;       /* characters */
    /* 0x004 */ s32 flameMax;    /* 50 per character */
    /* 0x008 */ s32 sparkMax;    /* 18 per character */
    /* 0x00C */ EftAuraFlame *flames;
    /* 0x010 */ EftAuraFlame *flameFree;
    /* 0x014 */ EftAuraFlame *flameUsed;
    /* 0x018 */ EftAuraSpark *sparks;
    /* 0x01C */ EftAuraSpark *sparkFree;
    /* 0x020 */ EftAuraSpark *sparkUsed;
    /* 0x024 */ s32 flameNext;
    /* 0x028 */ s32 sparkNext;
    /* 0x02C */ s32 unk2C;
    /* 0x030 */ EftAuraTexGroup grp[2];
    /* 0x490 */ EftNTask **tasks; /* the aura task of each character, or NULL */
    /* 0x494 */ u8 started;
    /* 0x495 */ u8 unk495[3];
    /* 0x498 */ void *data;      /* common entry 8: gEftAuraCfg and gEftAuraPrm both point at it */
    /* 0x49C */ s32 unk49C;
} EftAuraMgr; /* size 0x4A0 */

/* Body lightning: BT3 layouts (EftBolt_AllocSegs / FreeSegs / Step / DrawFlashes are the same code in BT2). */
/* ---- body lightning ------------------------------------------------------------------------------------- */

#define EFT_BOLT_COUNT 10
#define EFT_BOLT_FLASHES 20

/* One joint of a bolt. A bolt is drawn as a strip of quads between consecutive joints. */
typedef struct EftBoltSeg {
    /* 0x00 */ s32 flags;    /* 0 = free; 1 used, 2 shown, 4 first flash frame done, 8 flash over, 0x10 released (it
                                drifts, shrinks and fades), 0x20 thick (not the first or last joint) */
    /* 0x04 */ f32 widthA;   /* half width on one side */
    /* 0x08 */ f32 widthB;   /* and on the other */
    /* 0x0C */ f32 alphaMax; /* 150 / 255 */
    /* 0x10 */ Vec4 pos;     /* relative to the bolt's origin */
    /* 0x20 */ f32 r;        /* 50 / 255 */
    /* 0x24 */ f32 g;        /* 30 / 255 */
    /* 0x28 */ f32 b;        /* 150 / 255 */
    /* 0x2C */ f32 alpha;
    /* 0x30 */ struct EftBoltSeg *next;
    /* 0x34 */ u8 unk34[0xC];
} EftBoltSeg; /* size 0x40 */

/* A bolt: a chain of joints from one model node to another. */
typedef struct EftBolt {
    /* 0x00 */ EftBoltSeg *head;
    /* 0x04 */ s32 shown;    /* joints shown; jumps to `count` on the first update, then falls by 2 or 3 a frame, and
                                the first `count - shown` joints are released */
    /* 0x08 */ s32 count;    /* joints in the chain */
    /* 0x0C */ s32 flags;    /* 0 = free; 1 active, 2 fully shown (joints are being released), 4 finished */
    /* 0x10 */ s32 kind;     /* row of the node pair table */
    /* 0x14 */ s32 nodeA;
    /* 0x18 */ s32 nodeB;
    /* 0x1C */ f32 life;     /* frames left, 30 at the start */
    /* 0x20 */ f32 follow;   /* how far the origin moves from node A towards node B, 0..1 */
    /* 0x24 */ u8 unk24[0xC];
    /* 0x30 */ Vec4 pos;     /* origin */
    /* 0x40 */ Vec4 unk40;
    /* 0x50 */ Vec4 start;   /* start point, relative to the origin */
    /* 0x60 */ Vec4 end;     /* end point */
    /* 0x70 */ Vec4 dir;     /* unit vector from start to end */
    /* 0x80 */ Vec4 normal;  /* unit vector the bolt bulges along */
} EftBolt; /* size 0x90 */

/* A flash sprite that follows two model nodes. */
typedef struct EftBoltFlash {
    /* 0x00 */ s32 flags;    /* 0 = free; 1 alive */
    /* 0x04 */ s32 nodeA;
    /* 0x08 */ s32 nodeB;
    /* 0x0C */ s32 frame;    /* 0..3: cell of the 2 x 2 sheet */
    /* 0x10 */ s32 kind;     /* texture of the flash set */
    /* 0x14 */ f32 life;     /* frames left: 6 (kind 0) or 3 */
    /* 0x18 */ f32 size;
    /* 0x1C */ f32 sizeRate;
    /* 0x20 */ f32 alphaRate;
    /* 0x24 */ f32 follow;
    /* 0x28 */ f32 rot;      /* -pi..pi */
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ Vec4 pos;
    /* 0x40 */ Vec4 vel;
    /* 0x50 */ f32 r;
    /* 0x54 */ f32 g;
    /* 0x58 */ f32 b;
    /* 0x5C */ f32 a;
    /* 0x60 */ Vec4 uv;
} EftBoltFlash; /* size 0x70 */

/* Work of one fighter's lightning task (0xEB0 bytes; the task itself is at 0x167FD8.., in the next file). */
typedef struct EftBoltWork {
    /* 0x000 */ s32 flags;
    /* 0x004 */ s32 objId;
    /* 0x008 */ u8 unk8[8];
    /* 0x010 */ EftBolt bolt[EFT_BOLT_COUNT];
    /* 0x5B0 */ EftBoltFlash flash[EFT_BOLT_FLASHES];
    /* 0xE70 */ s32 paramFlags;  /* BtlCharApi_ObjGetParamFlags0; 8 = bolts more often */
    /* 0xE74 */ s32 side;        /* alternates 0 / 1 per spawn */
    /* 0xE78 */ s32 boltCount;   /* live bolts */
    /* 0xE7C */ s32 orderPos;    /* 0..3: position in `order` */
    /* 0xE80 */ s32 order[4];    /* a random permutation of 0..3 */
    /* 0xE90 */ f32 angle[2];    /* running angle of each side */
    /* 0xE98 */ u64 tex0;        /* GS TEX0 of the bolt texture */
    /* 0xEA0 */ f32 scale;       /* fighter height / 19.35 */
    /* 0xEA4 */ u8 unkEA4[0xC];
} EftBoltWork; /* size 0xEB0 */

/* A pair of model nodes a bolt can run between. */
typedef struct EftBoltPair {
    /* 0x00 */ s32 nodeA;
    /* 0x04 */ s32 nodeB;
    /* 0x08 */ f32 length;
    /* 0x0C */ f32 follow;       /* base */
    /* 0x10 */ f32 followRange;
} EftBoltPair; /* size 0x14 */

/* gEftBoltPool (0x478 bytes, allocated at 0x1682F0 in the next file). */
typedef struct EftBoltPool {
    /* 0x000 */ s32 unk0;
    /* 0x004 */ s32 segMax;
    /* 0x008 */ EftBoltSeg *segs;
    /* 0x00C */ s32 segNext;     /* where the search for a free joint starts */
    /* 0x010 */ u8 unk10[0x258];
    /* 0x268 */ EftNTexSet flashTex;
    /* 0x470 */ struct EftNTask **tasks;
    /* 0x474 */ EftBoltPair *pairs;
} EftBoltPool; /* size 0x478 */

extern EftBoltPool *gEftBoltPool;

#endif
