#include "common.h"

s32 BtlAnim_SetBlend(f32 farg0, s32 arg0, s32 arg1);
u8 *BtlMember_GetActiveGauge(void *arg0);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
s32 func_00212820(void *arg0);
s32 func_00212878(void);
s32 func_00217488(void *arg0);
s32 func_0023C780(void *arg0);
s32 func_0023D1E0(void *arg0, s32 arg1);

extern f32 D_00386044;
extern f32 D_00386048;

s32 func_00222850(void *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_v0;

    if ((func_00217488(arg0) == 0xA5) && (func_00212820(arg0) != 0)) {
        if (*(u8 *)(BtlMember_GetActiveGauge(arg0) + 0x29) == 0) {
            var_v0 = func_0023D1E0(arg0, 0);
            if (var_v0 == -1) {
                goto block_4;
            }
            return var_v0;
        }
        goto block_5;
    }
block_4:
block_5:
    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(D_00386044, (s32)arg0, 0);
    if ((func_00212878() == 0) || (func_00212820(arg0) == 0) || (var_v0 = 0x26, (func_00211310(arg0, 0, 0x40) == 0))) {
        temp_v0_2 = func_00217488(arg0);
        if (temp_v0_2 < 0xA5) {
            return func_0023C780(arg0);
        }
        if (temp_v0_2 >= 0xA7) {
            if (temp_v0_2 < 0xA9) {
                temp_v0 = func_0023D1E0(arg0, 1);
                if (temp_v0 == -1) {
                    if (func_00211310(arg0, 0, 0x100) != 0) {
                        return func_0023C780(arg0);
                    }
                    return 0xA6;
                }
                BtlAnim_SetBlend(D_00386048, (s32)arg0, 0);
                return temp_v0;
            }
            return func_0023C780(arg0);
        }
        return func_0023C780(arg0);
    }
    return var_v0;
}
