#include "m2c_macros.h"

M2C_UNK func_00304618(M2C_UNK *, M2C_UNK *);        /* extern */
void *memset(void *, int, unsigned int);
extern M2C_UNK D_0037F6F0 __attribute__((section(".data")));
extern M2C_UNK D_0037F750 __attribute__((section(".data")));
extern M2C_UNK D_0037F760 __attribute__((section(".data")));
extern M2C_UNK D_0037F770 __attribute__((section(".data")));

void func_00304A60(void *arg0) {
    if (arg0 == NULL) {
        func_00304618(&D_0037F750, &D_0037F6F0);
        return;
    }
    if (M2C_FIELD(arg0, s32 *, 4) == 0) {
        func_00304618(&D_0037F760, &D_0037F770);
        return;
    }
    memset(arg0, 0, 0x40);
    M2C_FIELD(arg0, s32 *, 4) = 0;
}
