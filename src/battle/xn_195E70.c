#include "m2c_macros.h"

s32 BtlScene_IsCharStopped(s32);                    /* extern */
void BtlTask_SetDead(void *);                    /* extern */
void func_00151FB0(void *);                      /* extern */
s32 func_00152200(s32, void *);                     /* extern */
void func_00195A90(s32, void *, s32);            /* extern */
void func_00196048(void *);                      /* extern */
void func_001961B8(void *);                      /* extern */
void func_001962A0(s32, void *, void *);         /* extern */
void func_001968B0(void *);                      /* extern */
void func_00196B28(void *);                      /* extern */

void func_00195E70(void *arg0) {
    s32 *temp_s0;
    s32 temp_s0_2;
    s32 temp_v0;
    s32 var_v1;
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    temp_s0 = M2C_FIELD(temp_s1, s32 **, 0xAF0);
    if (BtlScene_IsCharStopped(*temp_s0) == 0) {
        func_00196048(temp_s1);
        func_001962A0(*temp_s0, temp_s1 + 0x7B0, temp_s1);
        func_00151FB0(temp_s1);
        func_00195A90(*temp_s0, arg0, M2C_FIELD(temp_s1, s32 *, 0xA00));
        temp_s0_2 = func_00152200(M2C_FIELD(temp_s1, s32 *, 0xA00), temp_s1) != 0;
        func_001968B0(arg0);
        var_v1 = M2C_FIELD(temp_s1, s32 *, 0xB70);
        if ((temp_s0_2 == 0) && (var_v1 & 8)) {
            func_00196B28(temp_s1);
            temp_v0 = M2C_FIELD(temp_s1, s32 *, 0xB70) | 0x10;
            M2C_FIELD(temp_s1, s32 *, 0xB70) = temp_v0;
            var_v1 = temp_v0;
        }
        if (var_v1 & 0x20) {
            BtlTask_SetDead(arg0);
            return;
        }
        if (!(var_v1 & 0x200)) {
            func_001961B8(arg0);
        }
    }
}
