#include "m2c_macros.h"

extern void *gOrbitCam;

void func_0025CC38(f32 *arg0, f32 *arg1) {
    *arg0 = M2C_FIELD(gOrbitCam, f32 *, 0x24);
    *arg1 = M2C_FIELD(gOrbitCam, f32 *, 0x28);
}
