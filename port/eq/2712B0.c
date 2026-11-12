#include "common.h"

/* GS privileged (display) registers, as in src/sys/gfx_271178.c. */
#define GS_PMODE ((volatile u64 *)0x12000000)
#define GS_DISPFB1 ((volatile u64 *)0x12000070)
#define GS_DISPLAY1 ((volatile u64 *)0x12000080)
#define GS_DISPFB2 ((volatile u64 *)0x12000090)
#define GS_DISPLAY2 ((volatile u64 *)0x120000A0)
#define GS_EXTWRITE ((volatile u64 *)0x120000D0)

extern u8 *D_00387F2C;
extern s32 D_003B0A84 __attribute__((section(".data")));

/* Same logic as Gfx_SetDisplayRegs in BT3 (src/sys/gfx.c): the first argument is unused (it is overwritten before use). */
void Gfx_SetDisplayRegs(s32 field, s32 blend) {
    u8 *save;
    s32 w;
    s32 h;
    s32 dx;
    s32 dy;
    u64 size;
    u64 display1;
    u64 display2;
    s32 dispfb;
    u64 pmode;

    save = D_00387F2C;
    w = *(s32 *)(save + 0x109C);
    h = *(s32 *)(save + 0x10A0);
    dx = (s32)((u32)w << 2) + 0x27C;
    dy = (s32)((u32)h << 1);
    size = 0x1BF9FF02000000ULL;
    display2 = (u64)(s64)dx | ((u64)(s64)(dy + 0x32) << 12) | size;
    display1 = (u64)(s64)dx | ((u64)(s64)(dy + 0x33) << 12) | size;
    dispfb = ((D_003B0A84 & 1) != 0) ? 0x1000 : 0x1070;
    pmode = ((blend & 1) != 0) ? 0x7F23ULL : 0xFF23ULL;

    *GS_PMODE = pmode;
    *GS_DISPFB2 = (u64)(s64)dispfb;
    *GS_DISPLAY2 = display2;
    *GS_DISPFB1 = (u64)(s64)dispfb;
    *GS_DISPLAY1 = display1;
    *GS_EXTWRITE = 0;
}
