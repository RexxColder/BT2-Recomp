#include "common.h"

s32 BtlCharApi_IsInTechnique(s32 arg0);
s32 func_00126560(void);

s32 func_00174C38(s32 arg0) {
    if (func_00126560() != 0) {
        return 1;
    }
    return BtlCharApi_IsInTechnique(arg0);
}
