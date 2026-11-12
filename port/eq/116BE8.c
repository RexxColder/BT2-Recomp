#include "common.h"

void HudTeam_GsBeginMask(void);
void HudTeam_GsEndMask(void);
u8 *func_0010B080(void);
s32 func_0010B0A0(s32 arg0);
void func_0010C770(void);
void func_0010C868(void);
void func_00113430(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0, s32 t1, s32 t2);
void func_00114130(s32 arg0, s32 arg1);

void func_00116BE8(s32 arg0) {
    s32 temp_s0;
    s32 temp_s1;
    u8 *temp_s2;

    temp_s2 = func_0010B080();
    temp_s1 = func_0010B0A0(arg0);
    func_0010C770();
    temp_s0 = temp_s1 + 0x3960;
    func_00113430(*(s32 *)(temp_s2 + 0x10), temp_s1 + 0x3720, 1, 0x2A00, 0x2C00, 0, 0);
    func_0010C868();
    func_00113430(*(s32 *)(temp_s2 + 0x10), temp_s0, 1, 0x2A00, 0x2C00, 0, 0);
    func_00114130(temp_s0, 1);
    HudTeam_GsBeginMask();
    func_00113430(*(s32 *)(temp_s2 + 0x10), temp_s1 + 0x3A80, 1, 0x2A00, 0x2C00, 0, 0);
    HudTeam_GsEndMask();
    func_0010C770();
    func_00113430(*(s32 *)(temp_s2 + 0x10), temp_s1 + 0x37E0, 1, 0x2A00, 0x2C00, 0, 0);
    func_0010C868();
}
