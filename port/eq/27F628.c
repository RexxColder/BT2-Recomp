#include "common.h"

/* 0x0027F628: memset(a0, 0, 0xA00); GfxClut_InitPacket(a0 + 0x40, a1 & 0xFFFF); GfxClut_InitPacket(a0 + 0x500, a1 & 0xFFFF);
   idx = a0->+0x9C4; a0->+0x9C0 = a0 + idx * 1216 + 0x40; func_0027F538(a0);
   idx = a0->+0x9C4 ^ 1; a0->+0x9C4 = idx; a0->+0x9C0 = a0 + idx * 1216 + 0x40. */
void GfxClut_InitPacket();
void func_0027F538(s32 arg0);

void func_0027F628(s32 a0, s32 a1) {
    u8 *s;
    s32 idx;
    s32 s1;

    s = (u8 *)a0;
    s1 = a1 & 0xFFFF;
    memset(s, 0, 0xA00);
    GfxClut_InitPacket(a0 + 0x40, s1);
    GfxClut_InitPacket(a0 + 0x500, s1);
    idx = *(s32 *)(s + 0x9C4);
    *(s32 *)(s + 0x9C0) = (s32)(s + idx * 1216 + 0x40);
    func_0027F538(a0);
    idx = *(s32 *)(s + 0x9C4) ^ 1;
    *(s32 *)(s + 0x9C4) = idx;
    *(s32 *)(s + 0x9C0) = (s32)(s + idx * 1216 + 0x40);
}
