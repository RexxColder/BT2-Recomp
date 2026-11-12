#include "common.h"

s32 func_0010B080(s32 arg0);
s32 func_0010B0A0(s32 arg0);
void func_0010C958(void);
void func_0010C9E0(void);
void func_00113430(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_00114130(s32 arg0, s32 arg1);
void HudTeam_GsBeginMask(void);
void HudTeam_GsEndMask(void);

void func_0010DD40(s32 arg0) {
    s32 temp_s1;
    s32 temp_s3;
    s32 var_s0;
    s32 var_s2;

    var_s2 = 4;
    temp_s1 = func_0010B080(arg0);
    temp_s3 = func_0010B0A0(arg0) + 0x1AA0;
    var_s0 = temp_s3;
    do {
        var_s2 -= 1;
        func_00113430(*(s32 *)(temp_s1 + 8), var_s0, 1, 0x2A00, 0x2C80, 0, 0);
        func_00114130(var_s0, 1);
        HudTeam_GsBeginMask();
        func_00113430(*(s32 *)(temp_s1 + 8), var_s0 + 0xC0, 1, 0x2A00, 0x2C80, 0, 0);
        HudTeam_GsEndMask();
        func_00114130(var_s0, 1);
        HudTeam_GsBeginMask();
        func_00113430(*(s32 *)(temp_s1 + 8), var_s0 + 0x1E0, 1, 0x2A00, 0x2C80, 0, 0);
        HudTeam_GsEndMask();
        func_00114130(var_s0, 1);
        HudTeam_GsBeginMask();
        func_00113430(*(s32 *)(temp_s1 + 8), var_s0 + 0x300, 1, 0x2A00, 0x2C80, 0, 0);
        var_s0 += 0x420;
        HudTeam_GsEndMask();
    } while (var_s2 >= 0);
    func_0010C958();
    func_00113430(*(s32 *)(temp_s1 + 8), temp_s3 + 0x14A0, 1, 0x2A00, 0x2C80, 0, 0);
    func_0010C9E0();
}
