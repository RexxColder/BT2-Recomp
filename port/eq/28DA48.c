#include "common.h"

void ColMesh_CollectNode(s32 arg0, s32 arg1, s32 arg2);
extern s32 gColMeshBase;
extern s32 gColWalkBuf;
extern s32 gColWalkCount;
extern s32 gColWalkMax;

s32 ColMesh_CollectBox(s32 arg0, s32 arg1, u8 *arg2, s32 arg3) {
    if (*(s32 *)(arg2 + 0x0) <= 0) {
        return 0;
    }
    gColWalkMax = arg0;
    gColWalkBuf = arg1;
    gColWalkCount = 0;
    ColMesh_CollectNode(gColMeshBase + *(s32 *)(arg2 + 0xC) * 4, arg3, 0);
    gColWalkBuf = 0;
    return gColWalkCount;
}
