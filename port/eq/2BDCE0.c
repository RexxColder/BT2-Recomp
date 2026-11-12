#include "common.h"

void func_002BDC28(s32 arg0, s32 arg1, void *arg2);
void func_002BDC58(s32 arg0, s32 arg1, void *arg2);
void func_002DA3A8(s32 arg0, s32 arg1, s32 arg2);

void func_002BDCE0(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s32 sp[4];
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s3;
    u8 *temp_s1;

    temp_s1 = *(u8 **)(arg0 + 0x2004);
    temp_s3 = *(s32 *)(temp_s1 + 4);
    func_002BDC28(temp_s3, *(s32 *)(temp_s1 + 8), sp);
    temp_s0 = (arg2 < sp[1]) ? arg2 : sp[1];
    temp_s0_2 = (temp_s0 > 0x19000) ? 0x19000 : temp_s0;
    func_002DA3A8(sp[0], arg1, temp_s0_2);
    func_002BDC58(temp_s3, temp_s0_2, sp);
    *(s32 *)(temp_s1 + 0x48) = *(s32 *)(temp_s1 + 0x48) + temp_s0_2;
    *arg3 = temp_s0_2;
}
