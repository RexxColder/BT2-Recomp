#define Heap_Free func_0028BB60  /* fix_targets */ /* the original uses 0x28bb60 here */
#include "common.h"
/*
 * The Flash-like movie player (0x10AD58..0x10EC18). The data is a converted SWF: see include/sys/gfxm_c.h and
 * docs. Continues src/sys/gfxm_b_c.c (the low-level readers), very likely the same original object.
 * Proper name: flash.c.
 */
#include "sys/gfxm_c.h"
#include "sys/heap.h"
#include "sys/dma.h"
#include "sys/gfx.h"
#include "sys/gfxm_b_b.h"

extern void *memcpy(void *dst, const void *src, u32 size);
extern void *memset(void *dst, s32 c, u32 n);
extern s32 strcmp(const char *a, const char *b);
extern u32 strlen(const char *s);
extern s32 atoi(const char *s);

void FlashTl_TagPlace(FlashTl *tl, u8 *data, s32 *ofs);
void FlashTl_TagPlace2(FlashTl *tl, u8 *data, s32 *ofs);
void FlashTl_TagRemove(FlashTl *tl, u8 *data, s32 *ofs);
void FlashTl_TagRemove2(FlashTl *tl, u8 *data, s32 *ofs);
void FlashTl_TagActions(FlashTl *tl, u8 *data, s32 *ofs);
void FlashSlot_SetShape(FlashSlot *slot, u16 id, FlashMtx *mtx, FlashCxform *cx, Flash *flash);
void FlashSlot_SetClip(FlashSlot *slot, u16 id, char *name, FlashMtx *mtx, FlashCxform *cx, Flash *flash);
void FlashSlot_Clear(FlashSlot *slot);
void FlashSlot_Move(FlashSlot *slot, FlashMtx *mtx, FlashCxform *cx);
void FlashShape_Free(FlashShape *shape);
void FlashClip_Reset(FlashClip *clip, s32 arg);

/* Sets a colour transform to the identity. */
void Flash_CxformIdentity(FlashCxform *cx);

/* Reads a bit-packed colour transform at data + *ofs: a flag byte (bits 0..3 multipliers present, 4..7 offsets
   present), a 4-bit field width, then the fields (multipliers in 8.8). Leaves *ofs on the next whole byte. */
void Flash_ReadCxform(u8 *data, FlashCxform *cx, s32 *ofs);

/* Runs the tag list of one frame block (name, u16 size, then tags: u16 code + data, ended by code 1 = ShowFrame).
   A block of size 0 is the end of the timeline: stops and steps back onto the last frame. */
void FlashTl_RunFrame(FlashTl *tl, u8 *frame);

/* Tag 4 (PlaceObject): u16 depth, u8 kind (4 shape, 6 sprite), u16 id, matrix, and for a sprite a colour transform. */
void FlashTl_TagPlace(FlashTl *tl, u8 *data, s32 *ofs);

/* Tag 26 (PlaceObject2): u8 flags (2 new object, 4 matrix, 8 colour transform, 0x20 name), u16 depth; a new object
   adds u8 kind and u16 id. Without flag 2 the object already at that depth is moved. */
void FlashTl_TagPlace2(FlashTl *tl, u8 *data, s32 *ofs);

/* Tag 5 (RemoveObject): u16 depth, u8 kind, u16 id: frees the shape or resets the sprite at that depth. */
void FlashTl_TagRemove(FlashTl *tl, u8 *data, s32 *ofs);

/* Tag 28 (RemoveObject2): u16 depth: empties that depth. */
void FlashTl_TagRemove2(FlashTl *tl, u8 *data, s32 *ofs);

/* Action list (tag 12) while a jump replays earlier frames: every action is skipped except GetURL "pad". */
void FlashTl_SkipActions(FlashTl *tl, u8 *data, s32 *ofs);

FlashClip *FlashClipList_FindByName(FlashClipList *list, char *name);

/* Tag 12 (DoAction): runs SWF actions until the end code 0. 0x81 GotoFrame, 4 NextFrame, 5 PrevFrame, 6 Play,
   7 Stop, 0x83 GetURL (the game's command channel), 0x8A WaitForFrame (skipped), 0x8B SetTarget, 0x8C GotoLabel. */
void FlashTl_TagActions(FlashTl *tl, u8 *data, s32 *ofs);

/* Sets a timeline up on a frame record (root: tag 7, sprite: a record of tag 6) and allocates its depth slots. */
void FlashTl_Init(FlashTl *tl, u8 *record, Flash *owner);

/* Frees the depth slots and clears the timeline. */
void FlashTl_Term(FlashTl *tl);

/* Back to frame 0, stopped, every depth emptied. The second argument is not used. */
void FlashTl_Rewind(FlashTl *tl, s32 unused);

void FlashSlot_Advance(FlashSlot *slot, u32 count);

/* Runs `count` ticks: a pending jump first replays the frames up to the target (from 0, or from the frame the
   jump left when FLASH_TL_KEEP), then the current frame's tags run and the play head steps. `children` ticks the
   sprites placed on it after each frame (when 0 they are ticked once at the end); `force` does so even when this
   timeline is stopped. */
void FlashTl_Advance(FlashTl *tl, u32 count, u8 children, u8 force);

void FlashSlot_Draw(FlashSlot *slot, FlashProp *prop, Flash *flash);

/* Draws every depth, lowest first. `prop` is the drawing state of the sprite this timeline belongs to (NULL: root). */
void FlashTl_Draw(FlashTl *tl, FlashProp *prop);

/* Jumps to a frame label. `restart` rebuilds the display list from frame 0, else from the current frame. */
void FlashTl_GotoLabel(FlashTl *tl, char *label, u8 restart);

/* Moves the play head by `step` frames and plays; any step but +1 goes through the jump path. */
void FlashTl_StepFrames(FlashTl *tl, s32 step);

FlashShape *FlashShape_Create(FlashShapePool *pool, u16 id, FlashMtx *mtx, FlashCxform *cx);
FlashClip *FlashClip_Start(FlashClipList *list, u16 id, char *name, FlashMtx *mtx, FlashCxform *cx);
void FlashShape_Set(FlashShape *shape, FlashMtx *mtx, FlashCxform *cx);
void FlashClip_Set(FlashClip *clip, FlashMtx *mtx, FlashCxform *cx);

/* Puts a shape on a depth, replacing the shape that was there. */
void FlashSlot_SetShape(FlashSlot *slot, u16 id, FlashMtx *mtx, FlashCxform *cx, Flash *flash);

/* Puts a sprite on a depth, replacing the sprite that was there. */
void FlashSlot_SetClip(FlashSlot *slot, u16 id, char *name, FlashMtx *mtx, FlashCxform *cx, Flash *flash);

/* Empties a depth: frees the shape, marks the sprite unused (its state is kept). */
void FlashSlot_Clear(FlashSlot *slot);

/* Gives what is on a depth a new matrix and / or colour transform (NULL: keep). */
void FlashSlot_Move(FlashSlot *slot, FlashMtx *mtx, FlashCxform *cx);

/* Ticks the sprite on a depth. */
void FlashSlot_Advance(FlashSlot *slot, u32 count);

void FlashShape_Draw(FlashShape *shape, FlashProp *prop, Flash *flash);

static inline s32 Flash_Clamp255(s32 v);

static inline s16 Flash_ClampAdd(s32 v);

/* Draws what is on a depth: the shape, then the sprite. The sprite's drawing state is combined with its
   parent's (matrix product, colour transforms multiplied and added, the parent's overrides applied). */
void FlashSlot_Draw(FlashSlot *slot, FlashProp *parent, Flash *flash);

/* Returns its argument: every screen Y goes through it (a stripped vertical adjustment). */
f32 FlashDraw_AdjustY(f32 y);

/* Queues the upload of texture `index` of an image's entry table to block `tbp` and its CLUT to the blocks behind
   it (+0x40), and returns the TEX0 value. Entry `index` holds the CLUT; when it has no pixels of its own the
   pixels are entry 0's (several palettes for one picture). */
u64 FlashDraw_UploadTex(FlashTex *tex, s32 index, s32 tbp);

/* XYZ2 of a screen point: 12.4 fixed point, window origin at (1792, 1824), Z 0. */
#define FLASH_XY(x, y) ((s64)((s32)((x) * 16.0f) + ox) | ((s64)((s32)(FlashDraw_AdjustY(y) * 16.0f) + oy) << 16))
#define FLASH_RGBA(q) ((s64)(q)->rgba[0] | ((s64)(q)->rgba[1] << 8) | ((s64)(q)->rgba[2] << 16) | ((s64)(q)->rgba[3] << 24))

/* Writes a textured triangle strip of four vertices (REGLIST: RGBAQ, TEX0, PRIM, then UV / XYZ2 pairs) and
   returns the end of the packet. The texture rectangle is shrunk by one texel on each side unless flipped. */
u64 *FlashDraw_PutSprite(u64 *p, FlashQuad *q, u64 tex0);

/* Draws an untextured quad in its colour. */
void FlashDraw_FlatQuad(FlashQuad *q);

/* Draws a textured quad through the frame buffer's alpha plane. `set`: write only alpha (builds the mask).
   Otherwise: write only colour, where the texture's alpha is above 0x3C, blended by the alpha already there. */
void FlashDraw_MaskQuad(FlashQuad *q, u64 tex0, s32 set);

/* Draws one quad: nothing when its alpha is 0, flat without a texture, else uploads the texture to block 0x3000
   and draws it normally or through the alpha-plane mask. */
void FlashDraw_Quad(FlashTex *tex, FlashQuad *q);

/* Brings a shape's quad to the screen: the shape's matrix and colour transform, then the owning sprite's drawing
   state (matrix, position / scale / colour / alpha overrides, texture rectangle, draw flags), then the movie's
   screen offset. Only three corners are transformed; the fourth closes the parallelogram. */
void FlashDraw_TransformQuad(FlashQuad *q, FlashMtx *mtx, FlashCxform *cx, FlashProp *prop, s32 *ofs);

void FlashClipList_Init(FlashClipList *list, Flash *flash);
void FlashClipList_Term(FlashClipList *list);
void FlashClipList_Reset(FlashClipList *list);
void FlashClipList_FindRef(FlashClipList *list, char *parent, char *name, FlashRef *out);
void FlashShapePool_Init(FlashShapePool *pool, u32 count);
void func_0026F738(FlashShapePool *pool);
void FlashShapePool_Clear(FlashShapePool *pool);

/* Sets a movie up on a FOD file and its textures: allocates the root timeline, the sprite instances and the
   shape pool (one shape per depth of every timeline). The object must be zeroed or freshly destroyed. */
void Flash_Create(Flash *flash, u8 *file, FlashTex **tex);

/* Frees everything Flash_Create allocated. */
void Flash_Destroy(Flash *flash);

/* One tick: clears the event bits of the last tick and, while playing, runs `speed` frames of the root. */
/* The play test reads the flags back through a pointer to the field that is set AFTER the masking store (the
   same habit as `speed`): the compiler knows the value but keeps it as a second register, which is the
   original's `and v1,v1,v0 / move v0,v1 / andi v0,v0,1`. Testing a local or the field itself gives
   `andi v0,v1,1` (one instruction short), and a pointer initialised at its declaration makes the function
   two instructions longer. Found from a decomp-permuter candidate
   (`if ((*(p = &flash->flags) & ~FLASH_END) & FLASH_PLAY)`), of which only the late pointer is needed. */
void Flash_Advance(Flash *flash);

/* Draws the movie (after the default drawing environment) unless it is hidden. */
void Flash_Draw(Flash *flash);

/* Back to the first frame, playing, every other flag cleared. Unless `keepClips`, every sprite instance and
   shape is cleared as well. */
void Flash_Reset(Flash *flash, s32 keepClips);

/* Starts playing at `speed` frames per tick. */
void Flash_Play(Flash *flash, s32 speed);

/* Stops Flash_Advance from running the timelines. */
void Flash_Stop(Flash *flash);

/* Sets the screen offset added to everything drawn. */
void Flash_SetOffset(Flash *flash, s32 x, s32 y);

/* Sets or clears bits of Flash.flags. */
void Flash_SetFlag(Flash *flash, u32 mask, u8 on);

/* Jumps the root timeline to a frame label ("fl_..."). */
void Flash_GotoLabel(Flash *flash, char *label, u8 restart);

/* Moves the root timeline by `step` frames. */
void Flash_StepFrames(Flash *flash, s32 step);

/* Looks a sprite instance up by name ("mc_..."), optionally among the children of the instance called `parent`.
   out->index is -1 when there is none. (Existing name; it finds a clip, not a label.) */
void Flash_FindLabel(Flash *flash, char *parent, char *name, FlashRef *out);

/* The clip-list functions of the next file (src/sys/gfxm_d.c), declared here as this file calls them. */
extern void FlashClipList_GotoLabel(FlashClipList *list, FlashRef *ref, char *label);
extern void FlashClipList_SetPreDraw(FlashClipList *list, FlashRef *ref, void *fn, void *arg);
extern void FlashClipList_SetPostDraw(FlashClipList *list, FlashRef *ref, void *fn, void *arg);
extern void FlashClipList_SetDrawOver(FlashClipList *list, FlashRef *ref, void *fn, void *arg);
extern void FlashClipList_SetFlags(FlashClipList *list, FlashRef *ref, s32 mask, u8 on);
extern void FlashClipList_SetOverride(FlashClipList *list, FlashRef *ref, s32 mask, u8 on);
extern void FlashClipList_SetOffset(FlashClipList *list, FlashRef *ref, s32 x, s32 y);
extern void FlashClipList_SetScale(FlashClipList *list, FlashRef *ref, f32 x, f32 y);
extern void FlashClipList_SetAlpha(FlashClipList *list, FlashRef *ref, f32 alpha);
extern void FlashClipList_SetColor(FlashClipList *list, FlashRef *ref, f32 value);
extern void FlashClipList_SetTex(FlashClipList *list, FlashRef *ref, s32 user);
extern void FlashClipList_SetUv(FlashClipList *list, FlashRef *ref, void *rect);
extern void FlashClipList_GetPos(FlashClipList *list, FlashRef *ref, s32 *x, s32 *y);
extern f32 FlashClipList_GetAlpha(FlashClipList *list, FlashRef *ref);
void FlashClipList_Play(FlashClipList *list, FlashRef *ref);
void FlashClipList_Stop(FlashClipList *list, FlashRef *ref);

/* Jumps a clip (and its namesakes) to a label of its own timeline. */
void Flash_ClipGotoLabel(Flash *flash, FlashRef *ref, char *label);

/* Sets a clip's callback run before its children are drawn (FlashClip.preDraw / preArg). */
void Flash_ClipSetCallbackA(Flash *flash, FlashRef *ref, void *fn, void *arg);

/* Sets a clip's callback run after everything of it is drawn (FlashClip.postDraw / postArg). */
void Flash_ClipSetCallbackB(Flash *flash, FlashRef *ref, void *fn, void *arg);

/* Sets a clip's callback run after its children, which gets the clip's drawing state (FlashClip.drawOver). */
void Flash_ClipSetCallbackC(Flash *flash, FlashRef *ref, void *fn, void *arg);

/* Sets or clears properties of a clip, one bit of `props` each: 1 playing, 2 visible, 4 flip x, 8 flip y,
   0x10 no screen offset, 0x20 additive, 0x40 subtractive, 0x80 masked, 0x100 mask writer, 0x200 repeat,
   0x400 keeps running while its parent is stopped. */
s32 Flash_ClipSetFlags(Flash *flash, FlashRef *ref, s32 props, u8 on);

/* Gives a clip a position offset. */
void Flash_ClipSetOffset(Flash *flash, FlashRef *ref, s32 x, s32 y);

/* Gives a clip a scale; negative values are refused. */
void Flash_ClipSetScale(Flash *flash, FlashRef *ref, f32 x, f32 y);

/* Gives a clip an alpha multiplier; a negative value is refused. */
void Flash_ClipSetAlpha(Flash *flash, FlashRef *ref, f32 alpha);

/* Gives a clip a colour multiplier (r, g, b); a negative value is refused. */
void Flash_ClipSetColor(Flash *flash, FlashRef *ref, f32 color);

/* Makes a clip draw with texture `tex` of its image's texture file (a palette or a frame of a strip). */
void Flash_ClipSetTex(Flash *flash, FlashRef *ref, s32 tex);

/* Replaces a clip's texture rectangle (four texel coordinates). */
void Flash_ClipSetUv(Flash *flash, FlashRef *ref, void *rect);

/* Returns a clip's screen position. */
void Flash_ClipGetPos(Flash *flash, FlashRef *ref, s32 *x, s32 *y);

/* Returns a clip's alpha, 0 when the reference is empty. */
f32 Flash_ClipGetAlpha(Flash *flash, FlashRef *ref);

/* Allocates the pool of placed shapes. */
void FlashShapePool_Init(FlashShapePool *pool, u32 count);

/* Frees the pool's storage. */
void func_0026F738(FlashShapePool *pool) {
    if (pool->items != NULL) {
        Heap_Free(pool->items);
        pool->items = NULL;
    }
}

/* Frees every shape of the pool. */
void FlashShapePool_Clear(FlashShapePool *pool);

/* Returns a cleared free shape, or NULL when the pool is full. */
FlashShape *FlashShapePool_Alloc(FlashShapePool *pool);

/* Places shape record `id` with a matrix and a colour transform (NULL: identity). */
FlashShape *FlashShape_Create(FlashShapePool *pool, u16 id, FlashMtx *mtx, FlashCxform *cx);

/* Gives a shape back to the pool. */
void FlashShape_Free(FlashShape *shape);

/* Replaces a shape's matrix and / or colour transform (NULL: keep). */
void FlashShape_Set(FlashShape *shape, FlashMtx *mtx, FlashCxform *cx);

/* Draws a placed shape: each quad of its record (tag 4), textured with its image's texture file or flat when
   the image index is negative. A quad whose image has no texture file is skipped. */
void FlashShape_Draw(FlashShape *shape, FlashProp *prop, Flash *flash);

/* Makes one sprite instance per record of the sprite list (tag 2), each on its own frame record of tag 6. */
void FlashClipList_Init(FlashClipList *list, Flash *flash);

/* Frees every instance's depth slots and the list. */
void FlashClipList_Term(FlashClipList *list);

/* Ticks every instance's timeline `count` times. Not called by anything in this file. */
void FlashClipList_Advance(FlashClipList *list, u32 count);

/* Resets every instance. */
void FlashClipList_Reset(FlashClipList *list);

/* Returns the first unused instance of sprite `id`, or NULL. */
FlashClip *FlashClipList_FindFree(FlashClipList *list, u16 id);

/* Places sprite `id` under an instance name: takes a free instance, makes it used and visible, resets its
   overrides and callbacks and lets its timeline play (from the frame a jump left pending, if any). */
FlashClip *FlashClip_Start(FlashClipList *list, u16 id, char *name, FlashMtx *mtx, FlashCxform *cx);

/* Replaces an instance's matrix and / or colour transform (NULL: keep). */
void FlashClip_Set(FlashClip *clip, FlashMtx *mtx, FlashCxform *cx);

/* Clears an instance: name, flags, overrides, callbacks, and its timeline back to frame 0. */
void FlashClip_Reset(FlashClip *clip, s32 arg);

/* Returns the first instance with the given name, or NULL. */
FlashClip *FlashClipList_FindByName(FlashClipList *list, char *name);

/* Fills a reference to the instances called `name`. With `parent`: the one placed on a depth of the first
   instance called `parent`. Without: the first in the list, counting the further ones in out->more. */
void FlashClipList_FindRef(FlashClipList *list, char *parent, char *name, FlashRef *out);

/* Lets the referenced instance and its namesakes play. */
void FlashClipList_Play(FlashClipList *list, FlashRef *ref);

/* Stops the referenced instance and its namesakes. */
void FlashClipList_Stop(FlashClipList *list, FlashRef *ref);
