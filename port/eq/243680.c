#include "common.h"

void StgRigidList_AddForces(s32 arg0);
void StgRigidList_BeginFrame(s32 arg0);
void StgRigidList_Collide(s32 arg0);
s32 StgRigidList_Count(s32 arg0);
void StgRigidList_EndFrame(s32 arg0);
void StgRigidList_Step(s32 arg0);
void StgRigidList_UpdateCenters(s32 arg0);
extern f32 D_00386D5C;
extern f32 D_00386D60;
extern u8 *D_003876A0;
extern u8 *gStgRigid;

void StgRigid_Update(void) {
    f32 temp_f21;
    f32 temp_f22;
    f32 var_f20;

    var_f20 = 0.0f;
    if (!(*(s64 *)(D_003876A0 + 0x4D8) & 0x100)) {
        temp_f22 = D_00386D5C;
        temp_f21 = D_00386D60;
        StgRigidList_BeginFrame(*(s32 *)(gStgRigid + 0x12004));
        do {
            var_f20 += temp_f22;
            StgRigidList_UpdateCenters(*(s32 *)(gStgRigid + 0x12004));
            StgRigidList_Collide(*(s32 *)(gStgRigid + 0x12004));
            StgRigidList_AddForces(*(s32 *)(gStgRigid + 0x12004));
            StgRigidList_Step(*(s32 *)(gStgRigid + 0x12004));
        } while (var_f20 <= temp_f21);
        StgRigidList_EndFrame(*(s32 *)(gStgRigid + 0x12004));
        *(s32 *)(gStgRigid + 0x1200C) = StgRigidList_Count(*(s32 *)(gStgRigid + 0x12004));
    }
}
