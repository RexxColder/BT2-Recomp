#include "common.h"

void func_0012A360(u8 *a0, u8 *a1, s32 a2, f32 farg0);
void func_00129C28(void *a0, void *a1);
u8 *EftRibbon_Create(u8 *a0);
void EftRibbon_SetUnk58(u8 *a0, s32 a1);
void EftRibbon_SetFadeTime(u8 *a0, s32 a1);
void EftRibbon_SetPos(u8 *a0, void *a1);
void EftRibbon_SetEnd(u8 *a0, s32 a1, s32 a2);
void EftRibbon_SetSize(u8 *a0, f32 farg0);
void EftRibbon_Kill(u8 *a0);
void EftRibbon_Stop(u8 *a0);
void *memset(void *arg0, s32 arg1, u32 arg2);
void *memcpy(void *arg0, void *arg1, u32 arg2);

/* 0x0014FB50: ribbon effect. arg4 holds the handle; flag bits in arg5: 1 create when empty,
 * 8 set position and end, 0x20 set size, 4 kill (handle cleared), 2 stop. arg8..arg10 are stack
 * arguments of the caller; arg9 is also passed to func_00129C28. */
void func_0014FB50(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, u8 *arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, u8 *arg9, s32 arg10, f32 farg0, f32 farg1) {
    u8 fr[0x90];
    u8 *h;

    func_0012A360(fr, arg9, arg7, 1.0f);
    h = *(u8 **)arg4;
    if ((arg5 & 1) != 0 && h == NULL) {
        *(u8 *)(fr + 0x50) = 1;
        *(s32 *)(fr + 0x54) = arg6;
        *(s32 *)(fr + 0x58) = 0;
        *(f32 *)(fr + 0x5C) = farg1;
        memset(fr + 0x60, 0, 0x10);
        memset(fr + 0x70, 0, 0x10);
        *(s32 *)(fr + 0x80) = *(u8 *)(arg1 + 3);
        *(u8 **)(fr + 0x84) = arg0 + 0x1C8;
        *(s32 *)(fr + 0x88) = arg2;
        *(s32 *)(fr + 0x8C) = arg3;
        memcpy(fr + 0x10, fr + 0x50, 0x40);
        func_00129C28(fr + 0x30, arg9);
        func_00129C28(fr + 0x20, fr);
        h = EftRibbon_Create(fr + 0x10);
        *(u8 **)arg4 = h;
        EftRibbon_SetUnk58(h, arg10);
        EftRibbon_SetFadeTime(h, *(u8 *)(arg1 + 4));
        h = *(u8 **)arg4;
    }
    if (h == NULL) {
        return;
    }

    if ((arg5 & 8) != 0) {
        EftRibbon_SetPos(h, fr);
        EftRibbon_SetEnd(h, arg8, (arg5 & 0x10) != 0);
    }
    if ((arg5 & 0x20) != 0) {
        EftRibbon_SetSize(h, farg1);
    }
    if ((arg5 & 4) != 0) {
        EftRibbon_Kill(h);
        *(u8 **)arg4 = NULL;
        return;
    }
    if ((arg5 & 2) != 0) {
        EftRibbon_Stop(h);
    }
}
