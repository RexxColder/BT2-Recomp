#include "m2c_macros.h"

extern s32 ColMesh_GetPoly(s32 arg0, s32 arg1);
extern void ColMesh_GetPolyVerts(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 ColSeg_TestTri(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_003126C8(s32 arg0, s32 arg1);
extern s32 D_00387F28;

s32 func_0011D978(u8 *arg0, u8 *arg1) {
    s32 sp[4];
    s32 sp10[4];
    s32 sp20[4];
    s32 sp30[4];
    s32 sp40[4];
    f32 sp50;
    u8 *s1;
    u8 *s3;

    s1 = (u8 *)ColMesh_GetPoly(D_00387F28, *(s32 *)(arg0 + 0x18));
    s3 = s1 + 0x10;
    if (*(s32 *)s1 & 0x08000000) {
        return 0;
    }
    ColMesh_GetPolyVerts(D_00387F28, (s32)s1, (s32)sp, (s32)sp10, (s32)sp20);
    func_003126C8((s32)sp30, (s32)s3);
    if (ColSeg_TestTri((s32)(arg1 + 0x20), (s32)sp, (s32)sp40, (s32)&sp50) == 0) {
        return 0;
    }
    if (sp50 < *(f32 *)(arg1 + 0x80)) {
        *(s64 *)(arg1 + 0xA0) = *(s64 *)s1;
        *(s64 *)(arg1 + 0xA8) = *(s64 *)(s1 + 8);
        *(s64 *)(arg1 + 0xB0) = *(s64 *)s3;
        *(s64 *)(arg1 + 0xB8) = *(s64 *)(s1 + 0x18);
        func_003126C8((s32)(arg1 + 0x90), (s32)sp40);
        *(u8 *)(arg1 + 0xC8) = 1;
        *(f32 *)(arg1 + 0x80) = sp50;
        return 1;
    }
    return 0;
}
