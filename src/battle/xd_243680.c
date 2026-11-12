/*
 * BT3 transplant (fuzzy 0.935, BT3 StgRigid_Update): fdiff OK required.
 */
#include "common.h"
#include "sys/math3d.h"
#include "sys/heap.h"
#include "sys/randf.h"
#include "sys/rigid.h"
#include "battle/stg_d.h"
#include "battle/battle.h"

extern void func_0028BB60(void *p);
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern void func_00312680(Vec4 *dst, Vec4 *src, f32 scale);
extern BattleResult *func_0023EA20(void);

/* One frame of every body: 10 sub-steps of STG_RIGID_DT (until the summed time passes 1 / 6). Nothing while paused. */
void StgRigid_Update(void) {
    f32 t = 0.0f;

    if (Battle_GetWork()->flags & 0x100) {
        return;
    }
    StgRigidList_BeginFrame(gStgRigid->active);
    do {
        t += STG_RIGID_DT;
        StgRigidList_UpdateCenters(gStgRigid->active);
        StgRigidList_Collide(gStgRigid->active);
        StgRigidList_AddForces(gStgRigid->active);
        StgRigidList_Step(gStgRigid->active);
    } while (t <= 1.0f / 6.0f);
    StgRigidList_EndFrame(gStgRigid->active);
    gStgRigid->count = StgRigidList_Count(gStgRigid->active);
}
