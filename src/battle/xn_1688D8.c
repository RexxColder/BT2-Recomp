#include "m2c_macros.h"

void func_00147FB8(s32);                         /* extern */
void func_0014EEF8(s32, void *);                 /* extern */
void func_00168500(void *);                      /* extern */
void *func_001F3758();                              /* extern */

void func_001688D8(void *arg0) {
    s32 temp_s1;
    void *temp_s0;
    void *temp_s2;

    temp_s1 = M2C_FIELD(func_001F3758(arg0), s32 *, 0x38);
    temp_s2 = M2C_FIELD(arg0, void **, 0x38);
    temp_s0 = M2C_FIELD(temp_s2, void **, 0x120);
    func_00168500(arg0);
    func_0014EEF8(temp_s1, temp_s2 + 0x124);
    if (M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x20), s32 *, 4) != 0) {
        func_00147FB8(M2C_FIELD(temp_s0, s32 *, 0));
    }
}
