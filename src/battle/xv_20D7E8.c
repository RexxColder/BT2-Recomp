#include "common.h"

s32 BtlChar_GetPos(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/* if func_00211310(arg0, 0, 1): func_002113C0(arg0, 1, 0x80, 1); char->+0xCC = farg0; char->+0xD0 = farg1 */
void func_0020D7E8(s32 arg0, f32 farg0, f32 farg1) {
    void *p;
    if (func_00211310(arg0, 0, 1) != 0) {
        func_002113C0(arg0, 1, 0x80, 1);
        p = (void *)BtlChar_GetPos(arg0);
        *(f32 *)((u8 *)p + 0xCC) = farg0;
        *(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0xD0) = farg1;
    }
}
