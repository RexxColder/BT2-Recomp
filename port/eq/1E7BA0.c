#include "common.h"

void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void func_00129F60(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00126560(void);
extern s32 gBtlCamView;

void func_001E7BA0(s32 arg0) {
    s32 sp[8];
    s32 var_v0;
    s32 var_v1;
    u8 *p;

    p = (u8 *)arg0;
    func_00208DE8(*(s32 *)(p + 0x68), (s32)sp, 3);
    func_00129F60((s32)&sp[4], gBtlCamView + 0x100, (s32)sp, 1);
    if (func_00126560() != 0) {
        var_v0 = (sp[4] - 0x7000) >> 4;
        var_v1 = (sp[5] - 0x7200) >> 4;
    } else {
        var_v0 = 0x100;
        var_v1 = 0xE0;
    }
    *(s32 *)(p + 0x10) = var_v0;
    *(s32 *)(p + 0x14) = var_v1;
    *(f32 *)(p + 0x20) = 4.0f;
    *(f32 *)(p + 0x24) = 1.5f;
    *(s32 *)(p + 0x28) = 0;
    *(s32 *)(p + 0x18) = 0;
    *(s32 *)(p + 0x1C) = 0;
    *(s32 *)(p + 0x38) = *(s32 *)(p + 0x38) | 2;
}
