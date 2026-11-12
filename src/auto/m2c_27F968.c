#include "m2c_macros.h"

M2C_UNK GfxClut_InitPacket(s32, s32);               /* extern */
M2C_UNK func_0027F898();                            /* extern */
s32 func_0028BAA8(M2C_UNK);                         /* extern */
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);              /* extern */
extern void *D_003876A0;
extern s32 D_00387AF8;

void func_0027F968(s32 arg0) {
    s32 temp_s0;
    s32 temp_v0;

    temp_s0 = arg0 & 0xFFFF;
    if (M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 3) {
        temp_v0 = func_0028BAA8(0x1780);
        D_00387AF8 = temp_v0;
        memset(temp_v0, 0, 0x1780);
        GfxClut_InitPacket(D_00387AF8 + 0x700, temp_s0);
        GfxClut_InitPacket(D_00387AF8 + 0x12C0, temp_s0);
        func_0027F898();
    }
}
