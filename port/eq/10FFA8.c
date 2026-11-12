#include "common.h"

s32 func_0010B0A0(s32 arg0);
s32 BtlRec_CallFlagged(s32 arg0, s32 arg1, s32 arg2);
s32 func_00113B00(s32 arg0, s32 arg1, s32 arg2);
void func_00113CB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001140A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_00114508(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 *D_00387A40;

s32 func_0010FFA8(s32 arg0, s32 arg1, s32 arg2) {
    s32 obj;
    s32 rec;
    s32 s3;
    s32 s0;

    obj = func_0010B0A0(arg1);
    rec = obj + 0x960;
    s3 = arg2 * 0x18580;
    s0 = *(s32 *)(s3 + *D_00387A40 + 0x58);
    func_00114508(rec, 2, 0, 2);
    if (s0 != 0) {
        func_00113CB8(rec, 0, s0, 0);
        func_00113B00(rec, 4, 0);
        if (*(s32 *)(s3 + *D_00387A40 + 0xAF0) & 0x40000) {
            *(s8 *)(rec + 0x16) = -1;
            *(s8 *)(rec + 0x17) = 0x60;
            *(s8 *)(rec + 0x19) = -0x80;
        } else {
            *(s8 *)(rec + 0x19) = -0x80;
            *(s8 *)(rec + 0x16) = -0x80;
            *(s8 *)(rec + 0x17) = -0x80;
        }
        *(s8 *)(rec + 0x18) = -0x80;
        *(s32 *)rec = *(s32 *)rec | 0x100;
        if (arg1 == 1) {
            *(s16 *)(rec + 0x14) = (s16)arg1;
        } else {
            *(s16 *)(rec + 0x14) = 0;
        }
        if (arg1 == 1) {
            func_001140A8(rec, 0, 1, 0, 2);
        }
        return BtlRec_CallFlagged(rec, 1, 2);
    }
    return 0;
}
