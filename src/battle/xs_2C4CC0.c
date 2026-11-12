#include "m2c_macros.h"

s32 func_002C06B0();                 /* extern */
M2C_UNK func_002D05E8();    /* extern */
s32 func_002D07B0(void *, s32);               /* extern */
s32 func_002D3030();                 /* extern */

void func_002C4CC0(void *arg0) {
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x1F7C);
    if ((func_002D07B0(arg0, 6) != 0) && (func_002D07B0(arg0, 0x50) != 0)) {
        if ((func_002C06B0(arg0, 2) == 0) && (M2C_FIELD(temp_s1, s32 *, 8) == 0)) {
            if (func_002D3030(arg0, 6) != 0) {
                func_002D05E8(arg0, 6, 0);
            }
        }
    }
    if ((func_002D07B0(arg0, 5) != 0) && (func_002D07B0(arg0, 0x4F) != 0) && (func_002C06B0(arg0, 1) == 0) && (M2C_FIELD(temp_s1, s32 *, 4) == 0) && (func_002D3030(arg0, 7) != 0)) {
        func_002D05E8(arg0, 5, 0);
    }
}
