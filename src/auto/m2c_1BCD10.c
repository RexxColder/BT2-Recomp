#include "m2c_macros.h"

extern void *gEftPtcl4Mgr;

void func_001BCD10(void *arg0) {
    void *temp_v0;
    void *temp_v1;

    temp_v0 = M2C_FIELD(arg0, void **, 0xEC);
    temp_v1 = M2C_FIELD(temp_v0, void **, 0xF4);
    if (temp_v1 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0) = 0;
        M2C_FIELD(arg0, void **, 0xEC) = temp_v1;
        M2C_FIELD(temp_v1, s32 *, 0xF0) = 0;
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 0xFF);
        M2C_FIELD(gEftPtcl4Mgr, s32 *, 8) = (s32) (M2C_FIELD(gEftPtcl4Mgr, s32 *, 8) - 1);
        return;
    }
    M2C_FIELD(arg0, void **, 0xE8) = temp_v0;
}
