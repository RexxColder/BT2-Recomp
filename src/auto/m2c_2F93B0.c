#include "m2c_macros.h"

M2C_UNK memset(s8 *, M2C_UNK, M2C_UNK);             /* extern */
extern s32 D_00355334 __attribute__((section(".data")));
extern s8 D_0039D7F8 __attribute__((section(".data")));
extern s8 D_0039D938 __attribute__((section(".data")));
extern s8 D_0039DB38 __attribute__((section(".data")));

void func_002F93B0(void) {
    s32 temp_v0;
    s32 var_s1;
    s8 *var_s0;
    void *temp_v0_2;

    temp_v0 = D_00355334 - 1;
    D_00355334 = temp_v0;
    if (temp_v0 == 0) {
        var_s1 = 0x27;
        var_s0 = &D_0039D7F8;
        do {
            temp_v0_2 = M2C_FIELD(var_s0, void **, 0);
            if (temp_v0_2 != NULL) {
                M2C_FIELD(temp_v0_2, M2C_UNK (**)(s32), 0x14)(M2C_FIELD(var_s0, s32 *, 4));
            }
            var_s1 -= 1;
            var_s0 += 8;
        } while (var_s1 >= 0);
        memset(&D_0039D7F8, 0, 0x140);
        memset(&D_0039D938, 0, 0x200);
        memset(&D_0039DB38, 0, 9);
        D_0039DB38 = 0;
    }
}
