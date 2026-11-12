#include "common.h"

s32 ColNode_IsLeaf(u8 *arg0);
s32 ColNode_TestBox(u8 *arg0, s32 arg1);
void ColMesh_CollectNode(u8 *arg0, s32 arg1, s32 arg2);
extern u8 *gColWalkBuf;
extern s32 gColWalkCount;
extern s32 gColWalkMax;

void ColMesh_CollectNode(u8 *arg0, s32 arg1, s32 arg2) {
    s32 temp_a2;
    u8 *temp_s1;

    temp_a2 = arg2 * 32;
    temp_s1 = arg0 + temp_a2;
    if (ColNode_TestBox(temp_s1, arg1) != 0) {
        if (ColNode_IsLeaf(temp_s1) == 0) {
            ColMesh_CollectNode(arg0, arg1, *(s32 *)(temp_s1 + 0x18));
            ColMesh_CollectNode(arg0, arg1, *(s32 *)(temp_s1 + 0x1C));
        } else if (gColWalkBuf != NULL) {
            if (gColWalkCount < gColWalkMax) {
                *(u16 *)(gColWalkBuf + gColWalkCount * 2) = *(u16 *)(temp_s1 + 0x18);
                gColWalkCount += 1;
            }
        } else {
            gColWalkCount += 1;
        }
    }
}
