#include "common.h"

void BtlMenu_EndDraw(s32 arg0, f32 farg0);
extern f32 D_003873AC;
extern u8 *D_00387E18;

s32 func_002AE848(u8 *arg0) {
    if ((*(u8 *)(arg0 + 0x188) != 0) || (*(u8 *)(D_00387E18 + 0xA) != 0)) {
        BtlMenu_EndDraw((s32)arg0, D_003873AC);
        return 1;
    }
    return -1;
}
