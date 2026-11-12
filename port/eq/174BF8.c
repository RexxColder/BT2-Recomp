#include "common.h"

s32 func_00126560(void);
s32 func_0020A9C0(s32 arg0);

s32 func_00174BF8(s32 arg0) {
    if (func_00126560() != 0) {
        return 1;
    }
    return func_0020A9C0(arg0);
}
