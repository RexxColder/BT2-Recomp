#include "common.h"

void Gsc_LinkFile(s32 arg0);
s32 func_002A02B8(s32 arg0);
s32 func_002A03F0(s32 arg0);
extern s32 D_00387DBC;

s32 func_0029F518(s32 arg0) {
    s32 temp_v0;
    u8 *var_s0;
    u8 *var_s1;

    var_s1 = (u8 *)arg0;
    var_s0 = (u8 *)func_002A03F0(arg0);
    temp_v0 = func_002A02B8(D_00387DBC);
    *(s32 *)(var_s0 + 0x10) = 0;
    *(s32 *)(var_s0 + 0xC) = temp_v0;
    D_00387DBC += 1;
    *(s32 *)(var_s0 + 0x14) = (s32)var_s1;
    var_s1 += *(s32 *)(var_s1 + 4);
    *(s32 *)(var_s0 + 0x18) = (s32)var_s1;
    var_s1 = var_s1 + *(s32 *)(var_s1 + 8) + *(s32 *)(var_s1 + 4) + 0x10;
    *(s32 *)(var_s0 + 0x1C) = (s32)var_s1;
    var_s1 = var_s1 + *(s32 *)(var_s1 + 8) + *(s32 *)(var_s1 + 4) + 0x10;
    *(s32 *)(var_s0 + 0x20) = (s32)var_s1;
    Gsc_LinkFile((s32)var_s0);
    return *(s32 *)(var_s0 + 0xC);
}
