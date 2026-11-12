#include "m2c_macros.h"

M2C_UNK GfxClut_InitPacket(void *, s32);            /* extern */
M2C_UNK func_0027F538(void *);                      /* extern */
void *memset(void *, s32, s32);                     /* extern */

// Clears 0xA00 bytes of arg0, initializes two CLUT packets, then flips the double buffer index at +0x9C4 and sets the packet pointer at +0x9C0.
void func_0027F628(void *arg0, s32 arg1) {
    s32 temp_s1;
    s32 temp_v1;

    temp_s1 = arg1 & 0xFFFF;
    memset(arg0, 0, 0xA00);
    GfxClut_InitPacket((u8 *)arg0 + 0x40, temp_s1);
    GfxClut_InitPacket((u8 *)arg0 + 0x500, temp_s1);
    M2C_FIELD(arg0, void **, 0x9C0) = (void *) ((u8 *)arg0 + (M2C_FIELD(arg0, s32 *, 0x9C4) * 0x4C0) + 0x40);
    func_0027F538(arg0);
    temp_v1 = M2C_FIELD(arg0, s32 *, 0x9C4) ^ 1;
    M2C_FIELD(arg0, s32 *, 0x9C4) = temp_v1;
    M2C_FIELD(arg0, void **, 0x9C0) = (void *) ((u8 *)arg0 + (temp_v1 * 0x4C0) + 0x40);
}
