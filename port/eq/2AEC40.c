#include "common.h"

void BtlMenu_EndDraw(s32 arg0, f32 farg0);

extern f32 D_003873EC;

s32 func_002AEC40(u8 *arg0) {
    if (*(u8 *)(arg0 + 0x188) == 0) {
        return -1;
    }
    BtlMenu_EndDraw((s32)arg0, D_003873EC);
    return 1;
}
