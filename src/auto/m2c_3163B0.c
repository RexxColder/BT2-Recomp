#include "m2c_macros.h"

void sceMpegGetDecodeMode(void *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    void *temp_t0;

    temp_t0 = M2C_FIELD(arg0, void **, 0x40);
    *arg1 = M2C_FIELD(temp_t0, s32 *, 0xA8);
    *arg2 = M2C_FIELD(temp_t0, s32 *, 0xAC);
    *arg3 = M2C_FIELD(temp_t0, s32 *, 0xB0);
}
