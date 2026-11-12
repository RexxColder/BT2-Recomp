#include "m2c_macros.h"

M2C_UNK func_003126C8();             /* extern */
extern u8 D_003B1C80 __attribute__((section(".data")));

// Two calls to func_003126C8 on entries arg0*16 and arg0*16+0x80 of D_003B1C80, passing arg1 then arg2.
void func_002A3AF8(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s1;

    temp_s1 = arg0 * 0x10;
    func_003126C8((u8 *)&D_003B1C80 + temp_s1, arg1);
    func_003126C8((u8 *)&D_003B1C80 + temp_s1 + 0x80, arg2);
}
