#include "common.h"

extern s32 D_00387930;
extern s32 D_00387E18;

s32 func_00211288(s32 arg0);
void *BtlChar_GetPos(s32 arg0);
void *func_002B1DD0(s32 arg0);
void func_00209018(s32 arg0, void *arg1, s32 arg2);
f32 func_0029DFD0(void *arg0);

/* 0x00208CC8 BtlCharApi_GetSpeed(i): for i < 2 with D_00387930 set, the float at +0xC0 of the position of
 * func_00211288(i); else for i < 3 with D_00387E18 set, the float at +0x154 of func_002B1DD0(i); else
 * func_00209018(i, buf, 0) and func_0029DFD0(buf). */
f32 BtlCharApi_GetSpeed(s32 arg0) {
    s32 buf[4];
    u8 *p;

    if (D_00387930 != 0 && (u32)arg0 < 2U) {
        p = (u8 *)BtlChar_GetPos(func_00211288(arg0));
        return *(f32 *)(p + 0xC0);
    }
    if (D_00387E18 != 0 && (u32)arg0 < 3U) {
        p = (u8 *)func_002B1DD0(arg0);
        return *(f32 *)(p + 0x154);
    }
    func_00209018(arg0, buf, 0);
    return func_0029DFD0(buf);
}
