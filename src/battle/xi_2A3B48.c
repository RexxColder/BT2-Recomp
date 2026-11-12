#include "m2c_macros.h"

M2C_UNK func_003126C8(void *, void *);              /* extern */
extern u8 D_003B1C80 __attribute__((section(".data")));

// Sets two entries (arg0*16 into D_003B1C80, second at +0x80) via func_003126C8, then clears word +0xC of arg1 and arg2.
void func_002A3B48(s32 arg0, void *arg1, void *arg2) {
    s32 temp_s1;

    temp_s1 = arg0 * 0x10;
    func_003126C8(arg1, (u8 *)&D_003B1C80 + temp_s1);
    func_003126C8(arg2, (u8 *)&D_003B1C80 + temp_s1 + 0x80);
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    M2C_FIELD(arg2, s32 *, 0xC) = 0;
}
