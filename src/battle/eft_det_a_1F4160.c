#include "common.h"
#include "battle/eft_det_a.h"

/*
 * 0x1AE2A8..0x1B16F0: effect texture tail, volley aim, fighter-against-fighter volumes, the hit detection over
 * the effect hit records, and the ground probe. See include/battle/eft_det_a.h for the layouts.
 *
 * HIT DETECTION, the frame (EftDet_Update, called by Battle_Update between BtlScene_Update, where the projectile
 * tasks publish this frame's records, and BtlScene_PostUpdate, where the tasks read the results):
 *   nothing while the battle is paused (battle flag 0x100), else
 *   1. EftDet_PrepareAll    every record: hitFlags = 0, both distances = FLT_MAX, bounds / movement / zone
 *   2. EftDet_ClashPass     record against record (EftHit_CanHit mode 2)
 *   3. EftDet_StagePass     record against stage  (EftHit_CanHit mode 0)
 *   4. EftDet_FighterPass   record against fighter (EftHit_CanHit mode 1)
 * Every pass walks the list in index order (= the order the tasks created the records). Results go to the owning
 * task with EftHit_SetTaskFlag(index, bit, place): 1 hit a fighter, 2 guarded, 4 hit the stage, 8 lost a clash,
 * 0x20 absorbed, 0x40 deflected, 0x80 reflected, 0x100 beam struggle, 0x8000 multi-hit in contact.
 * The passes do not remove records: a record that lost a clash or hit the stage in this frame is still tested by
 * the later passes unless EftHit_CanHit refuses it because of the task flags the earlier pass set.
 *
 * Callees outside this file are declared here with local views.
 */

extern void *memset(void *dst, s32 c, u32 n);
extern f32 sqrtf(f32 x);
extern f32 powf(f32 x, f32 y);
extern f32 atan2f(f32 y, f32 x);

extern void Res_RelocateOffsets(void *out, void *base, void *hdr);
extern void Dma_AddData(void *src, s32 size);
extern void Dma_AddRef(void *addr, s32 size);
/* Empty (a stripped assert: count <= max). It is defined right before the loaders in the original file (0x1AE140),
   so the compiler knew it touches no memory and kept the pack header and the count in registers across the call;
   the attribute stands in for that (the function is in eft_ae.c, which declares it the same way; the two files were
   not joined at integration because everything matches as it is). */
extern void EftTexSet_CheckCount(s32 count, s32 max) __attribute__((const));

extern void Vec4_Set(EftDetVec *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Copy(EftDetVec *dst, EftDetVec *src);
extern void Vec4_Add(EftDetVec *dst, EftDetVec *a, EftDetVec *b);
extern void Vec4_Sub(EftDetVec *dst, EftDetVec *a, EftDetVec *b);
extern void Vec4_Scale(EftDetVec *dst, EftDetVec *src, f32 scale);
extern void Vec3_Add(EftDetVec *dst, EftDetVec *a, EftDetVec *b);
extern void Vec3_Sub(EftDetVec *dst, EftDetVec *a, EftDetVec *b);
extern void Vec3_Scale(EftDetVec *dst, EftDetVec *src, f32 scale);
extern void Vec3_Normalize(EftDetVec *dst, EftDetVec *src);
extern void Vec3_Cross(EftDetVec *dst, EftDetVec *a, EftDetVec *b);
extern f32 Vec3_Dot(EftDetVec *a, EftDetVec *b);
extern void Mtx_StoreIdentity(EftDetMtx *m);
extern void Mtx_MulVec4(EftDetVec *dst, EftDetMtx *m, EftDetVec *src);
extern void Mtx_RotateX(EftDetMtx *dst, EftDetMtx *src, f32 angle);          /* rotate about X */
extern void Mtx_RotateY(EftDetMtx *dst, EftDetMtx *src, f32 angle);          /* rotate about Y */
extern void Vec3_Copy(void *dst, EftDetVec *src);                          /* copies x, y, z */
extern void Vec3_Clamp(EftDetVec *dst, EftDetVec *src, f32 lo, f32 hi);     /* clamp x, y, z */
extern f32 Vec3_LengthSq(EftDetVec *v);                                        /* squared length */
extern f32 Vec3_Dist(void *a, EftDetVec *b);                               /* distance between two points */
extern void Vec3_RotateAxis(EftDetVec *out, EftDetVec *v, EftDetVec *axis, f32 angle); /* rotate about an axis */
extern f32 Mathf_SinFast(f32 angle);
extern f32 Mathf_CosFast(f32 angle);
extern f32 Mathf_Asin(f32 x);
extern f32 Mathf_Acos(f32 x);
extern f32 EftMath_WrapAngle(f32 angle);

extern f32 BtlScene_RandRangeF(f32 a, f32 b);
extern s32 BtlScene_RandRange(s32 a, s32 b);

extern s32 BtlCharApi_GetOpponentObjId(s32 objId);
extern void BtlCharApi_GetBasePos(s32 objId, EftDetVec *out);
extern void BtlCharApi_GetFrameMove(s32 objId, EftDetVec *out);
extern f32 BtlCharApi_GetAltitude(s32 objId);
extern void BtlCharApi_GetNodePos(s32 objId, s32 node, EftDetVec *out);
extern s32 BtlCharApi_IsSightBlocked(s32 objId);
extern s32 BtlCharApi_IsLockedOn(s32 objId);
extern void BtlCharApi_SetHeldFlagAA(s32 objId);
extern void BtlCharApi_ShakeCamsNear(EftDetVec *pos, f32 near, f32 far, f32 arg3, f32 arg4);
extern void BtlCharApi_RumbleNear(EftDetVec *pos, f32 near, f32 far, f32 power, f32 time);
extern s32 BtlSeq_GetState(void);
extern s32 BattleSide_GetObjId(s32 side);
extern EftDetObj *BtlObj_Get(s32 objId);
extern EftDetNodeMtx *BtlObj_GetNode(EftDetObj *obj, s32 node);

/* Battle work: only the flags. */
typedef struct EftDetBattle {
    /* 0x0000 */ u8 unk0[0x19F0];
    /* 0x19F0 */ u64 flags; /* 0x100: paused */
} EftDetBattle;
extern EftDetBattle *Battle_GetWork(void);

/* The hit record core (eft_a.c). */
extern EftDetList *EftHit_GetList(void);
extern s32 EftHit_SetTaskFlag(u32 idx, s32 bits, EftDetVec pos); /* void in eft_a.c; see EftDet_HitFighterMulti */
extern s32 EftHit_CanHit(EftDetRec *rec, s32 mode);
extern s32 EftHit_IsStoppedByHit(EftDetRec *rec);
extern s32 EftHit_RearmImpact(EftDetRec *rec);
extern s32 EftHit_Clash(EftDetRec *a, EftDetRec *b);
extern s32 EftHit_IsMultiHit(EftDetRec *rec);
extern void EftHit_IncHitCount(EftDetRec *rec);
extern s32 EftHit_GetHitCount(EftDetRec *rec);
extern s32 EftHit_GetMaxHits(EftDetRec *rec);
extern s32 EftHit_GetDefUnkB(EftDetRec *rec);
extern void EftHit_IncCountA(EftDetRec *rec);
extern void EftHit_SetCountA(EftDetRec *rec, s32 value);
extern s32 EftHit_GetCountA(EftDetRec *rec);
extern s32 EftHit_HasDefFlag20(EftDetRec *rec);
extern void EftHit_MarkLastHit(EftDetRec *rec);
extern s32 EftHit_NotifyBlastTask(u32 idx, void *tri);

/* The fighter's answer to a record that touches it (btl_char_coll_b.c). */
extern s32 BtlColl_TryDodge(s32 objId, EftDetRec *hit);
extern s32 BtlColl_TryDeflect(s32 objId, EftDetRec *hit);
extern s32 BtlColl_TryReflect(s32 objId, EftDetRec *hit);
extern s32 BtlColl_TryAbsorb(s32 objId, EftDetRec *hit);
extern s32 BtlColl_TryGuard(s32 objId, EftDetRec *hit);
extern s32 BtlColl_Hit(s32 objId, EftDetRec *hit);
extern void BtlColl_PlayContactSound(EftDetRec *hit);

/* Beam struggle effect (ki blast file, 0x174A70..). */
extern s32 EftStruggle_IsActive(void);                                       /* 1 while a beam struggle is running */
extern void EftStruggle_Start(EftDetVec *pos, EftDetRec *a, EftDetRec *b); /* starts the beam struggle at pos */

/* Collision primitives (0x230B38..0x239A00, not decompiled). */
extern void ColBox_SetCenterHalf(EftDetBox *box, EftDetVec *center, EftDetVec *extent); /* box = center +- extent */
extern void ColBox_GetCenter(EftDetBox *box, EftDetVec *center);                     /* centre of a box */
extern void ColBox_GetHalf(EftDetBox *box, EftDetVec *extent);                     /* half size of a box */
extern void ColMesh_GetPolyVerts(void *mesh, EftDetPoly *poly, EftDetVec *v0, EftDetVec *v1, EftDetVec *v2);
extern EftDetPoly *ColMesh_GetPoly(void *mesh, s32 poly);
extern s32 ColBox_Overlaps(EftDetBox *a, EftDetBox *b);                             /* 1 when two boxes overlap */
extern s32 ColObb_Overlaps(void *vol, void *partVol);
/* Swept capsule against a triangle. The 64-bit return type is what makes EftDet_StageCb match (with a 32-bit one
   the compiler threads the "return 0" after the test). */
extern s64 ColSweep_TestTri(EftDetStageCtx *sweep, EftDetTri *tri, EftDetVec *hit, f32 *dist);
extern s32 ColSphere_ContactObb(EftDetSphere *sphere, void *partVol, EftDetVec *out0, EftDetVec *out1, f32 *t);
extern s32 ColSphere_TestSphere(EftDetSphere *sphere, void *box);                        /* 1 when they overlap */
extern s32 ColSphere_SweepSphere(EftDetSphere *a, void *b, EftDetVec *moveA, EftDetVec *moveB, f32 *t);
extern s32 ColSphere_SeparateSphere(EftDetSphere *a, EftDetSphere *b, EftDetVec *posA, EftDetVec *posB, EftDetVec *nrm);
extern void ColBounds_OfCapsule(EftDetBox *box, void *capsule);                         /* bounds of a capsule */
extern void ColCapsule_Set(EftDetCapsule *cap, void *from, void *to, f32 radius);
extern void ColSweep_FromCapsule(EftDetStageCtx *sweep, EftDetCapsule *cap);
extern void ColSphere_Set(EftDetSphere *sphere, void *center, f32 radius);

/* Stage (stg_a.c, eft_det_b.c). */
extern s32 BtlStage_FindZoneNear(s32 zone, void *pos);
extern void *BtlStage_GetZone(s32 zone);
extern s32 BtlStage_DestroyObj(s32 objId, s32 idx, EftDetVec *hitPos);
extern s32 BtlStage_DamageObj(s32 idx, s32 damage);
extern void StgCol_SetModeAll(void);
extern void StgCol_SetModeObjects(void);
extern s32 StgCol_QueryZone(EftDetResult *result, void *zone, EftDetBox *box, void *ctx, void *callback);
extern s32 StgCol_FirstBit(u64 mask);
extern void StgCol_FighterBreakObj(EftDetObj *obj, s32 idx, EftDetVec *hitPos);

extern EftVram *gEftVram;
extern EftVolleyAimStep *gEftVolleyAimScripts[];
extern void *gStgColMesh;
extern EftDetResult gStgGroundResult;
extern EftDetVec D_002EC2C0; /* {0, 0, 0, 1}: "no movement" */
extern EftDetVec D_002EC2E0; /* {0, 1, 0, 1}: down */
extern const f32 D_002FEAF8[]; /* FLT_MAX */
extern const f32 D_002FEAFC[]; /* FLT_MAX */

#define EFT_DET_DEG(x) ((x) / 180.0f * 3.14159265f)
#define EFT_DET_PI 3.14159265f

/* Builds a texture set of at most 8 entries from a texture pack. */
void EftTexSet_Load8(EftTexSet8 *set, void *pack);

/* Builds a texture set of at most 16 entries from a texture pack. */
void EftTexSet_Load16(EftTexSet16 *set, void *pack);

/* Builds a texture set of at most 34 entries from a texture pack. */
void EftTexSet_Load34(EftTexSet34 *set, void *pack);

/* Returns the number of VRAM blocks the effect textures use (no caller). */
s32 EftVram_GetUsed(void);

/* Returns the number of VRAM blocks the effect textures may use (no caller). */
s32 EftVram_GetCapacity(void);

/* Queues the upload of a texture's image to VRAM block imageBlock and of its CLUT to clutBlock (< 0: skip). */
#define EFT_VRAM_BITBLTBUF(block, width) (((s64)(block) << 32) | ((u64)(width) << 48))

void EftVram_Upload(EftVramTex *tex, s32 imageBlock, s32 clutBlock) {
    u32 pkt[12] = {
        0x10000002, 0x00000000, 0x00000000, 0x50000002, 0x00008001, 0x10000000,
        0x0000000E, 0x00000000, 0x00000000, 0x00000000, 0x00000050, 0x00000000,
    };
    EftVramImage *img = tex->img;

    if (imageBlock >= 0 && img->imageSize != 0) {
        pkt[8] = EFT_VRAM_BITBLTBUF(imageBlock, img->imageWidth);
        pkt[9] = EFT_VRAM_BITBLTBUF(imageBlock, img->imageWidth) >> 32;
        Dma_AddData(pkt, sizeof(pkt));
        Dma_AddRef(img->image, img->imageSize);
    }
    if (clutBlock >= 0 && img->clutSize != 0) {
        pkt[8] = EFT_VRAM_BITBLTBUF(clutBlock, img->clutWidth);
        pkt[9] = EFT_VRAM_BITBLTBUF(clutBlock, img->clutWidth) >> 32;
        Dma_AddData(pkt, sizeof(pkt));
        Dma_AddRef(img->clut, img->clutSize);
    }
}

/* Returns a + (b - a) * t. */
f32 EftVolleyAim_Lerp(f32 a, f32 b, f32 t);

/* Returns the squared distance between fighters 0 and 1. */
f32 EftVolleyAim_GetFighterDistSq(void);

/* Stores the vector from fighter objId to its opponent. */
void EftVolleyAim_GetToOpponent(s32 objId, EftDetVec *out);

/* Returns which side a muzzle node is on: 0 for nodes 0x12..0x1F and 0x36, 1 for 0x20..0x2D. */
s32 EftVolleyAim_GetNodeSide(s32 node);

/* Spreads a new shot's direction and stores its steering script, speed and turn rate. */
void EftVolleyAim_InitShot(s32 objId, EftVolleyAimShot *shot, s32 kind, s32 side, s32 index, s32 count, f32 speed,
                           f32 maxTurn);

/* Turns dir by a yaw / pitch offset that depends on the aim kind, the shot's index in the volley and the scene
 * generator. Returns the steering script of the shot: 0 / 1 for the lobbed kinds 7 / 8, else -1. */
s32 EftVolleyAim_Spread(s32 objId, EftDetVec *dir, s32 kind, s32 lockedOn, s32 side, s32 index, s32 count);

/* One frame of a homing shot: leads the opponent's node 0x11 (+ offset) by its frame movement, turns the
 * direction towards it by at most shot->maxTurn, then advances the position by shot->speed. */
void EftVolleyAim_Steer(EftVolleyAimShot *shot, s32 objId, EftDetVec *offset, s32 frontOnly);

/* Runs the steering script of a lobbed shot for `time` frames since it was fired (speed, turn rate and target
 * offset by time window), then steers it. `offset` is the shot's own target offset, kept between frames. */
void EftVolleyAim_Update(s32 objId, EftVolleyAimShot *shot, EftDetVec *offset, s32 exact, f32 time, f32 speed,
                         f32 maxTurn);

/* Returns 1 when one of the active attack volumes in `work` touches one of the body parts of `body`. */
s32 BtlBodyHit_TestVolumes(EftDetObjWork *work, EftDetPart **body);

/* Tests the strike volumes of `atk` against the body of `def` and records the contact in both objects. */
s32 BtlBodyHit_Test(EftDetObj *atk, EftDetObj *def);

/* Fighter against fighter: the object of side 0 against the object of side 1, then the reverse. */
void BtlBodyHit_Update(void);

/* Shape type 0: bounds of the sweep from sphere b to sphere a, its movement and direction, and the zone. */
s32 EftDet_PrepareSpheres(EftDetShape *shape);

/* Shape type 1: bounds of capsule a, its axis as movement and direction, and the zone of its end. */
s32 EftDet_PrepareCapsule(EftDetShape *shape);

/* Shape types 2..6: nothing to prepare. */
s32 EftDet_PrepareNone(EftDetShape *shape);

/* Resets the detection fields of every record and prepares its shape. */
void EftDet_PrepareAll(void);

/* The hit detection of one frame; nothing while the battle is paused. */
void EftDet_Update(void);

/* Shape type 0 against a fighter: sphere b swept along delta against every body part; the earliest contact wins.
 * A part the sphere already overlaps at the start ends the search. */
s32 EftDet_SpheresVsFighter(EftDetObj *obj, EftDetShape *shape);

/* Shape type 1 against a fighter: a sphere at the start of capsule a swept along the capsule's axis. */
s32 EftDet_CapsuleVsFighter(EftDetObj *obj, EftDetShape *shape);

/* Shape types 2..6 never touch a fighter. */
s32 EftDet_NoneVsFighter(EftDetObj *obj, EftDetShape *shape);

/* A single-hit record touches fighter `target`: guard (task flag 2) or hit (task flag 1). */
void EftDet_HitFighter(EftDetRec *rec, s32 target, s32 idx);

/* A multi-hit record touches fighter `target`. The task counts the frames in contact (counter A) and the hits
 * landed: past the hit limit it only reports a hit; between two hits (fewer frames than the definition's interval
 * since the last one) it reports "in contact" (0x8000); else guard or hit as above, counting the hit.
 * The first exit is a tail call and the others are not, which this compiler only does for a non-void function
 * that returns the callee's value there, hence the types (the value is never used). */
s32 EftDet_HitFighterMulti(EftDetRec *rec, s32 target, s32 idx);

/* Record against fighter. Each record is tested against ONE fighter: target = owner id ^ 1, and the object tested
 * is the active fighter of side (target != 0). A contact that lies behind a stage contact of the same record
 * (found by EftDet_StagePass, which ran before) is dropped. Then the fighter answers, first yes wins: dodge
 * (nothing reported), deflect (0x40), reflect (0x80), absorb (0x20), then guard (2) or hit (1).
 * (The mix of `rec->` and `list->rec[i].` is what reproduces the original's two induction pointers.) */
void EftDet_FighterPass(void);

/* Two type 0 shapes: both spheres swept over the frame. On contact stores each one's centre and contact point. */
s32 EftDet_SpheresVsSpheres(EftDetShape *a, EftDetShape *b);

/* Two type 1 shapes: a sphere at the start of each capsule, swept along each capsule's axis. */
s32 EftDet_CapsuleVsCapsule(EftDetShape *a, EftDetShape *b);

/* A type 1 shape (a) against a type 0 shape (b). */
s32 EftDet_CapsuleVsSpheres(EftDetShape *a, EftDetShape *b);

/* Record against record: every pair i < count - 1, j >= i of records of different owners. Record i is asked
 * once whether it may still clash (EftHit_CanHit mode 2), before its inner loop; record j for every pair.
 * EftHit_Clash is called for the pair whether or not the shapes touch (it has side effects: a head-on pair of
 * techniques asks both technique timers to stop); its result is used only when they touch:
 * bit 0 -> record i lost (task flag 8), bit 1 -> record j lost (3 = both), 4 -> beam struggle: both lose when
 * the owner of i has no line of sight or the battle sequence is at state 4 or later; else both fighters get held
 * flag 0xAA and, unless a struggle is already running, both tasks get flag 0x100 and the struggle effect starts
 * at record i's contact centre. Only record i gets EFT_DET_HIT_CLASH. */
void EftDet_ClashPass(void);

/* Mesh callback of the stage test: the record's swept volume against one triangle; keeps the nearest contact in
 * the record's shape (centre, contact point pushed back by the radius along the plane normal, the triangle). */
s32 EftDet_StageCb(EftDetNode *node, EftDetStageCtx *ctx);

/* One record against the stage collision of its zone (none when the zone is < 0). The volume is a capsule from
 * the previous to the current position (type 0: sphere centres; type 1: capsule ends) with the radius times
 * shape->scale (not scaled for type 0 when objectsOnly), at least 0.08. Returns 1 when it hit something solid
 * that stays: sets EFT_DET_HIT_STAGE and stageDist; hitPos / contact / tri were filled by the callback.
 * When the walk touched an unbroken stage object, the one with the lowest index takes damage (1 from a ki blast,
 * 999999 from a technique); if that breaks it, it is destroyed and the record goes on as if nothing was hit
 * (returns 0 although hitPos / contact / tri were written). */
s32 EftDet_TestStage(EftDetShape *shape, s32 isBlast, s32 objectsOnly);

/* Record against stage. A rush-type technique (class 0 kind 4, or another class and kind 9) only meets unbroken
 * stage objects. A record that is stopped by the hit reports task flag 4 with the contact point, hands the
 * triangle to its blast task and plays the contact sound; a technique also shakes cameras and pads nearby. */
void EftDet_StagePass(void);

/* Stretches a box 8000 downwards (+Y is down), keeping its top. */
void StgGround_ExtendBoxDown(EftDetBox *box);

/* Tests the point (out->x, out->z) against a triangle seen from above. When it is inside and the plane's height
 * there is below minY and above the best so far, stores the height, the plane and the polygon flags. */
s32 StgGround_TestTri(StgGroundOut *out, EftDetTri *tri, s32 flags, f32 minY);

/* Mesh callback of the ground probe: solid polygons that face up only. */
s32 StgGround_Cb(EftDetNode *node, StgGroundCtx *ctx);

/* The ground probe: of the upward-facing solid triangles of the zone (static mesh, unbroken objects, remains of
 * broken ones) that lie under the point (out->x, out->z), the one nearest below the height minY (+Y is down:
 * the smallest plane height that is still greater than minY). `box` is only the search volume (stretched 8000
 * down) and gives the zone. out->y comes back as the ground height, or FLT_MAX when there is none; out->nrm and
 * out->flags describe the triangle. What the walk touched is left in gStgGroundResult. */
void StgGround_Probe(s32 zone, EftDetBox *box, StgGroundOut *out, f32 minY);

/* Per-frame ground query of a fighter object: probes below the body sphere's height at the object's position and
 * stores the result in the object's work buffer. When the probe touched an unbroken stage object and the ground
 * found is above the model's root node, the fighter is under / inside that object: break test on it. */
void StgGround_UpdateFighter(EftDetObj *obj);
