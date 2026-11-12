#include "common.h"

void Flash_CxformIdentity(s32 arg0);
void func_0026DEF0(s32 arg0);
void func_0026FBD0(s32 arg0);

void func_0026FEE0(s32 arg0) {
    u8 *var_s1;
    u32 var_s3;
    s32 var_s2;
    u8 *var_s0;

    var_s1 = (u8 *)arg0;
    var_s3 = 0;
    if (*(u32 *)(var_s1 + 4) != 0) {
        var_s2 = 0;
        var_s0 = *(u8 **)var_s1;
        for (;;) {
            var_s3 += 1;
            var_s0 += var_s2;
            var_s2 += 0xC0;
            memset(var_s0, 0, 0x40);
            *(s32 *)(var_s0 + 0x44) = 0;
            memset(var_s0 + 0x48, 0, 0x60);
            *(f32 *)(var_s0 + 0x54) = 1.0f;
            func_0026FBD0((s32)(var_s0 + 0x78));
            Flash_CxformIdentity((s32)(var_s0 + 0x90));
            func_0026DEF0((s32)(var_s0 + 0xA8));
            if (!(var_s3 < *(u32 *)(var_s1 + 4))) {
                break;
            }
            var_s0 = *(u8 **)var_s1;
        }
    }
}
