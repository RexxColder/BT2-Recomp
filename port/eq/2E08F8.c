#include "common.h"

#define PTR(v) ((u8 *)(s32)(v))
#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))

void StgSlot_Call16(void *obj, void *out);
void StgSlot_Call17(void *obj, void *out);
void StgSlot_Call18(void *obj, void *a, void *b, void *c);
void StgSlot_Call19(void *obj, void *a, void *b);
void *memcpy(void *dst, const void *src, u32 n);

/* 0x002E08F8: four slot calls on the object at +0x3B4 fill a 0x98-byte frame; its first 0x80 bytes are copied
 * to +0x1D0, and the words at 0x80..0x94 are stored to +0x2A8..+0x2BC (the word at 0x84 divided by 2048,
 * rounded toward zero). */
void func_002E08F8(s32 arg0) {
    u8 fr[0xa0];   /* tamano de locales del original (antes 0x98) */
    u8 *s0;
    s32 v;

    s0 = PTR(arg0);
    StgSlot_Call16(PTR(LD32(s0, 0x3B4)), fr);
    StgSlot_Call17(PTR(LD32(s0, 0x3B4)), fr + 0x80);
    StgSlot_Call18(PTR(LD32(s0, 0x3B4)), fr + 0x84, fr + 0x88, fr + 0x8C);
    StgSlot_Call19(PTR(LD32(s0, 0x3B4)), fr + 0x90, fr + 0x94);

    memcpy(s0 + 0x1D0, fr, 0x80);

    LD32(s0, 0x2A8) = LD32(fr, 0x80);
    v = LD32(fr, 0x84);
    if (v < 0) {
        v = v + 0x7FF;
    }
    v = v >> 11;
    LD32(s0, 0x2AC) = v;
    LD32(s0, 0x2BC) = LD32(fr, 0x88);
    LD32(s0, 0x2B4) = LD32(fr, 0x90);
    LD32(s0, 0x2B8) = LD32(fr, 0x94);
}
