#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 *arg2, s32 arg3);
void func_001AA1C0(void);
extern s32 D_00387840;
extern s32 D_00387844;
extern u8 D_003426F8[] __attribute__((section(".data")));

s32 func_001AA260(s32 arg0) {
    s32 sp[4];
    s32 ret = 0;

    if (D_00387840 != 0) {
        sp[0] = arg0;
        ret = BtlTaskList_AddTail(D_00387844, (s32)D_003426F8, sp, arg0);
        if (ret != 0) {
            func_001AA1C0();
            ret = 1;
        }
    }
    return ret;
}
