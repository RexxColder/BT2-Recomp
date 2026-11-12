#include "common.h"

s32 ColMesh_GetPoly(s32 arg0, s32 arg1);
void ColMesh_GetPolyVerts(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 ColSphere_TestTri(s32 arg0, s32 arg1, s32 arg2);
void func_003126C8(s32 arg0, s32 arg1);
extern s32 D_00387F28 __attribute__((section(".data")));

s32 func_0011DA78(s32 arg0, s32 arg1) {
    u8 buf[0x50];   /* tamano de locales del original (antes 0x40) */
    s32 sp40[4];
    s32 s0;
    s32 p;
    s32 n;
    s32 k;
    s32 var;

    var = 0;
    s0 = ColMesh_GetPoly(D_00387F28, *(s32 *)(arg0 + 0x18));
    if (*(u32 *)s0 & 0x08000000) {
        return var;
    }
    ColMesh_GetPolyVerts(D_00387F28, s0, (s32)buf, (s32)(buf + 0x10), (s32)(buf + 0x20));
    func_003126C8((s32)(buf + 0x30), s0 + 0x10);
    var = ColSphere_TestTri((s32)sp40, arg1, (s32)buf);
    if (var != 0) {
        p = *(s32 *)(arg1 + 0xC0);
        if (p != 0) {
            n = *(s32 *)p;
            if ((u32)n < 0x40U) {
                u8 *dst = (u8 *)(p + (n << 6) + 0x10);
                for (k = 0; k < 8; k++) {
                    *(s64 *)(dst + k * 8) = *(s64 *)(buf + k * 8);
                }
                *(s32 *)p = *(s32 *)p + 1;
            }
        }
        *(u8 *)(arg1 + 0xC8) = 1;
        var = 1;
    }
    return var;
}
