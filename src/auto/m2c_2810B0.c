#include "m2c_macros.h"

M2C_UNK func_00282260(void *);                      /* extern */
extern void *D_00387AFC;

void func_002810B0(void) {
    if (M2C_FIELD(D_00387AFC, u8 *, 0x3CCA) == 0) {
        func_00282260(D_00387AFC + 0x2F00);
    }
}
