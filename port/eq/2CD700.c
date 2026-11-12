#include "common.h"

s32 func_002C0EE0(s32 arg0, s32 arg1);
s32 func_002CD960(s32 arg0);
s32 func_002CDA00(s32 arg0);
s32 func_002D07B0(s32 arg0, s32 arg1);
void func_002D1510(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D1908(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002D3078(s32 arg0, s32 arg1);
s32 func_002E0A98(s32 arg0, s32 arg1, s32 arg2);

s32 func_002CD700(s32 arg0) {
    s32 sp[2];
    u8 *p = (u8 *)arg0;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 var_v0;
    u8 *temp_v1;

    var_v0 = func_002D07B0(arg0, 0x43);
    if (var_v0 != 0) {
        var_v0 = func_002D07B0(arg0, 0xF);
        if (var_v0 != 0) {
            var_v0 = 0;
            if ((*(s32 *)(p + 0x50) == 0) && (*(s32 *)(p + 0x48) == 4)) {
                if (func_002CD960(arg0) != 0) {
                    return 0;
                }
                if (func_002D07B0(arg0, 5) == 1) {
                    var_v0 = 0;
                    if (*(s32 *)(p + 0x950 + 0x28) != 0) {
                        goto block_10;
                    }
                    return var_v0;
                }
block_10:
                if (func_002D07B0(arg0, 6) == 1) {
                    var_v0 = 0;
                    if (func_002C0EE0(arg0, 2) <= 0) {
                        goto block_13;
                    }
                    return var_v0;
                }
block_13:
                if (((func_002D3078(arg0, 1) == 0) || (var_v0 = 0, (func_002C0EE0(arg0, 0) <= 0))) &&
                    ((func_002D07B0(arg0, 5) != 1) || (var_v0 = 0, (func_002CDA00(arg0) == 0)))) {
                    func_002D1510(arg0, (s32)sp, (s32)&sp[1]);
                    temp_v1 = p + 0xD30;
                    temp_s1 = *(s32 *)(temp_v1 + 0x288);
                    temp_s0 = *(s32 *)(temp_v1 + 0x284);
                    temp_s0_2 = temp_s0 - func_002E0A98(func_002D07B0(arg0, 0x44), temp_s1, 0xF4240);
                    if ((sp[0] <= 0) || (temp_s0_2 <= 0)) {
                        return 0;
                    }
                    var_v0 = func_002D1908(sp[0], sp[1], temp_s0_2, temp_s1) == 0;
                    return var_v0;
                }
                return var_v0;
            }
        }
    }
    return var_v0;
}
