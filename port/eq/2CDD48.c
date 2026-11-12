#include "common.h"

s32 func_002D07B0(u8 *arg0, s32 arg1);
s32 func_002D13D0(u8 *arg0, s32 *arg1, s32 *arg2);
s32 func_002D1908(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002D05E8(u8 *arg0, s32 arg1, s32 arg2);
extern s32 D_00346DE0 __attribute__((section(".data")));

s32 func_002CDD48(u8 *arg0) {
    s32 sp[2];
    s32 var_s0;
    s32 var_v0;

    if (*(s32 *)(arg0 + 0x48) == 4) {
        var_v0 = 0;
        if (*(s32 *)(arg0 + 0x50) != 1) {
            if (*(s32 *)(arg0 + 0x950 + 0x20) == 1) {
                return 0;
            }
            var_v0 = func_002D13D0(arg0, sp, sp + 1);
            if (var_v0 != 0) {
                return 0;
            }
            if (sp[0] >= 0) {
                var_s0 = func_002D07B0(arg0, 0x36);
                if (var_s0 == -1) {
                    var_s0 = ((0x7FFFFFFF / D_00346DE0) * 0x3E8) - 0x3E8;
                    func_002D05E8(arg0, 0x36, var_s0);
                }
                var_v0 = func_002D1908(var_s0, 0x3E8, sp[0], sp[1]) != 0;
            }
            return var_v0;
        }
        return var_v0;
    }
    return 0;
}
