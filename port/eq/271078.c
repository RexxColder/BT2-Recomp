#include "common.h"

s32 FlushCache(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 sceGsResetGraph(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 sceGsSetDefDBuff(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0, s32 t1, s32 t2);
s32 sceGsSyncVCallback(u8 *arg0);
extern u8 func_001006D8[] __attribute__((section(".data")));
extern u8 gGfx[] __attribute__((section(".data")));

void func_00271078(void) {
    s64 temp_t0;
    s64 temp_t1;
    s64 temp_t2;
    s64 temp_t3;

    sceGsResetGraph(0, 1, 2, 0);
    sceGsSetDefDBuff(gGfx, 0, 0x200, 0x1C0, 3, 0x31, 1);
    temp_t0 = (s64)0x8E009000ULL;
    temp_t1 = (s64)0xFE00 << 46;
    temp_t2 = ((s64)0x7200 << 32) | 0x7000;
    temp_t3 = (((s64)0x01BF0000 << 16) | 0x1FF) << 16;
    *(s64 *)(gGfx + 0x160) = 0x310000E0;
    *(s64 *)(gGfx + 0x200) = 0x72007000;
    *(s64 *)(gGfx + 0x210) = temp_t0;
    *(s64 *)(gGfx + 0x1F0) = temp_t1;
    *(s64 *)(gGfx + 0x10) = 0x1000;
    *(s64 *)(gGfx + 0x60) = 0x80000;
    *(s64 *)(gGfx + 0x38) = 0x1070;
    *(s64 *)(gGfx + 0x150) = 0x80070;
    *(s64 *)(gGfx + 0x170) = temp_t2;
    *(s64 *)(gGfx + 0x180) = temp_t3;
    *(s64 *)(gGfx + 0x110) = 0x72007000;
    *(s64 *)(gGfx + 0x120) = temp_t0;
    *(s64 *)(gGfx + 0x100) = temp_t1;
    *(s64 *)(gGfx + 0x80) = temp_t2;
    *(s64 *)(gGfx + 0x90) = temp_t3;
    *(s64 *)(gGfx + 0x70) = 0x310000E0;
    FlushCache(0, 0x1070, 0x80070, 0x72007000);
    sceGsSyncVCallback(func_001006D8);
}
