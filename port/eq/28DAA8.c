#include "common.h"

s32 ColNode_IsLeaf(s32 arg0);
s32 ColNode_TestBox(s32 arg0, s32 arg1, s32 arg2);
extern s32 (*gColWalkCb)(s32 arg0, s32 arg1);
extern s32 gColWalkCount;
extern s32 gColWalkCtx;

void ColMesh_WalkNode(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a2;
    u8 *temp_s0;

    temp_a2 = arg2 << 5;
    temp_s0 = (u8 *)arg0 + temp_a2;
    if (ColNode_TestBox((s32)temp_s0, arg1, temp_a2) != 0) {
        if (ColNode_IsLeaf((s32)temp_s0) != 0) {
            gColWalkCount |= gColWalkCb((s32)temp_s0, gColWalkCtx);
            return;
        }
        ColMesh_WalkNode(arg0, arg1, *(s32 *)(temp_s0 + 0x18));
        ColMesh_WalkNode(arg0, arg1, *(s32 *)(temp_s0 + 0x1C));
    }
}
