/*
 * This file is 0x24BBE8..0x250B28: bobj_a.c + bobj_b.c, merged at integration (the second part starts at the
 * separator comment further down; btl_obj.c is in front, bobj_b_b.c follows).
 *
 * Battle object, second part (0x24BBE8..0x24F1F0): the animation player of a battle object, the events and attack
 * volumes it produces, the body volumes, the object transform and node matrices, the flash / fade timers and the
 * face animation. Layouts and the animation file format are in include/battle/bobj_a.h.
 *
 * One frame of an object that BtlObj_UpdateAll steps itself (anim.manual == 0; effect models):
 *   BtlObj_SaveNodePositions, BtlObjAnim_Step, BtlObjAnim_SamplePose, BtlObjAnim_UpdateEvents,
 *   BtlObjPose_CalcMatrices, BtlObj_UpdateChains, BtlObjPose_CalcMatrices again.
 * A fighter's object has anim.manual == 1 (set by BtlObjAnim_Play); the fighter code moves anim.frame itself and
 * calls the same passes.
 */
#include "common.h"
#include "battle/bobj_a.h"

extern void *memset(void *dst, s32 c, u32 n);
extern s32 memcmp(const void *a, const void *b, u32 n);
extern s32 rand(void);

extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec3_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Mtx_MulVec4(Vec4 *dst, Mtx44 *m, Vec4 *v);
extern void Bpe_Decode(void *src, void *dst, s32 *size);
extern f32 BtlObj_GetUnk44FC4(void);
extern void Res_RelocateOffsets(void *out, void *base);

/* The battle work block: only the 64-bit flag word is read here (0x100 = pause). */
typedef struct BobjBattleWork {
    /* 0x0000 */ u8 unk00[0x19F0];
    /* 0x19F0 */ u64 flags;
} BobjBattleWork;
extern BobjBattleWork *Battle_GetWork(void);

/* VU0 helpers of src/sys: matrix product, matrix copy, inverse of a rigid matrix, xyz copy (w kept),
   dst = a * t + b * (1 - t). */
extern void Mtx_Mul(Mtx44 *dst, Mtx44 *a, Mtx44 *b);
extern void Mtx_Copy(Mtx44 *dst, Mtx44 *src);
extern void Mtx_InverseRT(Mtx44 *dst, Mtx44 *src);
extern void Vec3_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Lerp(Vec4 *dst, Vec4 *a, Vec4 *b, f32 t);
/* The VU0 matrix stack: the current matrix lives in vf16..vf19, the stack in VU0 data memory at vi15.
   0x120A98 current = identity, 0x120AB0 push, 0x120AE0 pop n, 0x120B18 empty the stack, 0x120B80 load,
   0x120B98 store, 0x120C18 translate, 0x120F00 rotate by Euler angles (z, x, y), 0x120F88 scale. */
extern void Vu0Cur_LoadIdentity(void);
extern void Vu0Cur_Push(void);
extern void Vu0Cur_PopN(s32 count);
extern void Vu0Cur_ResetStack(void);
extern void Vu0Cur_LoadMtx(Mtx44 *m);
extern void Vu0Cur_StoreMtx(Mtx44 *m);
extern void Vu0Cur_Translate(Vec4 *v);
extern void Vu0Cur_RotateZXY(Vec4 *angles);
extern void Vu0Cur_ScaleDiagUniform(f32 scale);
/* Collision shapes: box grow by a 16-byte point / a 12-byte point, box of a sphere / of an oriented box, box grow
   by a sphere centre, sphere and oriented box constructors. */
extern void StgAabb_SetEmpty(BobjAabb *box);
extern void ColBox_AddPoint(BobjAabb *box, Vec4 *point);
extern void ColBox_AddPointKeepW(BobjAabb *box, f32 *point);
extern void ColObb_Init(BobjObb *box, Vec4 *center, f32 x, f32 y, f32 z);
extern void ColObb_Update(BobjObb *box, Mtx44 *m);
extern void ColBounds_OfSphere(BobjAabb *out, BobjSphere *sphere);
extern void ColBounds_AddSphere(BobjAabb *box, Vec4 *point);
extern void ColBounds_OfObb(BobjAabb *out, BobjObb *box);
extern void ColSphere_Set(BobjSphere *out, Vec4 *center, f32 radius);
/* The second part of this file (formerly bobj_b.c): aliased declarations with this part's types, because the
   second part defines these functions with its own (a cast macro would rewrite the definitions). */
extern BobjBone *BtlObj_FindBound_a(BobjObj *obj, s32 node) __asm__("BtlObj_FindBound");
#define BtlObj_FindBound BtlObj_FindBound_a
extern BobjPart *BtlObj_GetNode_a(BobjObj *obj, s32 node) __asm__("BtlObj_GetNode");
#define BtlObj_GetNode BtlObj_GetNode_a
extern BobjPart *BtlObj_GetNodeByCode_a(BobjObj *obj, s32 code) __asm__("BtlObj_GetNodeByCode");
#define BtlObj_GetNodeByCode BtlObj_GetNodeByCode_a
extern s32 BtlObj_IsJawActive_a(BobjObj *obj) __asm__("BtlObj_IsJawActive");
#define BtlObj_IsJawActive BtlObj_IsJawActive_a
extern void BtlObj_GetJawRot_a(BobjObj *obj, Quat *out) __asm__("BtlObj_GetJawRot");
#define BtlObj_GetJawRot BtlObj_GetJawRot_a

/* 0, 0, 0, 1: the zero translation and the identity rotation. */
extern Vec4 D_002EC2C0;
/* Reference translation of each node (71 x {x, y, z}) that motions are authored against: the first 0x360 bytes of
   this object's .rodata (0x2F2420..0x2F2780), emitted by the INCLUDE_RODATA below the declarations. */
extern f32 D_002F2420[BOBJ_NODE_MAX * 3];
/* Talk patterns {frame, mouth shape} (7 and 5 steps) and jaw rotation tracks {x, y, z, frame} (4 keys each). */
extern BobjTalkStep D_002C6C20[];
extern BobjTalkStep D_002C6C40[];
extern BobjJawKey D_002C6C58[];
extern BobjJawKey D_002C6C98[];
extern BobjJawKey D_002C6CD8[];
extern BobjJawKey D_002C6D18[];
extern BobjJawKey D_002C6D58[];
extern BobjJawKey D_002C6D98[];
extern BobjJawKey D_002C6DD8[];
extern BobjJawKey D_002C6E18[];


#define TRACK_AT(anim, off) ((BobjTrack *)((u16 *)(anim) + (off) * 2))
#define QUAT64(q) ((u64)(q).lo + ((u64)(q).hi << 32))

/* Moves the translation keys of a motion from the skeleton it was made for to this object's skeleton: subtracts
   the source rest translation, scales y by the height ratio and adds this object's rest translation. The source
   is the built-in reference table (useTable), the character's own reference pose (useOwn) or another object. */
void BtlObjAnim_Retarget(BobjAnim *anim, BobjObj *obj, BobjObj *other, s32 useTable, s32 useOwn);

/* Samples a rotation-only track at a frame. The search starts at the key found last time. */
void BtlObjAnim_SampleRot(BobjTrack *trk, Quat *out, u16 *cursor, f32 frame);

/* Samples a full (translation + rotation) track at a frame. */
/* A key's frame as a float. The original had a helper like this one (inlined): each use of the previous key's
   frame computes `key - 1` and loads the frame again, which only an inlined argument reproduces. */
static inline f32 BobjKey_GetFrame(BobjKey *key);

void BtlObjAnim_SamplePosRot(BobjTrack *trk, Vec4 *pos, Quat *rot, u16 *cursor, f32 frame);

/* Returns motion `anim` of an object: ids below 0x19E are decompressed into buf, the others (the model's own
   motions, which follow in the same table) are returned in place. */
BobjAnim *BtlObjAnim_Load(BobjObj *obj, void *buf, s32 anim, s32 *size);

/* Initial player state: default step, identity extra rotations, volume scale 1. */
void BtlObjAnim_Init(BobjObj *obj);

/* Starts a blend of `seconds` from the current pose: remembers every node's translation and rotation. */
void BtlObjAnim_StartBlend(BobjObj *obj, f32 seconds);

/* Zeroes the chosen axes of every translation key of the root node's track. */
void BtlObjAnim_ZeroRootAxes(BobjAnim *anim, s32 x, s32 y, s32 z);

/* Makes the root node's track start at the origin: subtracts the first key's translation from every key. */
void BtlObjAnim_RebaseRoot(BobjAnim *anim) {
    BobjVec3 first;
    BobjTrack *trk;
    BobjKey *keys;
    s32 n;
    s32 i;

    if (anim->track[0] == 0) {
        return;
    }
    trk = TRACK_AT(anim, anim->track[0]);
    if (BOBJ_TRACK_ROT_ONLY(trk)) {
        return;
    }
    keys = trk->u.key;
    n = trk->count;
    first.x = keys[0].x;
    first.y = keys[0].y;
    first.z = keys[0].z;
    for (i = 0; i < n; i++) {
        keys[i].x -= first.x;
        keys[i].y -= first.y;
        keys[i].z -= first.z;
    }
}

/* Replaces every rotation key of a node's track by the packed identity. */
void BtlObjAnim_ClearNodeRot(BobjAnim *anim, s32 node);

/* Fills every node's local translation and rotation for the current frame: layer 0, then layer 1 mixed in by
   anim.mix, then the blend from the pose stored by BtlObjAnim_StartBlend (not for node 0). */
void BtlObjAnim_SamplePose(BobjObj *obj);

/* Reads the events of layer 0 for this frame: the hit window that is open (its volume and nodes), the number of
   hit windows, and up to eight distinct events whose frame lies in (previous frame, frame]. */
void BtlObjAnim_UpdateEvents(BobjObj *obj);

/* Sets the frames advanced per update. */
void BtlObjAnim_SetStep(BobjObj *obj, f32 step);

/* Starts motion `anim` on a layer. Layer 0 with reset restarts at frame 0; without it the frame is kept
   (clamped to the new length). The owner steps the object from now on (anim.manual). */
void BtlObjAnim_Play(BobjObj *obj, s32 layer, s32 anim, s32 reset);

/* Starts motion `anim` of ANOTHER object's table on layer 0 (frame 0), retargeted to this object. */
void BtlObjAnim_PlayFrom(BobjObj *obj, BobjObj *other, s32 anim, s32 useTable);

/* One decoded motion buffer. */
typedef struct BobjLayerBuf {
    u8 b[BOBJ_WORK_LAYER_SIZE];
} BobjLayerBuf;

/* Layer 1 becomes layer 0: copies its decoded motion, id and length, and restarts at frame 0. */
void BtlObjAnim_PromoteLayer(BobjObj *obj);

/* Starts motion `anim` (0..0x19D) on layer 0 and lets BtlObj_UpdateAll step it in the given mode. */
void BtlObjAnim_PlayAuto(BobjObj *obj, s32 anim, s32 mode);

/* Starts one of the eight motions of the model file itself, in the given mode. */
void BtlObjAnim_PlayModel(BobjObj *obj, s32 anim, s32 mode);

/* Advances the frame of a self-stepped object by anim.step: once (stops on the last frame) or looping. */
void BtlObjAnim_Step(BobjObj *obj);

/* Whether an event with any of the mask's attribute bits fell in this frame's interval. */
s32 BtlObjAnim_TestEvent(BobjObj *obj, u64 mask);

/* OR of the arguments of this frame's events that have any of the mask's attribute bits. */
u32 BtlObjAnim_GetEventArg(BobjObj *obj, u64 mask);

/* Lowest set bit of an event argument -> model node id (the order of the tests is the priority). */
s32 BtlObjAnim_MaskToNode(u32 mask);

/* Scans every event of a layer's motion that has any of the mask's attribute bits, relative to the current frame:
   what 0 = frame of the first, 1 = frame of the first one still ahead, 2 = frame of the last, 3 = how many,
   4 = how many still ahead, 5 = how many reached, 6 / 7 / 8 = the argument of 0 / 1 / 2. Frames are -1 and
   arguments 0 when there is none. */
s32 BtlObjAnim_QueryEvent(BobjObj *obj, u64 mask, s32 layer, u32 what);

/* Returns the play mode of a self-stepped object (0 = finished / none). */
s32 BtlObjAnim_GetMode(BobjObj *obj);

/* Whether the object has body volumes: a fighter (type 0) whose model carries body data. */
s32 BtlObjBody_Exists(BobjObj *obj);

/* Swaps the two body sphere records (not while the battle is paused). */
void BtlObjBody_Swap(BobjBody *body);

/* Places an oriented box: stores the matrix, its rows as axes and centre, and the eight world corners. */
void BtlObjObb_SetMtx(BobjObb *box, Mtx44 *m);

/* Stores a body part's world centre. */
void BtlObjBody_SetCenter(Vec4 *dst, Vec4 *src);

/* Rebuilds the body sphere: centred on node 0 in x / z, at node 0x11's height minus 1.2, never lower than
   radius + 1.2 above node 0 (+Y is down). */
void BtlObjBody_UpdateSphere(BobjObj *obj, BobjBody *body);

/* Rebuilds every body part's box from its node matrix, and the two bounding boxes of the body. */
void BtlObjBody_UpdateParts(BobjBody *body);

/* Clears the body block and fills it from the model: sizes, sphere radius, and each body part's node. */
void BtlObjBody_Init(BobjObj *obj);

/* Rebuilds the body volumes from the node matrices: the sphere (parts == 0) or the part boxes. Declared with a
   result it never sets: the calls are not tail calls in the original. */
s32 BtlObjBody_Update(BobjObj *obj, s32 parts);

/* Start of a fighter's collision frame: the stage contact word moves to "previous" and is cleared, and the body
   sphere records are swapped. */
void BtlObjBody_BeginFrame(BobjObj *obj);

/* Marks the body as teleported (body.reset) and swaps the sphere records. */
void BtlObjBody_Reset(BobjObj *obj);

/* Puts both body sphere records at a position (no sweep from the old one). */
void BtlObjBody_Warp(BobjObj *obj, Vec4 *pos);

/* Rebuilds the body part boxes and this frame's attack volumes: one sphere or oriented box per attack node of
   the open hit window, plus their bounding box. Clears the top byte of the stage contact word. */
void BtlObjHit_BuildVolumes(BobjObj *obj);

/* Local rotation matrix of a node. On a fighter, node 2 gets the extra rotation look.node2, nodes 0x2E / 0x2F
   are slerped towards look.node2E / node2F, and node 0x31 (the jaw) takes the face's rotation while it talks. */
void BtlObjPose_GetNodeMtx(BobjObj *obj, Mtx44 *out, BobjPart *part);

/* Resets the transform: position and rotation 0, scale 1, matrix rebuilt. */
void BtlObjXf_Reset(BobjObj *obj);

/* Rebuilds the object's matrix and its inverse from pos / rot / scale. The model faces -Z, so the yaw is turned
   by pi. */
void BtlObjXf_Update(BobjObj *obj);

/* Sets the object's matrix directly, and its inverse. */
void BtlObjXf_SetMtx(BobjObj *obj, Mtx44 *m);

/* World matrix of every node, parents first, on the VU0 matrix stack: node = local * parent. Stores the root
   node's world position in xf.rootPos. */
void BtlObjPose_CalcMatrices(BobjObj *obj);

/* Whether the object has the fighter buffer. */
s32 BtlObj_HasWork(BobjObj *obj);

/* Returns the flash / fade block of a fighter object, NULL for other objects. */
BobjFlash *BtlObjFlash_Get(BobjObj *obj);

/* Zeroes the flash / fade block. */
void BtlObjFlash_Clear(BobjObj *obj);

/* Same (the entry btl_obj.c calls). */
void BtlObjFlash_Reset(BobjObj *obj);

/* Starts a 0.2 s colour flash: kind 0 yellow, 1 white, 2 strong white. */
s32 BtlObjFlash_Start(BobjObj *obj, s32 kind);

/* Counts the flash down by one frame (1/30 s). */
s32 BtlObjFlash_Step(BobjObj *obj);

/* Returns the flash colour and its current strength (0..1); result 0 when no flash is running. */
s32 BtlObjFlash_GetColor(BobjObj *obj, Vec4 *color, f32 *alpha);

/* Moves the fade value by 0.1 per frame: up to 1 while object flag 0x40000 is set, else down to 0. */
s32 BtlObjFade_Step(BobjObj *obj);

/* Returns the fade value; result 0 when it is zero. */
s32 BtlObjFade_Get(BobjObj *obj, f32 *out);

/* Stores the byte at object + 0xB30. */
void BtlObj_SetUnkB30(BobjObj *obj, s32 value);

/* Stops the mouth animation; keep == 0 also resets the mouth state and the eye direction. */
void BtlObjFace_Reset(BobjFace *face, s32 keep);

/* Whether entry `index` (0..99) of the table at model block + 0x740 exists. */
s32 BtlObjMdl_HasLipTrack(BobjMdl *mdl, u32 index);

/* Copies the 16 alpha bytes of the model's shared material record into every record of a material table. */
void BtlObjMdl_CopyTexAlpha(BobjMdl *mdl, BobjTexTable *src, BobjTexTable *dst);

/* Whether the model has an animated face. */
s32 BtlObjMdl_HasJaw(BobjObj *obj);

/* Picks one of four eye direction tracks at random (libc rand); model flag 0x400000 selects the second set. */
void BtlObjFace_PickJawKeys(BobjObj *obj, BobjFace *face);

/* Empty. */
void BtlObjFace_Nop(BobjFace *face);

/* Face setup of a new object: shares the material alpha bytes, then the (empty) face hook. */
void BtlObjFace_Init(BobjObj *obj, BobjFace *face);

/* Eye frame of this update: the forced frame (object flag 0x4000000), shut (flag 0x8000000), or the random
   blink: every 90..179 updates the eyes close for 3..5 updates (two libc rand() draws per blink). */
void BtlObjFace_StepBlink(BobjObj *obj, BobjFace *face);

/* Whether mouth state `state` may replace the current one: states 9..12 only yield to 0 or 9..12. */
s32 BtlObjFace_CanStart(BobjFace *face, s32 state);

/* One update of the mouth: advances the talk pattern of the mode, then sets the jaw rotation (models with a jaw
   bone) or the mouth shape (models with mouth textures) from the pattern at the current time. */
void BtlObjFace_Step(BobjObj *obj, BobjFace *face);

/* Whether face texture `n` (1-based) of the model's first table exists. */
s32 BtlObjMdl_HasMouthSet(BobjMdl *mdl, s32 n);

/* Whether the model has anything a face animates: an entry in either texture table, or a jaw bone. */
s32 BtlObjMdl_HasMouth(BobjMdl *mdl);

/* ------------------------------------------------------------------------------------------------------------
 * Second part (formerly bobj_b.c, 0x24F1F0..0x250B28), merged at integration because BtlObj_UpdateFace and
 * BtlObj_IsJawActive only match with the face helpers of the first part defined above them. It keeps its own
 * header and view types. Names the first part already declared with
 * other types are reached through cast macros (the generated code is the same).
 * ------------------------------------------------------------------------------------------------------------ */
/* The first part reaches these through aliased declarations with its own types; the definitions follow. */
#undef BtlObj_FindBound
#undef BtlObj_GetNode
#undef BtlObj_GetNodeByCode
#undef BtlObj_IsJawActive
#undef BtlObj_GetJawRot
#undef BOBJ_NODE_MAX
/*
 * Battle object, third part (0x24F1F0..0x2527B0): what sits between the animation event queries (bobj_a) and
 * src/sys/fade.c. Layouts are in include/battle/bobj_b.h.
 *
 *   0x24F1F0..0x24FA20  the face: eye frame, mouth modes ("sub-states"), lip-sync tracks
 *   0x24FA20..0x2500E8  the tables an object reads out of its files, initial flags, colour preset
 *   0x2500E8..0x250570  colour mode requests and part visibility bits
 *   0x250570..0x250B28  model nodes: lookup, "is shown", position snapshots, node velocity
 *   0x250B28..0x2527B0  secondary motion: push / sway inputs and the two kinds of chains
 *
 * Per frame (BtlObj_UpdateAll in btl_obj.c, for every object in use, skipped while the battle is paused):
 *   BtlObj_SaveNodePositions(obj, 0)      positions of last frame's pose, for node velocities
 *   animation and pose passes (bobj_a)
 *   BtlObj_UpdateChains(obj)              chains rewrite node rotations; the pose pass then runs again
 *   BtlObj_UpdateFace(obj)                blink and mouth
 * None of it looks at the camera, a view or a draw list: the same calls run whether or not the object is drawn.
 */
#include "battle/bobj_b.h"

extern void *memset(void *dst, s32 c, u32 n);
extern s32 rand(void);
extern f32 atan2f(f32 y, f32 x);

extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Scale(Vec4 *dst, Vec4 *src, f32 scale);
extern f32 Vec3_Length(Vec4 *v);
extern f32 Vec3_Dot(Vec4 *a, Vec4 *b);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern void Mtx_MulVec4(Vec4 *dst, Mtx44 *m, Vec4 *v);
extern f32 Mathf_Sin(f32 a);
extern f32 Mathf_Cos(f32 a);
#define Res_RelocateOffsets ((void (*)(void *out, void *base, void *hdr))Res_RelocateOffsets)

/* dst = 0. */
extern void Vec4_SetZero(Vec4 *dst);
/* Inverse of a rotation + translation matrix. */
extern void Mtx_InverseRT(Mtx44 *dst, Mtx44 *src);
/* Matrix product into the first argument. */
extern void Mtx_Mul(Mtx44 *dst, Mtx44 *a, Mtx44 *b);
/* dst = lerp(a, b, t). */
extern void Vec4_Lerp(Vec4 *dst, Vec4 *a, Vec4 *b, f32 t);
/* Rotations of a vector: about an axis vector, about x, about y. */
extern void Vec3_RotateAxis(Vec4 *dst, Vec4 *src, Vec4 *axis, f32 angle);
extern void Vec3_RotateX(Vec4 *dst, Vec4 *src, f32 angle);
extern void Vec3_RotateY(Vec4 *dst, Vec4 *src, f32 angle);
/* Named "light direction" in stg_b.c; the chains use it as a wind vector whose w is the strength. */
extern s32 BtlStage_GetLightDir(Vec4 *out);

/* The 4-entry pool of btl_obj.c. */
extern BObjFace *BtlObjPool70_Alloc(void);
extern s32 BtlObjPool70_Free(BObjFace *node);

/* Face helpers of the previous file (bobj_a's range): mouth reset, "lip track exists", alpha patch of a mouth
   texture set, "model has a jaw bone", jaw table pick (rand() % 4), blink update (rand() % 3, rand() % 90),
   "mode change allowed", mouth animation, "mouth set exists", "model has a mouth". */
#define BtlObjFace_Reset ((void (*)(BObjFace *face, s32 keep))BtlObjFace_Reset)
#define BtlObjMdl_HasLipTrack ((s32 (*)(BObjMdl *mdl, s32 line))BtlObjMdl_HasLipTrack)
#define BtlObjMdl_CopyTexAlpha ((void (*)(BObjMdl *mdl, BObjTexTable *tex, void *set))BtlObjMdl_CopyTexAlpha)
#define BtlObjMdl_HasJaw ((s32 (*)(BObj *obj))BtlObjMdl_HasJaw)
#define BtlObjFace_PickJawKeys ((void (*)(BObj *obj, BObjFace *face))BtlObjFace_PickJawKeys)
#define BtlObjFace_Init ((void (*)(BObj *obj, BObjFace *face))BtlObjFace_Init)
#define BtlObjFace_StepBlink ((void (*)(BObj *obj, BObjFace *face))BtlObjFace_StepBlink)
#define BtlObjFace_CanStart ((s32 (*)(BObjFace *face, s32 mode))BtlObjFace_CanStart)
#define BtlObjFace_Step ((void (*)(BObj *obj, BObjFace *face))BtlObjFace_Step)
#define BtlObjMdl_HasMouthSet ((s32 (*)(BObjMdl *mdl, s32 shape))BtlObjMdl_HasMouthSet)
#define BtlObjMdl_HasMouth ((s32 (*)(BObjMdl *mdl))BtlObjMdl_HasMouth)

/* Talk patterns {frame, shape}: 7 and 5 records. */
#define D_002C6C20 (*(s16(*)[])&D_002C6C20)
#define D_002C6C40 (*(s16(*)[])&D_002C6C40)
/* (0, 0, 0, 1): the identity rotation. */
extern Vec4 D_002EC2C0;
/* Written by BtlObj_InitChains (0.1, 0, 0, 0); no reader found. */
extern Vec4 D_003337D0;

typedef struct BObjProgress {
    /* 0x00 */ s32 unk00;
} BObjProgress;

typedef struct BObjSave {
    /* 0x0000 */ u8 unk0000[0x1608];
    /* 0x1608 */ u32 flags; /* bit 0: second voice language */
} BObjSave;

typedef struct BObjCommon {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ BObjFile file3; /* only buf is real: the pointers of the three common files follow each other */
} BObjCommon;

extern BObjProgress *gProgress;
extern BObjSave *gSaveData;
extern BObjCommon *gCommonRes;

/* Offset of BObj.nodes: the two accessors only match with the index added to the object first. */
#define BOBJ_NODE_TABLE 0xD6C

#define SET_COLOR(obj, v) ((obj)->state.flags = ((obj)->state.flags & ~BOBJ_FLAG_COLOR_MASK) | (v))
#define Q_IDENT(q) ((q)->x = 0.0f, (q)->y = 0.0f, (q)->z = 0.0f, (q)->w = 1.0f)
#define FLAG_BITS(obj) ((BObjFlagBits *)&(obj)->state.flags)

/* Resets the mouth and patches the alpha bytes of every mouth texture set the model has. */
void BObjFace_InitMouth(BObj *obj, BObjFace *face);

/* Advances the lip track: finds the record the time falls in and opens or closes the mouth by its code. */
void BObjFace_StepLipData(BObj *obj, BObjFace *face);

/* Mouth update: lip track, then the mouth animation of the mode. */
void BObjFace_UpdateMouth(BObj *obj, BObjFace *face);

/* Matches only with the body of BtlObjFace_StepBlink (0x24EB70, first part) visible to the compiler (otherwise a
   beqz comes out as beqzl): the reason the two parts are one file. */
/* Per-frame face pass: blink, mouth. */
s32 BtlObj_UpdateFace(BObj *obj);

/* Gives the object a face state when its model has eyes or a mouth. */
void BtlObj_CreateFace(BObj *obj);

/* Returns the face state to its pool. */
void BtlObj_FreeFace(BObj *obj);

/* Forces eye frame `frame`; 9 hands the eyes back to the blink. */
void BtlObj_SetEyeFrame(BObj *obj, u32 frame);

/* Sets the mouth mode (BOBJ_MOUTH_*); arg is the lip track number or pointer for modes 2 and 14. */
void BtlObj_SetSubState(BObj *obj, s32 mode, s32 arg);

/* Returns the mouth shape in use minus one, or -1 (no face, mouth closed, or the model lacks that set). */
s32 BtlObj_GetSubState(BObj *obj);

/* Returns the texture entry of the face part being shown: mouth shape 5..8, else the eye frame. */
BObjTexEntry *BtlObj_GetFaceTexture(BObj *obj);

/* 1 when the object's face has eyes. */
s32 BtlObj_HasEyes(BObj *obj);

/* 1 when the object's face has a mouth. */
s32 BtlObj_HasMouth(BObj *obj);

/* Matches only with the body of BtlObjMdl_HasJaw (0x24E9C8, first part) visible; same cause as BtlObj_UpdateFace. */
/* 1 when the mouth is in a mode other than rest and the model moves a jaw bone for it. */
s32 BtlObj_IsJawActive(BObj *obj);

/* Jaw rotation as a quaternion; identity (and 0) when the object has no face. */
s32 BtlObj_GetJawRot(BObj *obj, Quat *out);

/* Returns the mouth mode, -1 without a face. */
s32 BtlObj_GetMouthMode(BObj *obj);

/* Returns the forced eye frame, -1 without a face. */
s32 BtlObj_GetEyeFrame(BObj *obj);

/* Returns entry n of a file's offset table, NULL when the entry is empty. */
void *BObjFile_GetEntry(BObjFile *file, s32 n);

/* Fills the object's table pointers from the files of its resource slot. */
/* The original's object type nests the model block: the two arrays written through `obj` are addressed as
   (obj + 0x20) + 0xA0 / + 0x90, and this compiler splits every member offset into a multiple of 16 (added to the
   index) and a remainder (added to the base), so the remainders along the member chain sum to 0x20. One level
   (mdl at 0x18, arrays at 0xA8 / 0x98) gives 0x10; a block at 0xC holding the model block at 0xC gives 0x20.
   Only the nesting is verified, not where the outer block really starts or ends. */
typedef struct BObjBindView {
    /* 0x00 */ u8 unk00[0xC];
    /* 0x0C */ struct {
        /* 0x00 */ u8 unk0C[0xC]; /* the slot pointer is the last word (object + 0x14) */
        /* 0x0C */ BObjMdl mdl;   /* object + 0x18 */
    } res;
} BObjBindView;

void BtlObj_BindTables(BObj *obj);

/* Sets the object's initial flags from its type and model header, then the colour preset. */
void BtlObj_InitFlags(BObj *obj);

/* Copies row `row` of preset table `set` (negative = the model's own, bit 24 of its flags) to the draw state. */
void BtlObj_SetColorPreset(BObj *obj, s32 row, s32 set);

/* Points the object's lip tracks and two more tables at common file 3. */
void BtlObj_BindCommonTables(BObj *obj);

/* Copies the 100 lip track pointers of another object. */
void BtlObj_CopyLipTables(BObj *obj, BObj *src);

/* Sets or clears one colour mode request and rewrites the colour flag (bits 16..23) by priority. */
void BtlObj_SetColorMode(BObj *obj, s32 bit, s32 on);

/* Returns the colour mode in force as a number 0..6. */
s32 BtlObj_GetColorMode(BObj *obj);

/* Shows or hides part 0..4 of the model; part 5 resets the low flags to "everything shown". */
void BtlObj_SetPartVisible(BObj *obj, u32 part, s32 on);

/* 1 when part 0..4 of the model is shown. */
s32 BtlObj_IsPartVisible(BObj *obj, u32 part);

/* Returns the bounds record of node `node`, NULL when the model has none. */
BObjBound *BtlObj_FindBound(BObj *obj, s32 node);

/* Returns model node `node`, NULL when the model does not have it. */
BObjNode *BtlObj_GetNode(BObj *obj, s32 node);

/* 1 when the model has node `node`. */
s32 BtlObj_HasNode(BObj *obj, s32 node);

/* 1 when the geometry hanging on node `node` is drawn, given the part bits and the model's layout class. */
s32 BtlObj_IsNodeShown(BObj *obj, s32 node);

/* Which side of the body a node id belongs to: 0 and 1 are the two sides, 2 the centre, 3 ids from 0x35 up. */
s32 BtlObj_GetNodeSide(s32 node);

/* Stores every node's position in the object's frame (relative to node 0's vector when `relative` is set). */
void BtlObj_SaveNodePositions(BObj *obj, s32 relative);

/* Movement of node `node` in the object's frame since the last BtlObj_SaveNodePositions; zero without the node. */
void BtlObj_GetNodeVelocity(BObj *obj, s32 node, Vec4 *out);

/* Returns the node for attachment code 0..18, NULL for other codes. */
BObjNode *BtlObj_GetNodeByCode(BObj *obj, u32 code);
