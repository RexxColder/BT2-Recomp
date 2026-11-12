#include "m2c_macros.h"

void func_00147FB8(s32);                         /* extern */
void func_0014EEF8(s32, void *);                 /* extern */
void func_001A1210(s32);                         /* extern */
void *func_001F3758();                              /* extern */

void func_0015A828(void *arg0) {
    s32 temp_s2;
    void *temp_s0;
    void *temp_s1;

    temp_s2 = M2C_FIELD(func_001F3758(arg0), s32 *, 0x38);
    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    temp_s0 = M2C_FIELD(temp_s1, void **, 0x80);
    if (*M2C_FIELD(temp_s0, s32 **, 0x20) != 0xD2) {
        func_001A1210(M2C_FIELD(temp_s0, s32 *, 0));
        func_00147FB8(M2C_FIELD(temp_s0, s32 *, 0));
    }
    func_0014EEF8(temp_s2, temp_s1 + 0x84);
}
