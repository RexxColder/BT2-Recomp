#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
void EftRay_CreateByValue(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                          f32 farg8, f32 farg9, f32 farg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14,
                          s32 arg15, s32 arg16, s32 arg17, s32 arg18, s32 arg19);

void EftRay_StartScreen(s32 arg0, s32 arg1, s32 arg2, f32 farg0) {
    s32 sp[0x18];

    memset(sp, 0, 0x10);
    *(f32 *)&sp[3] = 1.0f;
    *((u8 *)sp + 0x50) = 1;
    EftRay_CreateByValue(sp, 0x80, 3, 0x24, 0xC0, 0xC0, 0xC0, 0x80, farg0, 800.0f, 1.5f, 0, 0, 3, 0x24, arg0,
                         1, 1, (s32)(f32)arg1, (s32)(f32)arg2);
}
