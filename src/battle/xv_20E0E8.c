#include "common.h"

void ColSeg_Set(s32 arg0, s32 arg1, s32 arg2);
s32 func_0011E1C8(s32 arg0);
s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
s32 func_00211288(s32 arg0);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/* two objects (func_00211288(0), func_00211288(1)) get func_002113C0(obj, 0, 0x400, 0); their +0x1534 pointers
 * fill two 16-byte buffers, ColSeg_Set on them, and when func_0011E1C8 says so the 0x400 call is repeated with 1 */
void func_0020E0E8(void) {
    s32 sp[8];
    s32 sp20[4];
    s32 sp30[4];
    s32 var_s2;
    s32 var_s3;

    var_s2 = func_00211288(0);
    var_s3 = func_00211288(1);
    func_002113C0(var_s2, 0, 0x400, 0);
    func_002113C0(var_s3, 0, 0x400, 0);
    func_00208DE8(*(s32 *)((u8 *)var_s2 + 0x1534), (s32)sp20, 0x2F);
    func_00208DE8(*(s32 *)((u8 *)var_s3 + 0x1534), (s32)sp30, 0x2F);
    ColSeg_Set((s32)sp, (s32)sp20, (s32)sp30);
    if (func_0011E1C8((s32)sp) != 0) {
        func_002113C0(var_s2, 0, 0x400, 1);
        func_002113C0(var_s3, 0, 0x400, 1);
    }
}
