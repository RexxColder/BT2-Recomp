#include "common.h"
#include "battle/eft_t.h"

/*
 * 0x1809C0..0x182CE8: the module of task class 0x2C3EC0 (EftShotFx_*), the teleport ("vanish") lines: black
 * vertical streaks on a fighter's body and in a column around it. Written as two files and merged at
 * integration (one object in the original: its .rodata is tables, jump table, constants in that order): this
 * first part is the head, 0x1809C0..0x180BF8; the second part (formerly eft_u.c, 0x180BF8..0x182CE8) has the
 * other callbacks and all of the drawing (include/battle/eft_u.h has the full work layout).
 * Here: the request entry the fighter effect layer calls (requests 0xC..0xF give kinds 0..3, and object
 * animation event bit 42 gives kind 0), its slot finder, and the class's init callback.
 * Drawing only: a request is an object id and two frame counters.
 */

extern void *memset(void *dst, s32 c, u32 n);

extern s32 BtlPool_GetCurrent(void);
extern void *BtlPool_Alloc(s32 slot, s32 size);
extern s32 *BtlScene_GetCommonEntry(s32 idx);
extern void EftTexSet_Load4(EftTTex *tex, s32 *entry); /* builds a texture set from a pack entry */

extern EftTShotFxMgr *gEftShotFx;

/* The module's two file-scope tables (0x2ECEC0 body segments, 0x2ED0E8 column slices; layouts in
 * include/battle/eft_u.h). They come first in this object's .rodata, in front of the jump table of
 * EftShotFx_Request (0x2ED180), so they belong to this file. The second part reads them through non-const
 * `extern` declarations (as const data defined here its loads change), so they are emitted from the original. */



/* Returns a free request slot (flags == 0) of the two, or NULL. */
EftTShotFxReq *EftShotFx_FindFree(void);

/* Starts the lines on a fighter. Kinds 0 / 1 start sequence A / B (limb lines plus a column, flags 0x21 /
   0x12), kinds 2 / 3 the same with the burst bit 0x80, kind 4 claims a slot and clears it at once. Returns 0
   only when the module is not loaded or both slots are busy. */
s32 EftShotFx_Start(s32 objId, u8 kind);

/* Init callback of the task class 0x2C3EC0: the work, two request slots, 200 lines and the texture set. Each
   block is only allocated when missing. */
void EftShotFxMgr_Init(EftTTask *task);

/* ------------------------------------------------------------------------------------------------------------
 * Second part (formerly eft_u.c), with its own header and view types. Names the first part already declared with
 * other types are reached through cast macros (the generated code is the same).
 * ------------------------------------------------------------------------------------------------------------ */
#include "battle/eft_u.h"
#include "sys/gfx_ot.h"

/*
 * Vanish lines (module EftShotFx), 0x180BF8..0x182CE8: the rest of the module that starts at 0x1809C0 in
 * the first part. See include/battle/eft_u.h. The black vertical streaks of a teleport: on the body and in a column
 * around it, for fighter effect requests 0xC..0xF.
 * Drawing only: reads fighters through BtlCharApi_GetHeight / BtlCharApi_GetNodePos, writes nothing outside its
 * own pool and the display list. Random values come from libc rand().
 */

#define RAND_MAX_F 2147483647.0f

typedef struct EftUBattleWork {
    /* 0x0000 */ u8 unk0[0x19F0];
    /* 0x19F0 */ u64 flags; /* 0x100 = paused */
} EftUBattleWork;

/* The view being drawn (include/battle/btl_cam.h). */
typedef struct EftUView {
    /* 0x000 */ Mtx44 world2view;
    /* 0x040 */ Mtx44 world2view2;
    /* 0x080 */ u8 unk80[0xC0];
    /* 0x140 */ Mtx44 world2screen;
} EftUView;

/* GS XYZF2 register value. */
typedef struct EftUXyzf {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} EftUXyzf;

typedef struct EftUGsVtx {
    /* 0x00 */ u8 rgba[4];
    /* 0x04 */ f32 q;
    /* 0x08 */ f32 s;
    /* 0x0C */ f32 t;
    /* 0x10 */ EftUXyzf xyz;
} EftUGsVtx; /* 0x18: RGBAQ, ST, XYZF2 */

/* Triangle strip of four full vertices. 0x90 bytes. */
typedef struct EftUQuadPkt {
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 next;
    /* 0x08 */ u32 vif0;
    /* 0x0C */ u32 vif1;
    /* 0x10 */ u64 gif0;
    /* 0x18 */ u64 gif1;
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 tex0;
    /* 0x30 */ EftUGsVtx v[4];
} EftUQuadPkt;

#define V(p) ((Vec4 *)(p))

/* The "up" vector constant of three functions. The original object has three copies of it in .rodata (0x2ED1A0,
   0x2ED1B0, 0x2ED1C0); this compiler merges identical initialisers of one type, so each function gets a type of
   its own to keep them apart. */
typedef struct EftUUpA {
    f32 x, y, z, w;
} __attribute__((aligned(16))) EftUUpA;
typedef struct EftUUpB {
    f32 x, y, z, w;
} __attribute__((aligned(16))) EftUUpB;
typedef struct EftUUpC {
    f32 x, y, z, w;
} __attribute__((aligned(16))) EftUUpC;

extern EftUView *gBtlCamView;
#define gEftShotFx ((EftShotFxWork *)gEftShotFx)
extern EftShotFxSeg gEftShotFxSegs[23];
extern EftShotFxRow gEftShotFxRows[6];

extern s32 rand(void);
extern void *memset(void *dst, s32 c, u32 n);
extern f32 Mathf_SinFast(f32 angle);
extern f32 Mathf_CosFast(f32 angle);
extern f32 EftMath_WrapAngle(f32 angle);
extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Scale(Vec4 *dst, Vec4 *src, f32 s);
extern void Vec3_Scale(Vec4 *dst, Vec4 *src, f32 s);
extern f32 Vec3_Length(Vec4 *v);
extern void Vec3_Cross(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern void Mtx_MulVec4(Vec4 *dst, Mtx44 *m, Vec4 *src);
extern void Mtx_Copy(Mtx44 *dst, Mtx44 *src);          /* copy */
extern void Mtx_InverseRT(Mtx44 *dst, Mtx44 *src);          /* inverse of a rotation + translation matrix */
extern void Vu0Cur_Push(void);                            /* VU0 matrix stack push */
extern void Vu0Cur_LoadMtx(Mtx44 *m);                        /* load the matrix */
extern void Vu0Cur_Pop(void);                            /* pop */
extern void Vu0Cur_ProjectPointsStq(EftUIVec *xyz, Vec4 *stq, Vec4 *pos, Vec4 *uv, s32 n); /* projects with the loaded matrix */
extern void EftTexSet_Keep4(EftShotFxTex *tex, s32 a, s32 b);
extern EftUBattleWork *Battle_GetWork(void);
extern s32 BtlPool_GetCurrent(void);
extern void BtlPool_Free(s32 slot, void *ptr);
extern f32 BtlCharApi_GetHeight(s32 objId);
extern void BtlCharApi_GetNodePos(s32 objId, s32 node, Vec4 *out);

/* Task term: frees the textures, the request slots, the pool and the work. */
void EftShotFx_Term(void);

/* Task update: the request slots, then the lines. */
void EftShotFx_Update(void) {
    EftShotFx_UpdateReqs();
    EftShotFx_UpdateLines();
}

/* Task post-update: keeps the textures referenced. */
void EftShotFx_PostUpdate(void);

/* Task draw: takes the camera rotation of the view being drawn, then draws the lines under its world-to-screen matrix. */
void EftShotFx_Draw(void);

/* Returns a zeroed free line, or NULL when all 200 are in use. */
EftShotFxLine *EftShotFx_Alloc(void);

/* Adds a line at the list tail. `life` is in seconds; the alpha ramp (flags 0x10 / 0x20) spans the whole life. */
void EftShotFx_Add(EftUVec pos, EftUVec off, f32 toward, f32 len, f32 growth, f32 accelDiv, f32 width, f32 alpha,
                     f32 life, u8 tex, u8 blend, s32 flags, s32 delay);

/* Steps every line (not while paused) and unlinks the finished ones. */
void EftShotFx_UpdateLines(void);

/* One frame of a line: start delay, life, length change, alpha ramp. Returns 1 when its life is over. */
s32 EftShotFx_Step(EftShotFxLine *p);

/* Draws every active line, black with its alpha. */
void EftShotFx_DrawLines(void);

/* Steps the two request slots (not while paused). A sequence runs for five updates (frame 0..4):
   kind 0 (vanish): body lines on frames 0 and 1, the growing column on frame 1;
   kind 1 (reappear): the shrinking column on frame 0, body lines on frames 2, 3 and 4;
   kinds 2 / 3: four sets of body lines at once (frame 0 / frame 2), started 0..3 frames apart, and no column. */
void EftShotFx_UpdateReqs(void);

/* Keeps the textures referenced while any line is alive. */
void EftShotFx_UpdateTexture(s32 a, s32 b);

/* Corners of a line: centre = anchor pulled towards the camera plus the camera-space offset; the two ends lie
   half a length above and below it and are widened across the line of sight. */
void EftShotFx_BuildQuad(Vec4 *out, EftShotFxLine *p);

/* Queues the four corners as one textured triangle strip at their average depth; dropped when a corner is
   outside the GS coordinate range. The matrix argument is not used (the loaded one projects). */
void EftShotFx_DrawQuad(Vec4 *quad, EftUMtx mtx, u8 r, u8 g, u8 b, u8 a, u64 *tex, u8 blend);

/* Lines on the body segments of a fighter (table gEftShotFxSegs, up to the row whose node is 4): rings of `count`
   lines every `spacing` along each segment, at a random start angle, each pulled towards the camera, fading out
   over `life` seconds after `delay` frames. Draws 1 + 3 * count libc rand() per ring. */
void EftShotFx_SpawnBodyLines(s32 objId, f32 life, s32 delay);

/* Rings of lines on a vertical column centred on node 3, half the fighter's height tall (table gEftShotFxRows): the
   lines grow, by 10 % less each frame, while fading out. Same random draws as the body lines. */
void EftShotFx_SpawnVanishColumn(s32 objId, f32 life);

/* The same column with lines five times as long that shrink, by 12.5 % less each frame, while fading in. */
void EftShotFx_SpawnAppearColumn(s32 objId, f32 life);

/* 1 when a projected vertex (GS coordinates, 12.4 fixed, centre 2048) is in front of the camera and within a
   box around the screen centre: margin 0 = the 512 x 448 screen, 1..3 = wider boxes, else the whole GS range. */
s32 EftShotFx_IsOnScreen(EftUIVec *v, s32 margin);
