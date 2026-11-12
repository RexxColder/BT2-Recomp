#include "common.h"

u8 *ColMesh_GetPoly(s32 arg0, s32 arg1);
void ColMesh_GetPolyVerts(s32 arg0, void *arg1, void *arg2, void *arg3, void *arg4);
s32 func_0011E3B8(s32 arg0, void *arg1, s32 arg2);
void func_003126C8(void *arg0, void *arg1);
f32 sceVu0InnerProduct(void *arg0, void *arg1);
extern u8 D_00344C60[] __attribute__((section(".data")));
extern s32 D_00387F28;

s32 func_0011E4F8(u8 *arg0, s32 arg1) {
    s32 buf[16];
    u8 *temp_v0;
    u8 *temp_s1;
    s32 temp_a2;
    s32 var_v0;

    temp_v0 = ColMesh_GetPoly(D_00387F28, *(s32 *)(arg0 + 0x18));
    temp_s1 = temp_v0 + 0x10;
    var_v0 = 0;
    if (sceVu0InnerProduct(D_00344C60, temp_s1) < 0.0f) {
        ColMesh_GetPolyVerts(D_00387F28, temp_v0, buf, &buf[4], &buf[8]);
        func_003126C8(&buf[12], temp_s1);
        temp_a2 = *(s32 *)temp_v0;
        var_v0 = 0;
        if (!(temp_a2 & 0x0A000060)) {
            var_v0 = func_0011E3B8(arg1, buf, temp_a2) != 0;
        }
    }
    return var_v0;
}
