#include "m2c_macros.h"

extern void *gBtlCamView;

f32 func_0025B738(void *arg0) {
    return (M2C_FIELD(gBtlCamView, f32 *, 0x1E0) * M2C_FIELD(arg0, f32 *, 0)) + (M2C_FIELD(gBtlCamView, f32 *, 0x1E4) * M2C_FIELD(arg0, f32 *, 4)) + (M2C_FIELD(gBtlCamView, f32 *, 0x1E8) * M2C_FIELD(arg0, f32 *, 8)) + M2C_FIELD(gBtlCamView, f32 *, 0x1EC);
}
