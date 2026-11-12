#include "m2c_macros.h"

void *memset(void *, int, unsigned int);
void GfxClut_InitPacket(s32 arg0, s32 arg1);

void func_0027C2E0(s32 arg0, s32 arg1) {
    memset((void *)arg0, 0, 0x5C0);
    GfxClut_InitPacket(arg0, arg1 & 0xFFFF);
}
