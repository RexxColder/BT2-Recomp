#include "m2c_macros.h"

M2C_UNK func_0029BAB0(void *);                      /* extern */
extern u8 D_00388F30 __attribute__((section(".data")));

// Loop over three 0x60-byte entries of D_00388F30: clears the byte at +0x58 and calls func_0029BAB0 on +0x40.
void func_00284AC8(void) {
    u8 *var_s0;
    s32 var_s1;

    var_s0 = &D_00388F30;
    var_s1 = 2;
    do {
        var_s1 -= 1;
        M2C_FIELD(var_s0, s8 *, 0x58) = 0;
        func_0029BAB0(var_s0 + 0x40);
        var_s0 += 0x60;
    } while (var_s1 >= 0);
}
