#include "common.h"

void HudTeam_GsBeginMask(void);
void HudTeam_GsEndMask(void);
u8 *func_0010B080(s32 arg0);
s32 func_0010B0A0(s32 arg0);
void func_00113430(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_00114130(s32 arg0, s32 arg1);

void func_0010D3A0(s32 arg0) {
    u8 *s2;
    s32 base;
    s32 s1;

    s2 = func_0010B080(arg0);
    base = func_0010B0A0(arg0);
    s1 = base + 0xA20;
    func_00113430(*(s32 *)(s2 + 8), s1, 1, 0x2A00, 0x2C80, 0, 0);
    if (*(s32 *)(s1 + 0xC0) & 1) {
        func_00114130(base + 0xB40, 1);
        HudTeam_GsBeginMask();
        func_00113430(*(s32 *)(s2 + 8), base + 0xAE0, 1, 0x2A00, 0x2C80, 0, 0);
        HudTeam_GsEndMask();
    }
    if (*(s32 *)(s1 + 0x1E0) & 1) {
        func_00114130(base + 0xC60, 1);
        HudTeam_GsBeginMask();
        func_00113430(*(s32 *)(s2 + 8), base + 0xC00, 1, 0x2A00, 0x2C80, 0, 0);
        HudTeam_GsEndMask();
    }
    if (*(s32 *)(s1 + 0x300) & 1) {
        func_00114130(base + 0xD80, 1);
        HudTeam_GsBeginMask();
        func_00113430(*(s32 *)(s2 + 8), base + 0xD20, 1, 0x2A00, 0x2C80, 0, 0);
        HudTeam_GsEndMask();
    }
    if (*(s32 *)(s1 + 0x420) & 1) {
        func_00114130(base + 0xEA0, 1);
        HudTeam_GsBeginMask();
        func_00113430(*(s32 *)(s2 + 8), base + 0xE40, 1, 0x2A00, 0x2C80, 0, 0);
        HudTeam_GsEndMask();
    }
    func_00113430(*(s32 *)(s2 + 8), base + 0xF60, 1, 0x2A00, 0x2C80, 0, 0);
}
