#include "m2c_macros.h"

M2C_UNK func_003007F8(M2C_UNK *);                   /* extern */
extern M2C_UNK D_0037E9A8 __attribute__((section(".data")));

s32  func_00300188(void *arg0) {
    if (arg0 == NULL) {
        func_003007F8(&D_0037E9A8);
        return (s8)(-1);
    }
    return (s8)(M2C_FIELD(arg0, s8 *, 1));
}
