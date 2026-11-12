#include "m2c_macros.h"

extern void *gBtlCam;

void func_0025BF08(s32 arg0) {
    M2C_FIELD(gBtlCam, void **, 0x600) = (void *) (gBtlCam + (arg0 * 0x300));
}
