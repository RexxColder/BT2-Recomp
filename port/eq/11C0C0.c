#include "common.h"

u8 *ColMesh_GetPoly(s32 arg0, s32 arg1);
void ColMesh_GetPolyVerts(s32 arg0, u8 *arg1, void *arg2, void *arg3, void *arg4);
s32 ColSweep_TestTri(void *arg0, void *arg1, f32 *arg2, f32 *arg3);
void func_003126C8(void *arg0, f32 *arg1);
extern f32 D_00384058;
extern s32 D_00387F28;
void *memset(void *arg0, s32 arg1, u32 arg2);

s32 func_0011C0C0(u8 *arg0, u8 *arg1) {
    u8 fb[0x4c];   /* tamano de locales del original (antes 0x40) */
    f32 vec40[4];
    f32 sp50;
    u8 *temp_v0;
    u8 *temp_a0;
    s32 i;

    memset(vec40, 0, 0x10);
    vec40[3] = 1.0f;

    temp_v0 = ColMesh_GetPoly(D_00387F28, *(s32 *)(arg0 + 0x18));
    if (!(*(s32 *)temp_v0 & 0x08000000)) {
        ColMesh_GetPolyVerts(D_00387F28, temp_v0, fb, fb + 0x10, fb + 0x20);
        func_003126C8(fb + 0x30, (f32 *)(temp_v0 + 0x10));
        if (ColSweep_TestTri(arg1, fb, vec40, &sp50) != 0) {
            if (sp50 < *(f32 *)(arg1 + 0x84)) {
                *(f32 *)(arg1 + 0x84) = sp50;
                *(u8 *)(arg1 + 0x88) = 1;
                func_003126C8(*(u8 **)(arg1 + 0x80) + 0x20, vec40);
                temp_a0 = *(u8 **)(arg1 + 0x80);
                for (i = 0; i < 0x40; i++) {
                    temp_a0[0x40 + i] = fb[i];
                }
                if (sp50 < D_00384058) {
                    func_003126C8(*(u8 **)(arg1 + 0x80) + 0x30, vec40);
                    return 1;
                }
                *(f32 *)(*(u8 **)(arg1 + 0x80) + 0x30) = vec40[0] - (*(f32 *)(fb + 0x30) * *(f32 *)(arg1 + 0x20));
                *(f32 *)(*(u8 **)(arg1 + 0x80) + 0x34) = vec40[1] - (*(f32 *)(fb + 0x34) * *(f32 *)(arg1 + 0x20));
                *(f32 *)(*(u8 **)(arg1 + 0x80) + 0x38) = vec40[2] - (*(f32 *)(fb + 0x38) * *(f32 *)(arg1 + 0x20));
                *(f32 *)(*(u8 **)(arg1 + 0x80) + 0x3C) = 1.0f;
                return 1;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}
