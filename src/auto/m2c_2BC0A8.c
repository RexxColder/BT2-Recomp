#include "m2c_macros.h"

M2C_UNK func_002BBA38(s32);                         /* extern */
M2C_UNK func_002BBB68(s32, s32);                    /* extern */
M2C_UNK func_002BBC08(void *);                      /* extern */
s32 func_002BC1A0();                                /* extern */
M2C_UNK func_002BC600();                            /* extern */

void func_002BC0A8(void *arg0) {
    s32 temp_s1;
    s32 temp_s3;
    void **temp_s2;

    if (func_002BC1A0(arg0) == 1) {
        temp_s1 = M2C_FIELD(arg0, s32 *, 0x1C);
        temp_s3 = M2C_FIELD(arg0, s32 *, 4);
        temp_s2 = M2C_FIELD(arg0, void ***, 0x14);
        if (temp_s1 != 0) {
            func_002BC600();
            func_002BBC08(arg0);
            M2C_FIELD(arg0, s32 *, 0) = 0;
            func_002BBB68(temp_s3, temp_s1);
            M2C_FIELD(*temp_s2, M2C_UNK (**)(void *), 0xC)(temp_s2);
            M2C_FIELD(arg0, s32 *, 0x1C) = 0;
            func_002BBA38(temp_s3);
        }
    }
}
