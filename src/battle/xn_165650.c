#include "m2c_macros.h"

void func_0014EAE8(s32, void *);                 /* extern */
void *func_001F3758();                              /* extern */
void memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *D_003876A0;

void func_00165650(void *arg0, s32 *arg1) {
    s32 temp_s0;
    void *temp_s2;
    void *temp_v0;

    temp_s0 = M2C_FIELD(func_001F3758(arg0), s32 *, 0x38);
    temp_s2 = M2C_FIELD(arg0, void **, 0x38);
    memset(temp_s2, 0, 0xB10);
    M2C_FIELD(temp_s2, s32 **, 0xB0) = arg1;
    temp_v0 = M2C_FIELD(arg1, void **, 0x24);
    M2C_FIELD(temp_s2, f32 *, 0x10) = (f32) M2C_FIELD(temp_v0, f32 *, 8);
    M2C_FIELD(temp_s2, f32 *, 0x14) = (f32) M2C_FIELD(temp_v0, f32 *, 4);
    M2C_FIELD(temp_s2, f32 *, 0x18) = (f32) M2C_FIELD(temp_v0, f32 *, 4);
    func_0014EAE8(temp_s0, temp_s2 + 0xB4);
    if (!(M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 2)) {
        if (*M2C_FIELD(temp_s2, s32 **, 0xB0) == 0) {
            M2C_FIELD(temp_s2, s32 *, 0) = (s32) (M2C_FIELD(temp_s2, s32 *, 0) | 0x200);
        }
    }
}
