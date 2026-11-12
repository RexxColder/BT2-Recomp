#define gBtlObjTbl D_003B2548  /* fix_targets */ /* the original uses 0x3b2548 here */
/*
 * Battle objects (0x248F28..0x24BBE8): the table of animated models of a battle, their per-frame update, the
 * battle's light, the per-view draw lists, and the model resource slots the objects are built from.
 * Layouts and an overview of the work block are in include/battle/btl_obj.h.
 *
 * Frame order (Battle_Loop / Battle_Update):
 *   _InitSys          BtlObj_RebuildTable()
 *   Battle_Update           BtlObj_UpdateAll(), then per view BtlObj_UpdateVisibility(view), then
 *                           BtlObj_FinishVisibility(split)
 *
 * Objects and resource slots:
 *   BtlRes_Request(1, model, anim0, anim1) takes one of the two fixed slots (numbers 0 and 1, buffers allocated
 *   once by BtlRes_Init) and BtlRes_Request(0, ...) one of the twelve heap slots (numbers 2..13 when the fixed
 *   slots exist, else 0..11); both queue the files with File_Request and return the slot number, which is what
 *   BattleSide + 0x26C holds. Once the reads are done, BtlObj_Create(type, BtlRes_GetSlot(number), 1) takes a
 *   free object, binds it to the slot's files and returns the object id (BattleSide + 0x268).
 *   A character change keeps both numbers: BtlRes_Reload reads the new model into the spare buffer,
 *   BtlRes_CommitReload swaps it into the slot, BtlObj_Rebind sets the same object up again.
 *
 * The original was several source files (one per part of the work block, each with its own "get" function):
 * BtlObj_UpdateVisibility only matches when BtlObjVis_GetList is not visible to the compiler. They are kept in
 * one file here because their constants are contiguous (.rodata 0x2F23F0..0x2F2420, .lit4 0x2FE630..0x2FE640).
 */
#include "common.h"
#include "battle/btl_obj.h"
#include "battle/battle.h"
#include "battle/btl_cam.h"
#include "sys/common.h"
#include "sys/dma.h"
#include "sys/file.h"
#include "sys/heap.h"

extern void *memset(void *dst, s32 c, u32 n);
extern f32 sqrtf(f32 x);

extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Scale(Vec4 *dst, Vec4 *src, f32 scale);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern void Mtx_MulVec4(Vec4 *dst, Mtx44 *m, Vec4 *v);
extern void Res_RelocateOffsets(void *out, void *base, void *hdr);
extern s32 BtlStage_IsReady(void);

/* Uploads texture `index` of a texture file to texture block tbp, its CLUT to cbp (-1: none). Returns nothing
   (src/sys/gfxm_b_b.c); the older reading of this as a table lookup was wrong. */
extern void TexFile_UploadOne(void *file, s32 index, s32 tbp, s32 cbp);
/* Model object setup / teardown (0x113598 binds the resource, 0x1135F0 clears the object). */
extern void BtlObjMdl_Destroy(BtlObj *obj);
extern void BtlObjMdl_Create(s32 type, BtlObj *obj, BtlResSlot *res);
extern void ObjShadow_Update(BtlObj *obj);
extern void ObjShadow_InitPool(void);
extern void ObjShadow_TermPool(void);
/* Matrix helpers: 0x120230 copies the rotation rows, 0x1202A0 inverts a view matrix, 0x121388 gets the
 * current world-to-screen matrix, 0x122310 projects a point to integer screen coordinates. */
extern void Mtx_Copy(Mtx44 *dst, Mtx44 *src);
extern void Mtx_InverseRT(Mtx44 *dst, Mtx44 *src);
extern void Vu0Screen_StoreMtx(Mtx44 *dst);
extern void Mtx_ProjectInt(s32 *out, Mtx44 *m, Vec4 *v);
/* Box helpers: reset, set from centre + half size, add a point, get centre, get half size, contains point. */
extern void StgAabb_SetEmpty(BtlObjBox *box);
extern void ColBox_SetCenterHalf(BtlObjBox *box, Vec4 *center, Vec4 *extent);
extern void ColBox_AddPoint(BtlObjBox *box, Vec4 *point);
extern void ColBox_GetCenter(BtlObjBox *box, Vec4 *center);
extern void ColBox_GetHalf(BtlObjBox *box, Vec4 *extent);
extern s32 ColBox_ContainsPoint(BtlObjBox *box, Vec4 *point);
/* Stage: light direction, light record (bytes 8..11 = colour), ambient colour as integers. */
extern void BtlStage_GetLightVecB(Vec4 *dir);
extern u8 *BtlStage_GetLightColors(void);
extern void BtlStage_GetAmbient(s32 *rgb);
/* Object passes of the following files. */
extern void BtlObjAnim_SamplePose(BtlObj *obj);
extern void BtlObjAnim_UpdateEvents(BtlObj *obj);
extern void BtlObjAnim_Step(BtlObj *obj);
extern void BtlObjPose_CalcMatrices(BtlObj *obj);
extern void BtlObjFlash_Reset(BtlObj *obj);
extern void BtlObjFlash_Step(BtlObj *obj);
extern void BtlObjFade_Step(BtlObj *obj);
extern void BtlObjFade_Get(BtlObj *obj, Vec4 *out);
extern void BtlObj_UpdateFace(BtlObj *obj);
extern BtlObjPart *BtlObj_GetNode(BtlObj *obj, s32 node);
extern s32 BtlObj_IsNodeShown(BtlObj *obj, s32 arg);
extern void BtlObj_SaveNodePositions(BtlObj *obj, s32 arg);
extern void BtlObj_InitChains(BtlObj *obj);
extern void BtlObj_UpdateChains(BtlObj *obj);
/* Drawing modules. */
extern void ObjOutline_Init(void);
extern void ObjOutline_Term(void);
extern void ObjOutline_Draw(void);
extern void ObjGlow_Init(void);
extern void ObjGlow_Term(void);
extern void ObjGlow_SetAlphaTable(u8 *table);
extern void ObjGlow_Draw(void);
extern void GfxPost_CopyAlphaToDepth(void);
extern void GfxAlphaKey_Init(void);
extern void GfxAlphaKey_Term(void);
extern void GfxAlphaKey_Draw(void);

extern f32 gBtlObjFarDist[];

/* File_Request is called with a third argument (the buffer size), which it ignores. */
#define File_Request3(id, buf, size) ((void *(*)(s32, void *, s32))File_Request)(id, buf, size)

/* BtlObj_UpdateVisibility only matches when the compiler has not seen the body of BtlObjVis_GetList (it changes
   a branch-likely choice): the original had a file boundary somewhere between the two. */
extern BtlObjDrawList *BtlObjVis_GetListExt(s32 view) __asm__("BtlObjVis_GetList");

/* The flag word as bitfields: tests of two or three of these bits compile to one 64-bit load in the original,
   which is what ee-gcc does when it merges adjacent bitfield tests. */
#define FLAG_BITS(p) ((BtlObjFlagBits *)&(p)->flags)

/* Empty; called by BtlObj_Init. */
void BtlObj_InitNop(void);

/* Empty; called by BtlObj_Term. */
void BtlObj_TermNop(void);

/* Rebuilds the id -> object table from the list of objects in use. */
void BtlObj_RebuildTable(void);

/* Returns the per-view visibility block. */
BtlObjVis *BtlObjVis_Get(void);

/* Zeroes the visibility block. */
void BtlObjVis_Clear(void);

/* Claims one bit of the allocation mask; returns 0 if it was already taken. */
s32 BtlObjVis_AllocBit(s32 bit);

/* Releases one bit of the allocation mask. */
void BtlObjVis_FreeBit(s32 bit);

/* Claims the first free bit and returns its number. */
s32 BtlObjVis_AllocFreeBit(void);

/* Number of views of the last BtlObj_FinishVisibility. */
s32 BtlObjVis_GetViewCount(void);

/* Whether any object had one of the flags in any view this frame. */
s32 BtlObjVis_TestFlags(u32 mask);

/* Returns the draw list of a view. */
BtlObjDrawList *BtlObjVis_GetList(s32 view);

/* Returns the View a draw list was built for. */
void *BtlObjVis_GetView(s32 view);

/* Returns the light block. */
BtlObjLight *BtlObjLight_Get(void);

/* Sets the default light and finds the light's table in common file 2. */
void BtlObjLight_Init(void);

/* Sets the light direction and derives the half vector from it. */
void BtlObjLight_SetDir(Vec4 *dir);

/* Copies the light direction out. */
void BtlObjLight_GetDir(Vec4 *out);

/* Copies the half vector out. */
void BtlObjLight_GetHalf(Vec4 *out);

/* Sets the light colour. */
void BtlObjLight_SetColor(Vec4 *color);

/* Copies the light colour out. */
void BtlObjLight_GetColor(Vec4 *out);

/* Uploads texture 0 of the light's texture file to block 0x3D40. (The name predates the texture-file module: it
   uploads, it does not look anything up, and returns nothing.) */
void BtlObjLight_FindRes0(void);

/* Uploads texture 1 of the light's texture file to block `key`. */
void BtlObjLight_FindRes1(s32 key);

/* Returns the 0xE0-byte node pool. */
BtlObjPoolE0Work *BtlObjPoolE0_Get(void);

/* Puts all 512 nodes on the free list. */
void BtlObjPoolE0_Init(void);

/* Takes a node from the pool and resets it. */
BtlObjPoolE0 *BtlObjPoolE0_Alloc(void);

/* Returns a whole list of nodes to the pool. */
s32 BtlObjPoolE0_FreeList(SList *list);

/* Number of free 0xE0-byte nodes. */
s32 BtlObjPoolE0_GetFreeCount(void);

/* Returns the 0x70-byte node pool. */
BtlObjPool70Work *BtlObjPool70_Get(void);

/* Puts all 4 nodes on the free list. */
void BtlObjPool70_Init(void);

/* Takes a 0x70-byte node. */
BtlObjPool70 *BtlObjPool70_Alloc(void);

/* Returns a 0x70-byte node. */
s32 BtlObjPool70_Free(BtlObjPool70 *node);

/* Number of free 0x70-byte nodes. */
s32 BtlObjPool70_GetFreeCount(void);

/* Returns the third pool. */
BtlObjPool3Work *BtlObjPool3_Get(void);

/* Takes a node of the third pool. */
SListNode *BtlObjPool3_Alloc(void);

/* Returns a node to the third pool. */
s32 BtlObjPool3_Free(SListNode *node);

/* Number of free nodes of the third pool. */
s32 BtlObjPool3_GetFreeCount(void);

/* Returns the object table (the start of the work block). */
BtlObjTable *BtlObj_GetTable(void);

/* Returns the list of objects in use. */
List *BtlObj_GetUsedList(void);

/* Clears the table and puts all 12 objects on the free list, numbered in order. */
void BtlObj_InitTable(void);

/* Returns the float at table + 0x44FC4. */
f32 BtlObj_GetUnk44FC4(void);

/* Sets the float at table + 0x44FC4. */
void BtlObj_SetUnk44FC4(f32 value);

/* Number of objects in use. */
s32 BtlObj_GetCount(void);

/* Moves a free object to the used list and returns its id, or -1. */
s32 BtlObj_AllocId(void);

/* Moves the object with this id back to the free list; returns 1 if it was in use. */
s32 BtlObj_FreeId(s32 id);

/* Returns the object with this id, NULL if the id is free. */
BtlObj *func_002A4130(s32 id) {
    return gBtlObjTbl[id];
}

/* Returns the big work buffer that goes with a fighter object id. */
u8 *BtlObj_GetCharaWork(u32 id);

/* Binds an object to a loaded model and fills its header. */
void BtlObj_Setup(BtlObj *obj, s32 type, BtlResSlot *res, s32 id, s32 active);

/* Creates an object from a loaded model; returns its id or -1 when the table is full. */
s32 BtlObj_Create(s32 type, BtlResSlot *res, s32 active);

/* Releases an object; returns 1 if it existed. */
s32 BtlObj_Destroy(s32 id);

/* Creates a fighter object from a model resource slot. */
s32 BtlObj_CreateChara(s32 slot);

/* Sets an existing fighter object up again from a model resource slot (character change). */
void BtlObj_Rebind(s32 id, s32 slot);

/* Returns the model resource slot block. */
BtlResWork *BtlRes_GetWork(void);

/* Requests a character's model and its two animation files; returns the resource slot number. */
s32 BtlObj_RequestCharaModel(s32 side, s32 chara, s32 costume, s32 variant);

/* Returns the work block. */
BtlObjWork *BtlObj_GetWork(void);

/* Whether the module is initialised. */
s32 BtlObj_IsInit(void);

/* Commits a pending model reload. */
void BtlRes_CommitReloadEx(void);

/* Allocates the work block and initialises every part of it. */
void BtlObj_Init(s32 prealloc);

/* Shuts the parts down and frees the work block. */
void BtlObj_Term(void);

/* Rebuilds the object's world box from the bounds records of its model. */
void BtlObj_UpdateBounds(BtlObj *obj, BtlObjState *state);

/* Stores the object's horizontal distance from the camera in the view record. */
void BtlObj_CalcViewDist(BtlObjState *state, BtlObjView *view);

/* Distance fade: 128 up to nearDist, 0 beyond farDist, linear between; flag 8 says the fade is non-zero. */
void BtlObjView_SetFade(BtlObjView *view, f32 nearDist, f32 farDist);

/* Final alpha of each of the 16 material slots: the model's value plus the object's offset, at most 0x7F. */
void BtlObj_UpdateAlpha(BtlObj *obj);

/* Chooses the colour the object is lit with in this view from its flags. */
void BtlObj_CalcViewColor(BtlObj *obj, BtlObjView *view);

/* Returns 1 when all eight corners of the object's box are beyond the same edge of the view. */
s32 BtlObj_IsOffscreen(BtlObj *obj);

/* Fills the object's record for the view being built: flags, distance, culling, colour and fade. */
void BtlObj_UpdateView(BtlObj *obj);

/* Builds a view's draw list in three passes; the view's own fighter, when in the last pass, goes last. */
void BtlObj_BuildDrawList(BtlObjDrawList *list, s32 view);

/* Per-frame update of every object: light from the stage, animation and pose, bounds, alpha. */
void BtlObj_UpdateAll(void);

/* Builds every object's record and the draw list for one view (the current gBtlCamView). */
void BtlObj_UpdateVisibility(s32 view);

/* Combines the view records into per-object and global flags, then sends the alpha table. */
void BtlObj_FinishVisibility(s32 split);

/* Writes the object's 15 alpha bytes into its model's row of the alpha table. */
void BtlObj_FillAlphaRow(u8 *table, BtlObj *obj);

/* Initialises the three drawing modules objects are drawn with. */
void BtlObj_InitDraw(void);

/* Shuts the three drawing modules down. */
void BtlObj_TermDraw(void);

/* Sets the full-screen scissor and starts a frame of the drawing modules. */
void BtlObj_BeginDraw(void);

/* Builds the 0x100-byte alpha table from every active object and hands it to the drawing module. */
void BtlObj_UploadAlphaTable(void);

/* Takes a free fixed slot (the two with preallocated buffers). */
BtlResSlot *BtlRes_AllocFixed(void);

/* Takes a free heap slot. */
BtlResSlot *BtlRes_AllocSlot(void);

/* Finds a heap slot by number. */
BtlResSlot *BtlRes_FindSlot(s32 number);

/* Copies buffer, size and id of a file record. */
void BtlRes_CopyFile(BtlResFile *dst, BtlResFile *src);

/* Exchanges buffer, size and id of two file records. */
void BtlRes_SwapFile(BtlResFile *a, BtlResFile *b);

/* Sets which file a record holds: an id, none (negative), or unchanged (BTL_RES_ID_KEEP). */
void BtlRes_SetFileId(BtlResFile *file, s32 id);

/* Sets the three file ids of a slot. */
void BtlRes_SetIds(BtlResSlot *slot, s32 model, s32 anim0, s32 anim1);

/* Frees a heap-loaded file; returns 1 if there was one. */
s32 BtlRes_FreeFile(BtlResFile *file);

/* Queues the read of a file: into a new heap buffer (fromHeap == 1) or into the record's own buffer. */
void BtlRes_LoadFile(BtlResFile *file, s32 fromHeap);

/* After a reload has been read: swaps the new model buffer into the fixed slot. */
void BtlRes_CommitReload(void);

/* Clears the slots; with prealloc, allocates the buffers of the two fixed slots and the spare model buffer. */
void BtlRes_Init(s32 prealloc);

/* Frees every slot and the preallocated buffers. */
void BtlRes_Term(void);

/* Takes a slot and queues its files; returns the slot number or -1. */
s32 BtlRes_Request(s32 fixed, s32 model, s32 anim0, s32 anim1);

/* Releases a heap slot and its files. Fixed slots are never released. */
void BtlRes_Free(s32 number);

/* Returns the slot with this number, NULL if there is none. */
BtlResSlot *BtlRes_GetSlot(s32 number);

/* Character change: queues new files for a fixed slot. The model goes to the spare buffer and is swapped in
   by BtlRes_CommitReload; the animation files are read over the old ones unless only the model changes. */
void BtlRes_Reload(s32 number, s32 model, s32 anim0, s32 anim1);

/* Same as BtlRes_CommitReload (battle_load.c calls this copy). */
void BtlRes_CommitReload2(void);

/* Loads one model into a caller-owned slot record (not one of the work block's). */
void BtlRes_LoadSingle(s32 fromHeap, BtlResSlot *slot, s32 model);

/* Frees the files of a caller-owned slot record. */
void BtlRes_FreeSingle(BtlResSlot *slot);
