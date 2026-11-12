#include "common.h"

s32 BtlChar_GetPos(s32 arg0);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);

/* calls func_00312638 with the char's +0xA0 sub-block twice and arg1 (arg0 passes through to BtlChar_GetPos) */
void func_0020E440(s32 arg0, s32 arg1) {
    s32 p = BtlChar_GetPos(arg0) + 0xA0;
    func_00312638(p, p, arg1);
}
