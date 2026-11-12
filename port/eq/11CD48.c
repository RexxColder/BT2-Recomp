#include "common.h"

s32 *ColMesh_GetPoly(s32 arg0, s32 arg1);
void ColMesh_GetPolyVerts(s32 arg0, s32 *arg1, s32 *arg2, void *arg3, void *arg4);
s32 ColSweep_TestTri(void *arg0, void *arg1, s32 *arg2, f32 *arg3);
void func_003126C8(void *arg0, void *arg1);
extern s32 D_00387F28;

s32 func_0011CD48(u8 *arg0, u8 *arg1) {
    s64 sd[8];
    u8 *buf = (u8 *)sd;
    s32 sp40[4];
    f32 sp50;
    s32 *temp;

    memset(sp40, 0, 0x10);
    temp = ColMesh_GetPoly(D_00387F28, *(s32 *)(arg0 + 0x18));
    if (!(*temp & 0x0C000060)) {
        ColMesh_GetPolyVerts(D_00387F28, temp, (s32 *)buf, buf + 0x10, buf + 0x20);
        func_003126C8(buf + 0x30, (u8 *)temp + 0x10);
        if (ColSweep_TestTri(arg1, buf, sp40, &sp50) != 0) {
            if (sp50 < *(f32 *)(arg1 + 0x80)) {
                *(f32 *)(arg1 + 0x80) = sp50;
                *(s8 *)(arg1 + 0xE0) = 1;
                func_003126C8(arg1 + 0x90, sp40);
                *(s64 *)(arg1 + 0xA0) = sd[0];
                *(s64 *)(arg1 + 0xA8) = sd[1];
                *(s64 *)(arg1 + 0xB0) = sd[2];
                *(s64 *)(arg1 + 0xB8) = sd[3];
                *(s64 *)(arg1 + 0xC0) = sd[4];
                *(s64 *)(arg1 + 0xC8) = sd[5];
                *(s64 *)(arg1 + 0xD0) = sd[6];
                *(s64 *)(arg1 + 0xD8) = sd[7];
                return 1;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}
