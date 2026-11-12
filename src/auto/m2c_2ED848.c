#include "m2c_macros.h"

M2C_UNK func_002EA050(M2C_UNK *);                   /* extern */
M2C_UNK func_00300720(s32);                         /* extern */
extern M2C_UNK D_0037C3B8 __attribute__((section(".data")));

void func_002ED848(void *arg0) {
    if (arg0 == NULL) {
        func_002EA050(&D_0037C3B8);
        return;
    }
    func_00300720(M2C_FIELD(arg0, s32 *, 0x94));
}
