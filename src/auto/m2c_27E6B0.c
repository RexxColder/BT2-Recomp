#include "m2c_macros.h"

M2C_UNK GfxClut_InitPacket(s32, s32);               /* extern */
M2C_UNK func_0027DC10(s32);                         /* extern */

void func_0027E6B0(void *arg0, s32 arg1) {
    GfxClut_InitPacket(arg0 + 0x40, arg1 & 0xFFFF);
    func_0027DC10(M2C_FIELD(arg0, s32 *, 0x4D0));
}
