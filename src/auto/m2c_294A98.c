#include "m2c_macros.h"

M2C_UNK ColBox_AddPoint(s32, s32);                  /* extern */
M2C_UNK StgAabb_SetEmpty();                         /* extern */

void ColBounds_OfSeg(s32 arg0, s32 arg1) {
    StgAabb_SetEmpty(arg0);
    ColBox_AddPoint(arg0, arg1);
    ColBox_AddPoint(arg0, arg1 + 0x10);
}
