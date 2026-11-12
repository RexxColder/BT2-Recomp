#include "m2c_macros.h"

M2C_UNK Vu0Screen_StoreMtx();                 /* extern */
s32 func_001267E8();                         /* extern */
M2C_UNK func_00128EF0();                            /* extern */
M2C_UNK func_00128F08();                            /* extern */
M2C_UNK func_00128F90();                      /* extern */
M2C_UNK func_001E6B30();                      /* extern */

void func_001E6FB8(void *arg0) {
    s32 sp[16];
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    if (func_001267E8(M2C_FIELD(temp_s0, s32 *, 0x20), M2C_FIELD(temp_s0, u8 *, 4)) == 0) {
        func_00128EF0();
        Vu0Screen_StoreMtx(sp);
        func_00128F90(sp);
        func_001E6B30(temp_s0);
        func_00128F08();
    }
}
