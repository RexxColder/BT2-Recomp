#include "m2c_macros.h"

s32 ColNode_IsLeaf(void *arg0) {
    return ~M2C_FIELD(arg0, s32 *, 0x1C) == 0;
}
