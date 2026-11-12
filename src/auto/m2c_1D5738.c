#include "m2c_macros.h"

s32 BtlScene_IsTimeStopped();                       /* extern */
M2C_UNK func_001D57B0(void *);                      /* extern */
extern void *D_00387E9C;

void func_001D5738(void) {
    s32 var_s1;
    void *var_s0;

    if (M2C_FIELD(D_00387E9C, s32 *, 0x1430) != 0) {
        if (BtlScene_IsTimeStopped() == 0) {
            var_s1 = 0x11;
            var_s0 = M2C_FIELD(D_00387E9C, void **, 0x140C);
            do {
                if (M2C_FIELD(var_s0, u8 *, 0x5B) != 0) {
                    func_001D57B0(var_s0);
                }
                var_s1 -= 1;
                var_s0 += 0x60;
            } while (var_s1 >= 0);
        }
    }
}
