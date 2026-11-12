#include "common.h"

void GfxClut_InitPacket(s32 arg0, s32 arg1, s32 arg2);
void func_00284758(s32 arg0);

void func_002847E8(void *arg0, s32 arg1, s32 arg2) {
    GfxClut_InitPacket((s32) arg0, arg1 & 0xFFFF, arg2);
    func_00284758(*(s32 *) ((u8 *) arg0 + 0x490));
}
