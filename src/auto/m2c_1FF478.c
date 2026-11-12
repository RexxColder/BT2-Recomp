#include "m2c_macros.h"

s32 BattleResult_GetFlags(void *);                  /* extern */
void *BtlChar_GetPos(void *);                       /* extern */
s32 BtlObjXf_Update(void *);                        /* extern */
f32 BtlUtil_WrapAngle(f32);                         /* extern */
s32 func_001FA3A8(s32);                             /* extern */
M2C_UNK func_001FCF88(void *, s32);                 /* extern */
M2C_UNK func_0020FC38(void *, M2C_UNK);             /* extern */
void *func_00211288(M2C_UNK);                       /* extern */
M2C_UNK func_002113C0(void *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_00211418(void *, M2C_UNK);             /* extern */
s32 func_00212820(void *);                          /* extern */
M2C_UNK func_00212DD8(void *, M2C_UNK);             /* extern */
s32 func_0023E520(void *);                          /* extern */
s32 func_0023F410(void *);                          /* extern */
s32 func_0023F440(void *);                          /* extern */
extern f32 D_00385878;

s32 func_001FF478(void *arg0, M2C_UNK arg1) {
    s32 temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = func_00211288(arg1);
    if (func_0023E520(arg0) == 0x4A) {
        if ((func_0023F440(temp_s1) == 4) || ((func_0023F410(temp_s1) & 0x4000) && (BattleResult_GetFlags(arg0) & 0x4000))) {
            func_002113C0(arg0, 4, 0x08000000, 1);
            func_0020FC38(temp_s1, 0x44);
            func_00212DD8(arg0, 0);
            func_001FCF88(temp_s1, func_0023E520(arg0));
            return 0;
        }
        if (func_00212820(temp_s1) != 0) {
            temp_v0 = func_001FA3A8(BtlObjXf_Update(temp_s1));
            if ((temp_v0 & 0x31) && !(temp_v0 & 0x100000)) {
                temp_s0 = BtlChar_GetPos(arg0);
                if (D_00385878 < fabsf(BtlUtil_WrapAngle(M2C_FIELD(temp_s0, f32 *, 0xB4) - M2C_FIELD(BtlChar_GetPos(temp_s1), f32 *, 0xB4)))) {
                    if (M2C_FIELD(temp_s1, s32 *, 0x1174) > 0) {
                        func_002113C0(arg0, 4, 0x08000000, 1);
                        func_002113C0(temp_s1, 4, 0x10000000, 1);
                        func_0020FC38(temp_s1, 0x44);
                        func_00212DD8(arg0, 0);
                        func_00212DD8(temp_s1, 0x11);
                        func_001FCF88(temp_s1, func_0023E520(arg0));
                        func_00211418(temp_s1, 0x04000000);
                        return 0;
                    }
                    goto block_12;
                }
                /* Duplicate return node #13. Try simplifying control flow for better match */
                return 1;
            }
        }
        goto block_12;
    }
block_12:
    return 1;
}
