#include "m2c_macros.h"

s32 BtlScene_IsTimeStopped();                       /* extern */
M2C_UNK func_001D7A10(void *);                      /* extern */
extern void *D_00387E9C;

void func_001D7988(void) {
    u32 var_s1;
    void *var_s0;

    if (M2C_FIELD(D_00387E9C, s32 *, 0x1444) != 0) {
        if (BtlScene_IsTimeStopped() == 0) {
            var_s1 = 0;
            var_s0 = M2C_FIELD(D_00387E9C, void **, 0x1420);
            if (M2C_FIELD(D_00387E9C, s32 *, 0x16BC) != 0) {
                do {
                    if (M2C_FIELD(var_s0, u8 *, 0x63) != 0) {
                        func_001D7A10(var_s0);
                    }
                    var_s1 += 1;
                    var_s0 += 0x70;
                } while (var_s1 < (u32) M2C_FIELD(D_00387E9C, u32 *, 0x16BC));
            }
        }
    }
}
