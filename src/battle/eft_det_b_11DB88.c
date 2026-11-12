/*
 * Stage collision queries: 0x1B16F0..0x1B3510 (include/battle/eft_det_b.h has the layouts).
 *
 * Despite the file stem this is not effect code: it continues the stage collision that starts at the end of the
 * neighbouring file (EftDet_TestStage 0x1B0E88, StgGround_Probe 0x1B14C0 and StgGround_UpdateFighter 0x1B15B8
 * call StgCol_QueryZone, StgCol_FirstBit, StgCol_FighterBreakObj and the mode setters defined here).
 *
 * Source file boundaries (evidence): StgCol_TraceZone and StgCol_CollectZone only match when StgCol_FirstBit
 * (0x1B18B8) is NOT known to the compiler, so a source file ends between 0x1B18F8 and 0x1B2BA0; the .lit4 pool
 * runs on from the neighbouring file (0x2FCFC0 is its last constant, 0x2FCFC4 the first one here).
 *
 * Per fighter and frame (BtlChar_UpdateStage8, fighter 0 first): BtlObjBody_BeginFrame clears the contact word,
 * StgCol_UpdateFighter sweeps the body sphere, StgGround_UpdateFighter probes the ground; BtlColl_UpdateGround
 * (stage 9) then turns the contact word into fighter flags and damage.
 *
 * In address order:
 *   0x1B16F0  query mode, the zone query every other function is built on, lowest-bit helper
 *   0x1B1900  camera: a swept sphere against the stage (StgCol_TraceSphere)
 *   0x1B1CA0  fighter: the body sphere moved through the stage in sub-steps and pushed out of what it touches
 *             (StgCol_UpdateFighter), breaking stage objects on the way (StgCol_FighterBreakObj)
 *   0x1B25E0  segment trace through the zones (StgCol_TraceSegment) and triangle collection around a sphere
 *             (StgCol_CollectSphere, for the stage rigid bodies)
 *   0x1B2FE8  triangles under a box, for the fighter's ground shadow (StgShadow_*)
 *
 * SIMULATION: StgCol_UpdateFighter (moves the fighter, writes its stage contact word, breaks objects),
 * StgCol_FighterBreakObj, StgCol_TraceSegment (lock-on sight, AI, sweeping beam, approach point) and
 * StgCol_CollectSphere (debris rigid bodies; read by no fighter code). The camera sweep feeds the camera only;
 * StgShadow_* only drawing. No random draw anywhere in this file.
 */
#include "common.h"
#include "battle/eft_det_b.h"

extern void *memset(void *dst, s32 c, u32 n);
extern f32 sqrtf(f32 x);
extern void *memcpy(void *dst, const void *src, u32 n);

extern void Vec4_Copy(StgColVec *dst, StgColVec *src);
extern void Vec4_Add(StgColVec *out, StgColVec *a, StgColVec *b);
extern void Vec3_Sub(StgColVec *out, StgColVec *a, StgColVec *b);
extern void Vec3_Scale(StgColVec *out, StgColVec *v, f32 s);
extern f32 Vec3_Dot(StgColVec *a, StgColVec *b);
extern f32 Vec3_Dist(StgColVec *a, StgColVec *b);          /* distance */

/* Collision mesh (0x230EC0..0x231768). */
extern s32 ColMesh_WalkBox(void *mesh, StgColBox *box, void *ctx, StgColCb cb); /* walk: cb per candidate node */
extern StgColPoly *ColMesh_GetPoly(void *mesh, s32 poly);
extern void ColMesh_GetPolyVerts(void *mesh, StgColPoly *poly, StgColVec *v0, StgColVec *v1, StgColVec *v2);
extern s32 ColNode_TestBox(StgColNode *node, StgColBox *box);     /* node bounds against a box */

/* Box helpers (0x230B10..0x2311C8). */
extern void StgAabb_SetEmpty(StgColBox *box);                   /* 0x230B10: empty box */
extern void ColBox_SetCenterHalf(StgColBox *out, StgColVec *center, StgColVec *extent);
extern void ColBox_AddPoint(StgColBox *box, StgColVec *pt);       /* grow to contain a point */
extern void ColBox_AddPointKeepW(StgColBox *box, StgColVec *pt);       /* grow to contain a point (x, z) */
extern void ColBox_GetCenter(StgColBox *box, StgColVec *center);
extern void ColBox_GetHalf(StgColBox *box, StgColVec *half);
extern s32 ColBox_ContainsPoint(StgColBox *box, StgColVec *pt);        /* point inside */
extern s32 ColBox_Overlaps(StgColBox *a, StgColBox *b);           /* overlap */
extern s32 ColBox_ClipRay(StgColBox *box, StgColRay *ray, StgColVec *out); /* ray against box */

/* Primitive tests (0x236228..0x2387E0). */
extern s32 ColSweep_TestTri(StgColSweepCtx *ctx, StgColTri *tri, StgColVec *pos, f32 *dist); /* swept sphere */
extern s32 ColSeg_TestTri(StgColSeg *seg, StgColTri *tri, StgColVec *pos, f32 *dist);      /* segment */
extern s32 ColSphere_TestTri(StgColVec *pos, StgColSphere *sphere, StgColTri *tri);           /* sphere */
extern void ColBounds_OfCapsule(StgColBox *out, StgColSweep *seg);    /* bounds of a swept sphere */
extern void ColBounds_OfSphere(StgColBox *out, StgColSphere *sphere); /* bounds of a sphere */
extern void ColRay_FromSeg(StgColRay *out, StgColSeg *seg);      /* ray of a segment */
extern void ColBounds_OfSeg(StgColBox *out, StgColSeg *seg);      /* bounds of a segment */
extern void ColCapsule_GetLongSegDir(StgColVec *out, StgColVec *dir, StgColSweepCtx *ctx); /* direction of a sweep */

/* Battle object body (0x24DC58..0x24E3F8). */
extern void BtlObjBody_Update(StgColFighter *obj, s32 arg);
extern void BtlObjBody_BeginFrame(StgColFighter *obj);
extern void BtlObjXf_Update(StgColFighter *obj);
extern void BtlObjPose_CalcMatrices(StgColFighter *obj);

/* Stage (stg_a.c). */
extern s32 BtlStage_IsReady(void);
extern s32 BtlStage_FindZoneNear(s32 zone, StgColVec *pos);
extern StgColZone *BtlStage_GetZone(s32 zone);
extern void BtlStage_ClearZoneMarks(void);
extern s32 BtlStage_DestroyObj(s32 objId, s32 idx, StgColVec *hitPos);
extern s32 BtlStage_IsObjBroken(s32 idx);
extern s32 BtlStage_GetObjType(s32 idx);

extern s32 BtlCharApi_TestStageBreakA(s32 objId);
extern s32 BtlCharApi_TestStageBreakB(s32 objId);

extern StgColStage *gBtlStage;
extern s32 gStgColMode;
extern void *gStgColMesh;
extern s32 gStgColZoneMisses;
extern s32 gStgColZoneVisits;
extern f32 gStgColFar[];
extern StgColVec D_002EC2C0;       /* zero vector */
extern StgColVec D_002EC2E0;       /* (0, 1, 0): down */

/* Queries test the zone's static mesh, whole objects and broken objects. */
void StgCol_SetModeAll(void);

/* Queries test unbroken objects only. */
void StgCol_SetModeObjects(void);

/* Walks every collision mesh of a zone that is in force against `box`, calling `cb(node, ctx)` for each candidate
   node, and reports what was touched. */
s32 StgCol_QueryZone(StgColResult *res, StgColZone *zone, StgColBox *box, void *ctx, StgColCb cb);

/* Index of the lowest set bit, -1 when none. */
s32 StgCol_FirstBit(u64 mask);

/* Mesh callback of the camera sweep: keeps the nearest triangle the swept sphere touches. */
s32 StgCol_SweepCb(StgColNode *node, StgColSweepCtx *ctx);

/* Sweeps a sphere from seg->a to seg->b through one zone (the sweep starts two radii behind a). Returns 1 on a
   hit, with the sphere's position, the fraction of the (lengthened) way and the triangle. Camera only. */
s32 StgCol_TraceSphere(s32 zoneIdx, StgColSweep *seg, StgColVec *hitPos, f32 *frac, StgColTri *tri);

/* Splits a movement of length `dist` into steps of at most half a radius: writes one step, returns how many. */
/* The `do { } while (0)` is needed to match: the original keeps `scale = 1.0f` in front of the branch although its
   only use is in the other block; without loop notes around that use the compiler moves the load next to it. */
s32 StgCol_SplitStep(StgColVec *out, StgColVec *delta, f32 radius, f32 dist);

/* Advances the sphere by one step and rebuilds its bounds (radius + 0.1). */
void StgCol_StepSphere(StgColSphere *sphere, StgColBox *box, StgColVec *step);

/* Moves the sphere away from a contact point until the point lies on its surface, and rebuilds its bounds. */
void StgCol_PushSphere(StgColSphere *sphere, StgColBox *box, StgColVec *point);

/* Mesh callback of the fighter's body sphere: pushes the sphere out of every solid triangle it touches, in the
   order the mesh walk delivers them, and remembers the last one. */
s32 StgCol_PushCb(StgColNode *node, StgColPushCtx *ctx);

/* Moves the body sphere `steps` times by `step`, resolving against the zone after every step (the zone is looked
   up again each step when crossZones is set) and breaking the first unbroken object touched in a step. When
   anything pushed the sphere: contact bit 0x20, the polygon into the work buffer, the object's position moved by
   the correction. Returns 1 when pushed. */
s32 StgCol_MoveFighter(StgColFighter *obj, StgColPushCtx *ctx, s32 zoneIdx, s32 steps, StgColVec *step,
                       StgColVec *delta, s32 crossZones, s32 keepSphere);

/* Per-frame stage collision of a fighter's battle object: sweeps its body sphere from last frame's position to
   this frame's and pushes the object out of the stage. */
void StgCol_UpdateFighter(StgColFighter *obj, s32 keepSphere, s32 grow);

/* A fighter's body touched unbroken stage object idx. */
void StgCol_FighterBreakObj(StgColFighter *obj, s32 idx, StgColVec *hitPos);

/* StgCol_FirstBit as a function not yet seen by the compiler: StgCol_TraceZone and StgCol_CollectZone only match
   that way (branch-likely choice), so in the original it was not defined earlier in their source file. */
extern s32 StgCol_FirstBit_(u64 mask) __asm__("StgCol_FirstBit");

/* Mesh callback of the segment trace: keeps the nearest solid triangle the segment crosses. */
s32 StgCol_SegCb(StgColNode *node, StgColCtx *ctx);

/* Mesh callback of the triangle collection: appends every solid triangle the sphere touches (64 at most). */
s32 StgCol_CollectCb(StgColNode *node, StgColCtx *ctx);

/* Prepares the static context for a segment trace. */
void StgCol_InitSegCtx(StgColCtx *ctx, StgColSeg *seg) {
    f32 far;

    memset(ctx, 0, sizeof(StgColCtx));
    ctx->seg = *seg;
    ColBounds_OfSeg(&ctx->box, seg);
    ctx->dist = Vec3_Dist(&seg->a, &seg->b);
    ColRay_FromSeg(&ctx->ray, seg);
    far = gStgColFar[0];
    ctx->obj = -1;
    ctx->dist = far;
}

/* Prepares the static context for a triangle collection. */
void StgCol_InitSphereCtx(StgColCtx *ctx, StgColSphere *sphere, StgColTriList *list) {
    memset(ctx, 0, sizeof(StgColCtx));
    ctx->sphere = *sphere;
    ColBounds_OfSphere(&ctx->box, sphere);
    ctx->list = list;
    if (list != NULL) {
        list->count = 0;
    }
    ctx->obj = -1;
}

/* The zone's rectangle as a box of unlimited height. */
void StgCol_GetZoneBox(StgColBox *box, s32 zoneIdx);

/* Bounds of the part of the segment that lies inside zone `cur`: between the point where it enters (`entry`, or
   its start in the first zone) and the point where it leaves (found with the reversed ray, or its end in the last
   zone). */
void StgCol_ClipSegToZone(StgColBox *out, s32 cur, s32 from, s32 to, StgColCtx *ctx, StgColBox *zoneBox,
                          StgColVec *entry);

/* Segment trace, one zone: tests the zone when the segment passes through it; without a hit goes on to every
   neighbour that contains the point where the segment entered this zone... The first zone with a hit ends the
   walk. */
void StgCol_TraceZone(s32 cur, s32 from, s32 to, StgColCtx *ctx);

/* Triangle collection in one zone. */
void StgCol_CollectZone(s32 zoneIdx, StgColCtx *ctx);

/* Does the stage block the segment a -> b? On 1, gStgColHit has the position, the polygon and the index of the
   unbroken object hit (-1: static geometry). 0 while the stage is not ready. */
s32 StgCol_TraceSegment(StgColSeg *seg);

/* Hit position of the last trace or collection; 0 when it found nothing. */
s32 StgCol_GetHitPos(StgColVec *out);

/* Result block of the last segment trace. */
StgColHit *StgCol_GetHit(void);

/* Collects the solid triangles touching a sphere, in the sphere's zone only. Used by the stage rigid bodies. */
s32 StgCol_CollectSphere(StgColSphere *sphere, StgColTriList *list);

/* Shadow query setup: the caller's box extended 50 downwards, and a thin column through its centre. */
void StgShadow_InitCtx(StgShadowCtx *ctx, StgColBox *box, s32 max, StgColTri *buf);

/* When the point lies over the triangle (x, z), lowers *y to the triangle's height there. */
s32 StgShadow_ProbeTri(StgColVec *pt, StgColTri *tri, f32 *y);

/* Appends a triangle to the shadow list. A polygon with the "flat only" flag is dropped unless it faces straight
   up. */
s32 StgShadow_AddTri(StgShadowCtx *ctx, StgColTri *tri, s32 flags);

/* Mesh callback of the shadow query: upward-facing triangles only. */
s32 StgShadow_Cb(StgColNode *node, StgShadowCtx *ctx);

/* Shadow strength by height above the ground: 1 up to 20, falling to 0 at 50. */
f32 StgShadow_CalcAlpha(f32 height);

/* Writes the output block of the shadow query. */
void StgShadow_Finish(StgShadowCtx *ctx);

/* Collects up to `max` upward-facing triangles under `box` into `buf` and the shadow strength into gStgShadow.
   Returns the triangle count. Drawing only (caller: the stage model code at 0x1143A0). */
s32 StgShadow_Collect(s32 zoneIdx, StgColBox *box, s32 max, StgColTri *buf);

/* Output block of the last shadow query. */
StgShadowOut *StgShadow_GetOut(void);
