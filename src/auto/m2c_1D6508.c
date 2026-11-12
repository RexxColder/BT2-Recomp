#include "m2c_macros.h"

s32 BtlScene_IsTimeStopped();                       /* extern */
M2C_UNK func_001D6580(void *);                      /* extern */
extern void *D_00387E9C;

void func_001D6508(void) {
    s32 var_s1;
    void *var_s0;

    if (M2C_FIELD(D_00387E9C, s32 *, 0x1438) != 0) {
        if (BtlScene_IsTimeStopped() == 0) {
            var_s1 = 0x1D;
            var_s0 = M2C_FIELD(D_00387E9C, void **, 0x1414);
            do {
                if (M2C_FIELD(var_s0, u8 *, 0x6F) != 0) {
                    func_001D6580(var_s0);
                }
                var_s1 -= 1;
                var_s0 += 0x80;
            } while (var_s1 >= 0);
        }
    }
}
