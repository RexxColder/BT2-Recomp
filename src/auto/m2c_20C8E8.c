#include "m2c_macros.h"

s32 func_002B20B0();                                /* extern */
extern s32 D_00387E18;

s32 func_0020C8E8(void) {
    if (D_00387E18 != 0) {
        return func_002B20B0();
    }
    return -1;
}
