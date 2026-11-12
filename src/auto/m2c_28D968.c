#include "m2c_macros.h"

s32 ColBox_Overlaps(M2C_UNK, s32);                  /* extern */

s32 ColNode_TestBox(s32 arg0, M2C_UNK arg1) {
    return ColBox_Overlaps(arg1, arg0) != 0;
}
