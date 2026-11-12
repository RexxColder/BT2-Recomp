#include "m2c_macros.h"

s32 BtlObjVis_GetView_207EA0();                     /* extern */

// Returns field 0x960 of the view entry arg (4-byte stride) from BtlObjVis_GetView_207EA0.
s32 func_00208768(s32 unused0, s32 arg1) {
    return M2C_FIELD(((arg1 * 4) + BtlObjVis_GetView_207EA0(unused0)), s32 *, 0x960);
}
