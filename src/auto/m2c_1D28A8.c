#include "m2c_macros.h"

extern void *D_00387E9C;

void func_001D28A8(void *arg0) {
    M2C_FIELD(arg0, f32 *, 0) = (f32) M2C_FIELD(D_00387E9C, f32 *, 0x14A0);
    M2C_FIELD(arg0, f32 *, 4) = (f32) M2C_FIELD(D_00387E9C, f32 *, 0x14A4);
    M2C_FIELD(arg0, f32 *, 8) = (f32) M2C_FIELD(D_00387E9C, f32 *, 0x14A8);
    M2C_FIELD(arg0, f32 *, 0xC) = (f32) M2C_FIELD(D_00387E9C, f32 *, 0x14AC);
}
