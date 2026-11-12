#include "common.h"

s32 BattleSide_SetChara(s32 arg0, s32 arg1);
f32 BtlMember_GetHealthRatio(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212878(void);
s32 func_00218838(s32 arg0, s32 arg1);

void func_002231F8(u8 *arg0) {
    s32 sel;
    f32 ratio;
    f32 x;
    s32 t;
    f32 d;

    sel = (func_00218838((s32)arg0, 1) == 0) ? 0xD5 : 0xD6;
    BattleSide_SetChara((s32)arg0, sel);
    func_002113C0((s32)arg0, 0, 2, 1);
    *(s32 *)(arg0 + 0x8C0) = 0x20;
    if (func_00212878() != 0) {
        ratio = BtlMember_GetHealthRatio((s32)arg0);
        x = (1.0f - ratio) * 32.0f;
        t = (s32)x;
        d = x - (f32)t;
        if (d > 0.5f || (d == 0.5f && (t & 1))) {
            t += 1;
        } else if (d < -0.5f || (d == -0.5f && (t & 1))) {
            t -= 1;
        }
        *(s32 *)(arg0 + 0x8C0) = t;
    }
}
