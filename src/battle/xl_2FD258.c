#include "m2c_macros.h"

void BtlSeq_Term(void);
void PauseMenu_Term(void);
M2C_UNK func_002FCE78(s8 *);                        /* extern */
extern s8 D_003553F0 __attribute__((section(".data")));

void func_002FD258(void) {
    s32 var_s1;
    s8 *var_s0;

    var_s1 = 0xF;
    PauseMenu_Term();
    var_s0 = &D_003553F0;
    do {
        if (*var_s0 == 1) {
            func_002FCE78(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0x44;
    } while (var_s1 >= 0);
    BtlSeq_Term();
}
