#include "common.h"

void *memset(void *s, s32 c, u32 n);
void GfxClut_InitPacket(u8 *arg0, s32 arg1, s32 arg2);
s32 func_0027EBA8(u8 *arg0);

s32 func_0027EBD0(u8 *arg0, s32 arg1) {
    memset(arg0, 0, 0x540);
    GfxClut_InitPacket(arg0 + 0x40, arg1 & 0xFFFF, 0);
    return func_0027EBA8(arg0);
}
