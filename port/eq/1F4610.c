#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
s32 EftRay_Create(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  f32 farg8, f32 farg9, f32 farg10, f32 farg11, f32 farg12, s32 arg13, s32 arg14,
                  s32 arg15, s32 arg16, s32 arg17, s32 arg18, s32 arg19);
extern f32 D_0038575C;
extern u8 *D_00387920;

void func_001F4610(void) {
    s32 sp[24];

    if ((D_00387920 != NULL) && (*(s32 *)(D_00387920 + 0x60) == 0)) {
        memset(sp, 0, 0x10);
        *(f32 *)&sp[0] = 256.0f;
        *(f32 *)&sp[1] = 224.0f;
        sp[2] = 0;
        *(f32 *)&sp[3] = 1.0f;
        sp[4] = 0xC0;
        sp[5] = 0xC0;
        *((u8 *)sp + 0x50) = 0;
        *(s32 *)(D_00387920 + 0x60) = EftRay_Create(sp, 0x70, 0x24, 0, 0xC0, 0xC0, 0xC0, 0x70, 10.0f, 600.0f,
                                                    7.0f, 40.0f, D_0038575C, 1, 0x24, 0, 1, 1, 0, 0);
    }
}
