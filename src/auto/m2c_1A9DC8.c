#include "m2c_macros.h"

M2C_UNK BtlTask_SetDead(void *);                    /* extern */
s32 func_00126560();                                /* extern */
extern s32 D_00387840;

void func_001A9DC8(void *arg0) {
    s32 *temp_s1;

    temp_s1 = M2C_FIELD(arg0, s32 **, 0x38);
    if (func_00126560() == 0) {
        M2C_FIELD((D_00387840 + *temp_s1), s8 *, 4) = 0;
    }
    BtlTask_SetDead(arg0);
}
