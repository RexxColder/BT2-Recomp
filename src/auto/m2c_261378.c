#include "m2c_macros.h"

M2C_UNK func_00260A50(s32);                         /* extern */
s32 func_00261060(s32);                             /* extern */
M2C_UNK func_003126C8(s32, M2C_UNK);                /* extern */
extern s32 D_003B2654 __attribute__((section(".data")));

void func_00261378(s32 arg0, M2C_UNK arg1) {
    s32 temp_v0;

    if (!(D_003B2654 & 0x100)) {
        temp_v0 = func_00261060(arg0 & 0xFFFF);
        func_003126C8(temp_v0 + 0x9A0, arg1);
        func_003126C8(temp_v0 + 0x9C0, arg1);
        func_00260A50(temp_v0);
    }
}
