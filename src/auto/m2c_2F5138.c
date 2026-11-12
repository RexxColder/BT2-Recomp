#include "m2c_macros.h"

M2C_UNK func_002EA050(M2C_UNK *);                   /* extern */
extern M2C_UNK D_0037C980 __attribute__((section(".data")));

s32  func_002F5138(s32 arg0, s32 arg1) {
    if (arg0 == 0) {
        func_002EA050(&D_0037C980);
        return (s16)(0);
    }
    return (s16)(M2C_FIELD(((arg1 * 2) + arg0), s16 *, 0x42));
}
