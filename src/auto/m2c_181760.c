#include "m2c_macros.h"

s32 BtlTaskList_AddTail(s32, M2C_UNK *, M2C_UNK);   /* extern */
extern M2C_UNK D_00341E70 __attribute__((section(".data")));
extern s32 *D_0038779C;

void func_00181760(s32 *arg0, M2C_UNK arg1) {
    if (*arg0 == 0) {
        *arg0 = BtlTaskList_AddTail(*D_0038779C, &D_00341E70, arg1);
    }
}
