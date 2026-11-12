#include "m2c_macros.h"

M2C_UNK __register_frame_info_table(s32, s32);      /* extern */
s32 malloc(M2C_UNK);                                /* extern */

void func_00323090(s32 arg0) {
    __register_frame_info_table(arg0, malloc(0x18));
}
