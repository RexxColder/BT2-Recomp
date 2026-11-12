#include "common.h"

s32 BtlTask_CreateChildList(void *arg0, s32 arg1, s32 arg2);
void EftShot_SetCharPool(s32 arg0, void *arg1);
s32 func_00148440(s32 arg0, s32 arg1, s32 arg2);
void func_00148568(s32 arg0, s32 arg1);
s32 func_00148A08(s32 arg0, s32 arg1);
extern u8 *D_00387760;

void func_00148268(u8 *arg0, s32 *arg1) {
    s32 var_s3;
    s32 idx;
    s32 r;
    u8 *s0;

    if (D_00387760 == NULL) {
        return;
    }
    var_s3 = 0;
    arg0[1] = *(u8 *)arg1;
    s0 = *(u8 **)(D_00387760 + 4) + *arg1 * 0x270;
    EftShot_SetCharPool(*arg1, D_00387760);
    *(s32 *)(s0 + 0x258) = BtlTask_CreateChildList(arg0, 6, 0x2000);
    do {
        idx = var_s3;
        r = func_00148A08(*arg1, idx);
        r = func_00148440(*arg1, idx, r);
        var_s3 += 1;
        if (r != 0) {
            func_00148568(*arg1, idx);
        }
    } while (var_s3 < 5);
}
