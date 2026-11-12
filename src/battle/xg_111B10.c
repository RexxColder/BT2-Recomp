#include "m2c_macros.h"

void *func_0010B080();                              /* extern */
M2C_UNK func_00113430(s32, s32, s32, s32, s32, s32, s32);  /* extern */

/* Calls func_00113430 with the first field of func_0010B080()'s result and arg0, plus constants 1, 0x2A00, 0x2C00, 0, 0. */
void func_00111B10(s32 arg0) {
    func_00113430(M2C_FIELD(func_0010B080(), s32 *, 4), arg0, 1, 0x2A00, 0x2C00, 0, 0);
}
