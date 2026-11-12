#include "common.h"

s32 func_0010B080(s32 arg0);
s32 func_0010B0A0(s32 arg0);
void func_0010C958(void);
void func_0010C9E0(void);
void func_00113430(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_00114130(s32 arg0, s32 arg1);
void HudTeam_GsBeginMask(void);
void HudTeam_GsEndMask(void);

void func_0010EA90(s32 arg0) {
    s32 temp_s2;
    s32 temp_v0;
    s32 temp_s0;

    temp_s2 = func_0010B080(arg0);
    temp_v0 = func_0010B0A0(arg0);
    temp_s0 = temp_v0 + 0x1500;
    if (*(s32 *)(temp_s0 + 0x240) & 1) {
        func_0010C958();
        func_00113430(*(s32 *)(temp_s2 + 8), temp_v0 + 0x1740, 1, 0x2A00, 0x2C80, 0, 0);
        func_0010C9E0();
    }
    func_00113430(*(s32 *)(temp_s2 + 8), temp_s0, 1, 0x2A00, 0x2C80, 0, 0);
    if (*(s32 *)(temp_s0 + 0x300) & 1) {
        func_0010C958();
        func_00113430(*(s32 *)(temp_s2 + 8), temp_v0 + 0x1800, 1, 0x2A00, 0x2C80, 0, 0);
        func_0010C9E0();
    }
    if (*(s32 *)(temp_s0 + 0x3C0) & 1) {
        func_00113430(*(s32 *)(temp_s2 + 8), temp_v0 + 0x18C0, 1, 0x2A00, 0x2C80, 0, 0);
        func_00114130(temp_v0 + 0x19E0, 1);
        HudTeam_GsBeginMask();
        func_00113430(*(s32 *)(temp_s2 + 8), temp_v0 + 0x1980, 1, 0x2A00, 0x2C80, 0, 0);
        HudTeam_GsEndMask();
    }
}
