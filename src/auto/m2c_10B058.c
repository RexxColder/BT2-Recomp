#include "m2c_macros.h"

extern s32 D_003876C8;

s32 BtlObjVis_GetView(s32 arg0) {
    return M2C_FIELD(((arg0 * 4) + D_003876C8), s32 *, 0x91F0);
}
