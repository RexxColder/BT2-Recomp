#include "m2c_macros.h"

void BtlFacade_BeginWait();                      /* extern */
void func_00306F10();                            /* extern */
extern M2C_UNK D_003A0320 __attribute__((section(".data")));

void func_00307700(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;

    BtlFacade_BeginWait();
    temp_s0 = arg0 * 2;
    *(temp_s0 + &D_003A0320) = arg1;
    M2C_FIELD((&D_003A0320 + temp_s0), s32 *, 4) = arg2;
    func_00306F10();
}
