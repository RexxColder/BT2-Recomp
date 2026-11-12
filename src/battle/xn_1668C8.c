#include "m2c_macros.h"

void func_0014EAE8(s32, void *);                 /* extern */
void *func_001F3758();                              /* extern */
void memset(void *, M2C_UNK, M2C_UNK);           /* extern */

void func_001668C8(void *arg0, void *arg1) {
    s32 temp_s1;
    void *temp_s0;
    void *temp_v0;

    temp_s1 = M2C_FIELD(func_001F3758(arg0), s32 *, 0x38);
    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    memset(temp_s0, 0, 0xD40);
    M2C_FIELD(temp_s0, void **, 0xB0) = arg1;
    temp_v0 = M2C_FIELD(arg1, void **, 0x24);
    M2C_FIELD(temp_s0, f32 *, 0x14) = (f32) M2C_FIELD(temp_v0, f32 *, 8);
    M2C_FIELD(temp_s0, f32 *, 0x18) = (f32) M2C_FIELD(temp_v0, f32 *, 4);
    M2C_FIELD(temp_s0, f32 *, 0x1C) = (f32) M2C_FIELD(temp_v0, f32 *, 4);
    func_0014EAE8(temp_s1, temp_s0 + 0xB4);
}
