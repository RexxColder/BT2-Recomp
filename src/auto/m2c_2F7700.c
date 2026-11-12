#include "m2c_macros.h"

M2C_UNK func_002F1350(s32, s32);                    /* extern */
M2C_UNK func_002F1470(s32, M2C_UNK *, void *);      /* extern */
M2C_UNK func_002F1480(s32, s32);                    /* extern */
M2C_UNK func_002F1490(s32, M2C_UNK);                /* extern */
M2C_UNK func_002F14A0(s32, s32);                    /* extern */
s32 func_002F15A0(s32);                             /* extern */
s32 func_002F15B8(s32);                             /* extern */
s32 func_002F15E8(s32);                             /* extern */
M2C_UNK func_002F1770(s32);                         /* extern */
extern M2C_UNK func_002F77B8 __attribute__((section(".data")));

void func_002F7700(void *arg0) {
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 temp_s3;
    s32 temp_s4;

    temp_s1 = M2C_FIELD(arg0, s32 *, 4);
    temp_s3 = func_002F15A0(temp_s1);
    temp_s4 = func_002F15B8(temp_s1);
    temp_s0 = func_002F15E8(temp_s1);
    func_002F1770(temp_s1);
    temp_s0_2 = temp_s0 - temp_s3;
    func_002F1490(temp_s1, 0);
    M2C_FIELD(arg0, s32 *, 0x90) = temp_s0_2;
    func_002F1480(temp_s1, temp_s0_2);
    func_002F14A0(temp_s1, temp_s4);
    func_002F1350(temp_s1, temp_s3);
    func_002F1470(temp_s1, &func_002F77B8, arg0);
}
