#include "common.h"

void GfxClut_InitPacket(s32 arg0, s32 arg1, s32 arg2);
void GfxDepthFog_BuildClut(s32 arg0);

void func_00285D68(void *arg0, s32 arg1, s32 arg2) {
    GfxClut_InitPacket((s32) arg0, arg1 & 0xFFFF, arg2);
    GfxDepthFog_BuildClut(*(s32 *) ((u8 *) arg0 + 0x490));
}
