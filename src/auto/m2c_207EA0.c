#include "m2c_macros.h"

extern s32 D_00387A40;

s32 BtlObjVis_GetView_207EA0(s32 arg0) {
    return M2C_FIELD(((arg0 * 4) + D_00387A40), s32 *, 0x38184);
}
