#include "common.h"

s32 func_0010B080(s32 arg0);
s32 func_0010B0A0(s32 arg0);
void func_0010C958(void);
void func_0010C9E0(void);
void func_00113430(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_00114130(s32 arg0, s32 arg1);
void HudTeam_GsBeginMask(void);
void HudTeam_GsEndMask(void);

void func_00110570(s32 arg0) {
    s32 temp_s2;
    s32 temp_v0;
    s32 temp_s1;

    temp_s2 = func_0010B080(arg0);
    temp_v0 = func_0010B0A0(arg0);
    temp_s1 = temp_v0 + 0x3180;
    if (*(s32 *)temp_s1 & 1) {
        func_00113430(*(s32 *)(temp_s2 + 8), temp_s1, 1, 0x2A00, 0x2C80, 0, 0);
        func_00114130(temp_v0 + 0x32A0, 1);
        HudTeam_GsBeginMask();
        func_00113430(*(s32 *)(temp_s2 + 8), temp_v0 + 0x3240, 1, 0x2A00, 0x2C80, 0, 0);
        HudTeam_GsEndMask();
    }
    if (*(s32 *)(temp_s1 + 0x1E0) & 1) {
        func_00113430(*(s32 *)(temp_s2 + 8), temp_v0 + 0x3360, 1, 0x2A00, 0x2C80, 0, 0);
        func_00114130(temp_v0 + 0x3480, 1);
        HudTeam_GsBeginMask();
        func_00113430(*(s32 *)(temp_s2 + 8), temp_v0 + 0x3420, 1, 0x2A00, 0x2C80, 0, 0);
        HudTeam_GsEndMask();
    }
    if (!(*(s32 *)(temp_s1 + 0x3C0) & 1)) {
        return;
    }
    func_0010C958();
    func_00113430(*(s32 *)(temp_s2 + 8), temp_v0 + 0x3540, 1, 0x2A00, 0x2C80, 0, 0);
    func_0010C9E0();
}
