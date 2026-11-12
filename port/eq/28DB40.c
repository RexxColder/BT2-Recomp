#include "common.h"

/* 0x0028DB40: if (*(s32 *)a0 <= 0 || a3 == 0) return 0; node = gColMeshBase + (a0->+0xC << 2);
   gColWalkBox = a1; gColWalkCb = a3; gColWalkCtx = a2; gColWalkCount = 0; ColMesh_WalkNode(node, a1, 0, a3);
   return gColWalkCount. */
extern u8 D_00387D70[];
extern s32 D_00387D74;
extern s32 D_00387D80;
extern s32 D_00387D84;
extern s32 D_00387EC8;
void ColMesh_WalkNode(s32 arg0, s32 arg1, s32 arg2);

s32 func_0028DB40(void *a0, s32 a1, s32 a2, s32 a3) {
    u8 *node;
    u8 *m;

    m = (u8 *)a0;
    if (*(s32 *)m <= 0) {
        return 0;
    }
    if (a3 == 0) {
        return 0;
    }
    node = *(u8 **)D_00387D70 + (*(s32 *)(m + 0xC) << 2);
    D_00387D80 = a1;
    D_00387D84 = a3;
    D_00387EC8 = a2;
    D_00387D74 = 0;
    ColMesh_WalkNode((s32)node, a1, 0);
    return D_00387D74;
}
