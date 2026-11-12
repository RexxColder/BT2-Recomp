#include "m2c_macros.h"

M2C_UNK func_0027AAF8(void *);                      /* extern */
M2C_UNK func_0027AB98(void *);                      /* extern */
M2C_UNK func_00282058(void *);                      /* extern */
M2C_UNK func_00282268(void *);                      /* extern */
extern void *D_00387AFC;

void func_00281360(void) {
    if (M2C_FIELD(D_00387AFC, u8 *, 0x3CCA) == 0) {
        func_0027AB98(D_00387AFC + 0x3090);
        func_0027AAF8(D_00387AFC + 0x3090);
        func_00282268(D_00387AFC + 0x2F00);
        func_00282058(D_00387AFC + 0x2F00);
    }
}
