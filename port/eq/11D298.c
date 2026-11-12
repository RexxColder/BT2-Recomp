#include "common.h"

void *memset(void *, int, unsigned int);
void *memcpy(void *, const void *, unsigned int);
s32 ColMesh_GetPoly(s32 arg0, s32 arg1);
void ColMesh_GetPolyVerts(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_003126C8(s32 arg0, s32 arg1);
s32 ColSphere_TestTri(s32 arg0, s32 arg1, s32 arg2);
void StgCol_PushSphere(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00387F28;

/* 0x0011D298 (StgCol_PushCb in BT3): mesh callback of the body sphere at ctx+0x10 (box at ctx+0x30). Polygon
 * node->poly: returns 0 when its flags have 0x08000000 (not solid). Else the triangle (three vertices, normal copied
 * from poly+0x10 to tri+0x30) is tested against the sphere; on a hit the sphere is pushed out, the 0x20-byte polygon
 * header is copied to ctx+0x50, ctx byte 0 = 1, and it returns 1. Otherwise returns 0. */
s32 StgCol_PushCb(u8 *node, u8 *ctx) {
    f32 pos[4];
    u8 tri[0x50];   /* tamano de locales del original (antes 0x40) */
    u8 *poly;

    memset(pos, 0, 0x10);
    pos[3] = 1.0f;
    poly = (u8 *)ColMesh_GetPoly(D_00387F28, *(s32 *)(node + 0x18));
    if (*(s32 *)poly & 0x08000000) {
        return 0;
    }
    ColMesh_GetPolyVerts(D_00387F28, (s32)poly, (s32)tri, (s32)(tri + 0x10), (s32)(tri + 0x20));
    func_003126C8((s32)(tri + 0x30), (s32)(poly + 0x10));
    if (ColSphere_TestTri((s32)pos, (s32)(ctx + 0x10), (s32)tri) == 0) {
        return 0;
    }
    StgCol_PushSphere((s32)(ctx + 0x10), (s32)(ctx + 0x30), (s32)pos);
    memcpy(ctx + 0x50, poly, 0x20);
    ctx[0] = 1;
    return 1;
}
