#include "common.h"

void *memset(void *s, s32 c, u32 n);
void GfxClut_InitPacket(u8 *arg0, s32 arg1, s32 arg2);

void func_00280940(u8 *arg0, s32 arg1, s32 arg2) {
    memset(arg0, 0, 0x5C0);
    GfxClut_InitPacket(arg0, ((arg1 & 0xFFFF) + 4) & 0xFFFF, arg2);
}
