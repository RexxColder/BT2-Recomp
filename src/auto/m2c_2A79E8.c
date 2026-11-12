#include "m2c_macros.h"

s32 Gsc_GetInt();                                   /* extern */
M2C_UNK func_00101438(s32);                         /* extern */
extern s32 D_003B25F8 __attribute__((section(".data")));

s32 func_002A79E8(s32 arg0) {
    s32 temp_v0;

    if (arg0 == 0) {
        temp_v0 = Gsc_GetInt() + 0x3E1F;
        D_003B25F8 = temp_v0;
        func_00101438(temp_v0);
    }
    return 1;
}
