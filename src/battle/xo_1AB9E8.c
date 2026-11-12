#include "m2c_macros.h"

M2C_UNK EftRibbon_SetEnd(s32, void *, M2C_UNK);     /* extern */
M2C_UNK EftRibbon_Stop(s32);                        /* extern */
M2C_UNK EftRibbon_StopAndKill(s32);                 /* extern */
M2C_UNK func_00129C38(void *, void *);              /* extern */
f32 func_001AA4B0(s32);                      /* extern */
M2C_UNK func_001AA848(void *, void *);                      /* extern */

/* Ribbon/trail update: stops or kills the attached EftRibbon and resets flags according to arg0 state bits. */
void func_001AB9E8(void *arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_v0;
    s32 temp_v1;
    void *temp_s0;

    temp_v1 = M2C_FIELD(arg0, s32 *, 4);
    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    if (temp_v1 & 0x3F) {
        M2C_FIELD(temp_s0, s32 *, 0xC) = 0;
        temp_v0 = M2C_FIELD(temp_s0, s32 *, 0) | 0x10;
        M2C_FIELD(temp_s0, s32 *, 0) = temp_v0;
        if (!(temp_v0 & 0x100)) {
            func_00129C38(temp_s0 + 0x90, arg0 + 0x10);
            temp_v0 = M2C_FIELD(temp_s0, s32 *, 0);
            temp_v0 |= 0x100;
            M2C_FIELD(temp_s0, s32 *, 0) = temp_v0;
        }
        temp_a0 = M2C_FIELD(temp_s0, s32 *, 0xD4);
        if (temp_a0 != 0) {
            EftRibbon_SetEnd(temp_a0, temp_s0 + 0x90, 1);
            EftRibbon_Stop(M2C_FIELD(temp_s0, s32 *, 0xD4));
            M2C_FIELD(temp_s0, s32 *, 0xD4) = 0;
        }
    } else if ((temp_v1 & 0xC0) && !(M2C_FIELD(temp_s0, s32 *, 0) & 8)) {
        func_001AA848(arg0, temp_s0);
        M2C_FIELD(temp_s0, f32 *, 0x90) = (f32) M2C_FIELD(arg0, f32 *, 0x10);
        M2C_FIELD(temp_s0, f32 *, 0x94) = (f32) M2C_FIELD(arg0, f32 *, 0x14);
        M2C_FIELD(temp_s0, f32 *, 0x98) = (f32) M2C_FIELD(arg0, f32 *, 0x18);
        if (!(M2C_FIELD(temp_s0, s32 *, 0) & 0x80)) {
            temp_a0_2 = M2C_FIELD(temp_s0, s32 *, 0xD4);
            if (temp_a0_2 != 0) {
                EftRibbon_StopAndKill(temp_a0_2);
                M2C_FIELD(temp_s0, s32 *, 0xD4) = 0;
            }
            func_001AA4B0(arg0);
        }
        M2C_FIELD(temp_s0, s32 *, 0) = (s32) (M2C_FIELD(temp_s0, s32 *, 0) | 0x200);
        M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) & ~0xC0);
    }
}
