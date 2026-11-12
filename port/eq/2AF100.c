#include "common.h"

void BtlMenu_EndDraw(s32 arg0, f32 farg0);
s32 func_002B0DB0(s32 arg0, s32 arg1);
extern f32 D_00387438;
extern f32 D_0038743C;
extern f32 D_00387440;

s32 func_002AF100(u8 *arg0) {
    s32 var_v0;

    if (func_002B0DB0((s32)arg0, 0x05000000) == 0) {
        BtlMenu_EndDraw((s32)arg0, D_00387438);
        return 9;
    }
    var_v0 = -1;
    if (D_0038743C < *(f32 *)(arg0 + 0xAC)) {
        BtlMenu_EndDraw((s32)arg0, D_00387440);
        var_v0 = 0xB;
    }
    return var_v0;
}
