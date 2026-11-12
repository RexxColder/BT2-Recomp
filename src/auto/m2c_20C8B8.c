#include "m2c_macros.h"

void *func_002B1DD0(M2C_UNK);                       /* extern */
extern s32 D_00387E18;

s32  func_0020C8B8(void) {
    if (D_00387E18 != 0) {
        return (u8)(M2C_FIELD(func_002B1DD0(0), u8 *, 0x21));
    }
    return (u8)(0U);
}
