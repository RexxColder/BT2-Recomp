#include "m2c_macros.h"

s32 func_002099C0(M2C_UNK);                         /* extern */
extern s32 D_00387930;

s32 func_00209A78(void) {
    if ((D_00387930 != 0) && ((func_002099C0(0) != 0) || (func_002099C0(1) != 0))) {
        return 1;
    }
    return 0;
}
