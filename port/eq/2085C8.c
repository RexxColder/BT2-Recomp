#include "common.h"

s32 func_0020A758(s32 arg0);
u8 *func_00211288(s32 arg0);
s32 func_00212320(u8 *arg0);
s32 func_00241BE0(u8 *arg0, s32 arg1);
s32 func_00241C18(u8 *arg0, s32 arg1);
extern s32 D_00387930;

s32 func_002085C8(u32 arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 r1;
    s32 var_v0;
    u8 *temp_s1;

    if ((D_00387930 != 0) && (arg0 < 2U)) {
        temp_s1 = func_00211288(arg0);
        var_v0 = func_0020A758(arg0);
        if (var_v0 != 0) {
            temp_v0_2 = func_00212320(temp_s1);
            r1 = func_00241BE0(temp_s1, temp_v0_2);
            temp_v0 = func_00241C18(temp_s1, temp_v0_2);
            if (*(s32 *)(*(u8 **)(temp_s1 + 0x1530) + 4) != r1) {
                return r1;
            }
            return temp_v0;
        }
        return var_v0;
    }
    return 0;
}
