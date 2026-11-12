#include "m2c_macros.h"

M2C_UNK func_002EA050(M2C_UNK *);                   /* extern */
extern M2C_UNK D_0037CA40 __attribute__((section(".data")));

s32  func_002F5390(void *arg0) {
    if (arg0 == NULL) {
        func_002EA050(&D_0037CA40);
        return (s16)(0);
    }
    return (s16)(M2C_FIELD(arg0, s16 *, 0x40));
}
