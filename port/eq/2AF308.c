#include "common.h"

void BtlMenu_EndDraw(s32 arg0, f32 farg0);
extern f32 D_0038745C;
extern f32 D_00387460;
extern f32 D_00387464;

s32 func_002AF308(u8 *arg0) {
    if (*(u8 *)(arg0 + 0x188) == 0) {
        if (*(f32 *)(arg0 + 0xAC) < D_00387460) {
            BtlMenu_EndDraw((s32)arg0, D_00387464);
            return 0xA;
        }
        return -1;
    }
    BtlMenu_EndDraw((s32)arg0, D_0038745C);
    return 9;
}
