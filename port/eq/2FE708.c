#include "common.h"

s32 func_00326950(s32 arg0, s32 *arg1, s32 arg2);
void func_002EFA40(s32 arg0, s32 arg1);
extern u8 D_0037E540[];
extern u8 D_0037E558[];
extern u8 D_0037E568[];

s32 func_002FE708(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 cur;

    cur = arg0;
    *arg1 = func_00326950(arg0, &cur, 16);
    if (*(s8 *)cur != 0) {
        cur = cur + 1;
    }
    if (arg2 != NULL) {
        *arg2 = func_00326950(cur, &cur, 16);
    }
    func_002EFA40((s32)D_0037E540, arg0);
    func_002EFA40((s32)D_0037E558, *arg1);
    func_002EFA40((s32)D_0037E568, *arg2);
    return 1;
}
