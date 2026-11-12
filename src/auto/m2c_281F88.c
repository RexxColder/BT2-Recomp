#include "m2c_macros.h"

s32 Ramp_Step(void *);                              /* extern */
M2C_UNK func_0029BAB0(void *);                      /* extern */
extern void *D_003876A0;
extern s32 D_00387B00;

void func_00281F88(void) {
    s32 var_s2;
    s32 var_s3;
    u8 temp_v0;
    void *temp_s0;
    void *temp_s1;

    var_s2 = 0;
    var_s3 = 0;
    do {
        if ((var_s2 == 3) || !(M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 0x100)) {
            temp_s0 = D_00387B00 + var_s3;
            temp_s1 = temp_s0 + 0x40;
            if ((M2C_FIELD(temp_s0, u8 *, 0x58) & 1 & 0xFF) && (Ramp_Step(temp_s1) == 1)) {
                temp_v0 = M2C_FIELD(temp_s0, u8 *, 0x58);
                if (temp_v0 & 4) {
                    M2C_FIELD(temp_s0, u8 *, 0x58) = (u8) (temp_v0 | 8);
                    func_0029BAB0(temp_s1);
                }
            }
        }
        var_s2 += 1;
        var_s3 += 0x60;
    } while (var_s2 < 4);
}
