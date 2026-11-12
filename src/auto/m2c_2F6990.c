#include "m2c_macros.h"

M2C_UNK func_002EA050(M2C_UNK *);                   /* extern */
s32 func_002F1330(s32);                             /* extern */
extern M2C_UNK D_0037CDE0 __attribute__((section(".data")));

s32 func_002F6990(void *arg0) {
    if (arg0 == NULL) {
        func_002EA050(&D_0037CDE0);
        return -1;
    }
    return func_002F1330(M2C_FIELD(arg0, s32 *, 4));
}
