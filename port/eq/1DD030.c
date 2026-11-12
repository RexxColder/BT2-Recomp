#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, void *arg1, s32 *arg2, u8 *arg3);
void func_001DCF40(u8 *arg0, u8 *arg1, s32 arg2);
s32 func_001DCFD8(s32 arg0, s32 arg1);
s32 func_00207EC0(s32 arg0);
extern u8 D_003431A8[] __attribute__((section(".data")));
extern u8 *D_003878D0;

void func_001DD030(s32 arg0) {
    s32 sp[4];
    u8 *temp_s1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 sp1;

    temp_s1 = D_003878D0;
    sp[0] = 0;
    sp[1] = 0;
    sp[2] = arg0;
    if (temp_s1 != NULL) {
        temp_v0 = func_00207EC0(arg0);
        if (temp_v0 >= 0x3D) {
            if (temp_v0 >= 0x41) {
                if ((temp_v0 < 0x58) && (temp_v0 >= 0x56)) {
                    sp1 = func_00207EC0(arg0) - 0x52;
                    goto block_8;
                }
            } else {
                sp1 = func_00207EC0(arg0) - 0x3D;
block_8:
                sp[1] = sp1;
                sp[0] = *(s32 *)temp_s1 + sp[1] * 400;
                temp_v0_2 = func_001DCFD8(BtlTaskList_AddTail(*(s32 *)(temp_s1 + 0x164), D_003431A8, sp, temp_s1), arg0);
                if (temp_v0_2 != 0) {
                    func_001DCF40(temp_s1 + 0x120, temp_s1 + 0x124, temp_v0_2);
                }
            }
        }
    }
}
