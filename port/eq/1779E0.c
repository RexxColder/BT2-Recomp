#include "common.h"

void *func_00177980(void);
void func_00129C28(s32 arg0, s32 arg1);
extern void *D_00387E94;

void func_001779E0(s32 arg0, void *arg1, void *arg2, void *arg3, f32 farg0, f32 farg1, f32 farg2) {
    s64 c1[2];
    s64 c2[2];
    s64 c3[2];
    u8 *temp_v0;
    u8 *G;
    u8 *temp_v1;

    c1[0] = ((s64 *)arg1)[0];
    c1[1] = ((s64 *)arg1)[1];
    c2[0] = ((s64 *)arg2)[0];
    c2[1] = ((s64 *)arg2)[1];
    c3[0] = ((s64 *)arg3)[0];
    c3[1] = ((s64 *)arg3)[1];

    temp_v0 = (u8 *)func_00177980();
    if (temp_v0 != NULL) {
        G = (u8 *)D_00387E94;
        if (*(void **)(G + 0x3F5C) != NULL) {
            *(s32 *)(temp_v0 + 0x50) = 0;
            *(void **)(temp_v0 + 0x4C) = *(void **)(G + 0x3F60);
        } else {
            *(void **)(G + 0x3F5C) = temp_v0;
            *(void **)(temp_v0 + 0x4C) = NULL;
            *(s32 *)(temp_v0 + 0x50) = 0;
        }
        temp_v1 = *(u8 **)(G + 0x3F60);
        if (temp_v1 != NULL) {
            *(void **)(temp_v1 + 0x50) = temp_v0;
        }
        *(void **)(G + 0x3F60) = temp_v0;

        *(s32 *)(temp_v0 + 0x30) = arg0;
        func_00129C28((s32)temp_v0, (s32)c1);
        func_00129C28((s32)(temp_v0 + 0x10), (s32)c2);
        func_00129C28((s32)(temp_v0 + 0x20), (s32)c3);
        *(f32 *)(temp_v0 + 0x34) = farg0;
        *(f32 *)(temp_v0 + 0x38) = farg2;
        *(f32 *)(temp_v0 + 0x3C) = 160.0f;
        *(s32 *)(temp_v0 + 0x44) = 1;
        *(u8 *)(temp_v0 + 0x49) = 0;
        *(u8 *)(temp_v0 + 0x48) = 0;
        *(f32 *)(temp_v0 + 0x40) = 160.0f / (farg1 * 30.0f);
        *(s32 *)(G + 0x3D44) = *(s32 *)(G + 0x3D44) + 1;
    }
}
