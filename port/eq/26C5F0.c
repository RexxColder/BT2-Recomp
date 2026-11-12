#include "common.h"

void func_00270198(s32 arg0);
s32 func_0026FFE0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x0026C5F0(obj, a1, a2, a3, t0, t1): if obj->+8 is set, func_00270198(it) and clear it; then
 * obj->+8 = func_0026FFE0(t1->+0x1C, a1, a2, a3, t0). */
void func_0026C5F0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 *arg5) {
    s32 h = *(s32 *)(arg0 + 8);

    if (h != 0) {
        func_00270198(h);
        *(s32 *)(arg0 + 8) = 0;
    }
    *(s32 *)(arg0 + 8) = func_0026FFE0(*(u8 **)(arg5 + 0x1C), arg1, arg2, arg3, arg4);
}
