#include "common.h"

void BtlObjAnim_RebaseRoot(s32 arg0);
void func_0025F130(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00260038(s32 arg0);

void func_00260068(u8 *arg0) {
    s32 *var_s2;
    s32 temp_s0;
    s32 var_s1;

    var_s1 = 0;
    var_s2 = (s32 *)(arg0 + 0x60);
    do {
        temp_s0 = *var_s2;
        var_s2 += 1;
        if (temp_s0 != 0) {
            if ((func_00260038(var_s1) & 1) != 0) {
                func_0025F130(temp_s0, 1, 1, 1);
            }
            if ((func_00260038(var_s1) & 2) != 0) {
                BtlObjAnim_RebaseRoot(temp_s0);
            }
        }
        var_s1 += 1;
    } while (var_s1 < 0x32);
}
