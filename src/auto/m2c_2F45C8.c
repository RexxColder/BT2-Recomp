#include "m2c_macros.h"

M2C_UNK func_002EA050(M2C_UNK *);                   /* extern */
extern M2C_UNK D_0037C7E0 __attribute__((section(".data")));

s32  func_002F45C8(void *arg0) {
    if (arg0 == NULL) {
        func_002EA050(&D_0037C7E0);
        return (s8)(-1);
    }
    return (s8)(M2C_FIELD(arg0, s8 *, 1));
}
