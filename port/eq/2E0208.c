#include "common.h"

void func_002DA708(s32 arg0, s32 arg1, s32 arg2);
void func_002E0590(s32 arg0, s32 arg1);
void func_002E1A60(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0037B030[] __attribute__((section(".data")));
extern u8 D_00399DA8[] __attribute__((section(".data")));

void func_002E0208(s32 arg0, s32 arg1) {
    s32 temp_s1;
    s32 temp_s3;
    s32 temp_s4;

    temp_s3 = (arg1 + 0x3F) & ~0x3F;
    temp_s1 = temp_s3 + arg0 * 0x440;
    temp_s4 = temp_s1 + 0x420;
    func_002DA708(temp_s3, 0, arg0 * 0x118 + 0x800);
    func_002E0590(temp_s4, 0x1BE0);
    func_002E1A60((s32)D_00399DA8, (s32)D_0037B030, 0x10);
    *(s32 *)(D_00399DA8 + 0x4C) = temp_s1;
    *(s32 *)(D_00399DA8 + 0x58) = temp_s3;
    *(s32 *)(D_00399DA8 + 0x50) = temp_s4;
    *(s32 *)(D_00399DA8 + 0x54) = arg0;
}
