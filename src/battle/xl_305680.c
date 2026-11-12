#include "m2c_macros.h"

M2C_UNK func_003053C8(M2C_UNK *, M2C_UNK *);        /* extern */
void *memset(void *, int, unsigned int);
extern M2C_UNK D_0037F888 __attribute__((section(".data")));
extern M2C_UNK D_0037F898 __attribute__((section(".data")));
extern M2C_UNK D_0037F8B8 __attribute__((section(".data")));
extern M2C_UNK D_0037F8C8 __attribute__((section(".data")));

void func_00305680(void *arg0) {
    if (arg0 == NULL) {
        func_003053C8(&D_0037F888, &D_0037F898);
        return;
    }
    if (M2C_FIELD(arg0, s8 *, 4) == 0) {
        func_003053C8(&D_0037F8B8, &D_0037F8C8);
        return;
    }
    memset(arg0, 0, 0x30);
    M2C_FIELD(arg0, s8 *, 4) = 0;
}
