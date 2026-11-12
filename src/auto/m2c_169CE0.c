#include "m2c_macros.h"

M2C_UNK func_00126ED0();                            /* extern */
M2C_UNK func_00147FB8(s32);                         /* extern */
M2C_UNK func_0014EEF8(s32, void *);                 /* extern */
M2C_UNK func_00168F70(void *);                      /* extern */
void *func_001F3758();                              /* extern */

void func_00169CE0(void *arg0) {
    s32 *temp_s3;
    s32 temp_s1;
    void *temp_s0;

    temp_s1 = M2C_FIELD(func_001F3758(arg0), s32 *, 0x38);
    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    temp_s3 = M2C_FIELD(temp_s0, s32 **, 0xB0);
    func_00126ED0();
    func_0014EEF8(temp_s1, temp_s0 + 0xB4);
    func_00168F70(arg0);
    func_00147FB8(*temp_s3);
}
